import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    symbols=db.execute("SELECT DISTINCT symbol FROM purchases WHERE user_id=?;", session['user_id'])
    data=[]
    sumtotal=0
    for i in range(len(symbols)):
        symbols[i]=symbols[i]['symbol'].upper()
    symbols=set(symbols)
    for symbol in symbols:
        tempdata={}
        pshares = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = ? AND type = 'purchase' AND UPPER(symbol) = UPPER(?);", session['user_id'], symbol)[0]['SUM(shares)']
        sshares = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = ? AND type = 'sell' AND UPPER(symbol) = UPPER(?);", session['user_id'], symbol)[0]['SUM(shares)']
        if pshares == None:
            pshares = 0
        if sshares == None:
            sshares = 0
        tempdata['symbol']=symbol
        tempdata['shares']=(int(pshares)-int(sshares))
        tempdata['price']=lookup(symbol)['price']
        tempdata['total']= tempdata['shares'] * tempdata['price']
        sumtotal+=tempdata['total']
        if tempdata['shares']>0:
            data.append(tempdata)
    cash=db.execute("SELECT cash FROM users WHERE username=?", session['username'])[0]['cash']
    sumtotal+=cash
    return render_template("index.html", data=data, cash=cash, sumtotal=sumtotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not (symbol and shares):
            return apology(" Missing Symbol/Shares ")
        stock = lookup(symbol)
        shares = int(shares)
        if stock:
            price = int(stock['price']) * shares
            usercash = db.execute("SELECT cash FROM users WHERE username= ?", session['username'])
            usercash = int(usercash[0]['cash'])
            if price > usercash:
                return apology(" Insufficient funds ")
            else:
                usercash -=price
                db.execute("UPDATE users SET cash = ? WHERE username = ?;", usercash, session['username'])
                db.execute("INSERT INTO purchases(user_id, symbol, shares, price, type, transacted) VALUES (?, ?, ?, ?, 'purchase', datetime('now'))", session["user_id"], symbol, shares, int(stock['price']))
                flash("Bought!")
                return redirect('/')
        else:
            return apology(" Invalid Symbol/Shares ")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    data = db.execute("SELECT * FROM purchases WHERE user_id=?", session['user_id'])
    prices = []
    for item in data:
        prices.append(float(lookup(item['symbol'])['price']))
    return render_template("history.html", data=data, prices=prices)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    return render_template('quote.html')

@app.route("/quoted", methods=["GET", "POST"])
@login_required
def quoted():
    symbol = request.form.get("symbol")
    if not symbol:
        return apology(" Missing Symbol ")
    share = lookup(symbol)
    if share:
        price = share['price']
        return render_template('quoted.html', symbol=symbol, price=price)
    else:
        return apology(" Invalid symbol ")


@app.route("/register", methods=["GET", "POST"])
def register():
    usernames = db.execute("SELECT username FROM users")
    for i in range(len(usernames)):
        usernames[i] = usernames[i]['username']
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        if request.form.get("username") in usernames:
            return apology(" Username already in use ")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        else:
            username= request.form.get("username")
            password= request.form.get("password")

        # Check if password and passwordagain match

        if request.form.get("password")==request.form.get("passwordagain"):
            passhash = generate_password_hash(password)
            db.execute(" INSERT INTO users(username, hash) VALUES (?, ?) ", username, passhash)
            return redirect("/")
        else:
            return apology("Passwords must match")



    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    symbols=db.execute("SELECT DISTINCT symbol FROM purchases WHERE user_id=? AND shares>0;", session['user_id'])
    realsymbols=set()
    for i in range(len(symbols)):
        symbols[i]=symbols[i]['symbol'].upper()
        pshares = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = ? AND type = 'purchase' AND UPPER(symbol) = UPPER(?);", session['user_id'], symbols[i])[0]['SUM(shares)']
        sshares = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = ? AND type = 'sell' AND UPPER(symbol) = UPPER(?);", session['user_id'], symbols[i])[0]['SUM(shares)']
        if pshares == None:
            continue
        if sshares == None:
            sshares=0
        if (int(pshares)-int(sshares))>0:
            realsymbols.add(symbols[i])
    symbols=realsymbols
    if request.method=="POST":
        shares = request.form.get("shares")
        symbol = request.form.get("symbol")
        if shares and symbol:
            stock = lookup(symbol)
        shares = int(shares)

        pshares = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = ? AND type = 'purchase' AND UPPER(symbol) = UPPER(?);", session['user_id'], symbol)[0]['SUM(shares)']
        sshares = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = ? AND type = 'sell' AND UPPER(symbol) = UPPER(?);", session['user_id'], symbol)[0]['SUM(shares)']
        if pshares == None:
            pshares = 0
        if sshares == None:
            sshares = 0
        existingshares=(int(pshares)-int(sshares))

        if shares<=existingshares:
            price = stock['price'] * shares
            usercash = db.execute("SELECT cash FROM users WHERE username= ?", session['username'])
            usercash = float(usercash[0]['cash'])
            usercash +=price
            db.execute("UPDATE users SET cash = ? WHERE username = ?;", usercash, session['username'])
            db.execute("INSERT INTO purchases(user_id, symbol, shares, price, type, transacted) VALUES (?, ?, ?, ?, 'sell', datetime('now'))", session["user_id"], symbol, shares, price)
            flash("Sold!")
            return redirect('/')
        else:
            return apology(" Too Many Shares! ")
    else:
        return render_template("sell.html", symbols=symbols)
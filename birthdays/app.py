import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

ids = [element['id'] for element in db.execute("SELECT id FROM birthdays")]


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/savechanges", methods=["POST"])
def savechanges():
    change_id=request.form.get('id')
    change_name=request.form.get('name')
    change_month=request.form.get('month')
    change_day=request.form.get('day')
    db.execute(" UPDATE birthdays SET name = ?, month=?, day=? WHERE id=?; ", change_name, change_month, change_day, change_id)
    return redirect("/")

@app.route("/delete", methods=["POST"])
def delete():
    id=request.form.get('id')
    if int(id) in ids:
        db.execute("DELETE FROM birthdays WHERE id=?", id)
        return redirect("/")
    else:
        return redirect("/")


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        name = request.form.get('name')
        if not name:
            return redirect("/")
        month = request.form.get('month')
        if not month:
            return redirect("/")
        day = request.form.get('day')
        if not day:
            return redirect("/")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        birthdays= db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)

from cs50 import get_float

while True:
    n=get_float("Change: ")
    if n>=0:
        break
n=n*100

coins=0
coins+=n//25
n%=25
coins+=n//10
n%=10
coins+=n//5
n%=5
coins+=n

print(int(coins))

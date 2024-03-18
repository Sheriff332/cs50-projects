import pyfiglet
from sys import argv,exit

if len(argv)==1:
    pass
elif (len(argv) !=3) or (argv[1].lower() not in ("-f","--font")) or (argv[2].lower() not in ("slant","rectangles","alphabet")):
    print ("Invalid usage, use python figlet.py -f/--font slant/rectangles/alphabet")
    print("Alternatively, use python figlet.py")
    exit()

s=input("Input: ")

f = pyfiglet.figlet_format(s, font= "standard" if len(argv)==1 else argv[2])

print("Output: ")
print (f)

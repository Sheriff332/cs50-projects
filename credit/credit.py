from cs50 import get_int

cc=get_int("Number: ")
cc_str=str(cc)
sumval=0
for i in range(-2, -(len(cc_str)+1), -2):
    sumval += (2*int(cc_str[i]) %10) + (2*int(cc_str[i])//10)
for i in range(-1, -(len(cc_str)+1), -2):
    sumval += int(cc_str[i])
if sumval%10==0:
    first_digit=int(cc_str[0])
    first_two_digits=int(cc_str[:2])
    if first_digit==4 and len(cc_str) in [13,16]:
        print("VISA")
    elif first_two_digits in (51,56) and len(cc_str)==16:
        print("MASTERCARD")
    elif first_two_digits in [34,37] and len(cc_str)==15:
        print("AMEX")
    else:
        print("UNKNOWN")
else:
    print("INVALID")

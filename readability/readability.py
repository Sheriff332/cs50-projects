s=input("Text: ")
letters=sentences=0
words=1
for i in range(len(s)):
    if s[i].isalnum():
        letters+=1
    elif s[i].isspace():
        words+=1
    elif s[i] in ['.','?','!']:
        sentences+=1
a = (letters/words)*100.0
b = (sentences/words) *100.0
index = round((0.0588 * a) - (0.296 * b) - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")

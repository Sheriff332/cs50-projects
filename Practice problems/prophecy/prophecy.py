import csv
from cs50 import SQL
db = SQL("sqlite:///roster.db")

with open ("students.csv", 'r') as students:
    houses_dict={}
    students_dict={}
    student_houses_dict={}
    reader = csv.DictReader(students)
    for row in reader:
        tmp = {row['id']:row['student_name']}
        students_dict.update(tmp)
        tmp = {row['house']:row['head']}
        houses_dict.update(tmp)
        tmp = {row['id']:row['house']}
        student_houses_dict.update(tmp)
for student in students_dict:
    try:
        n = db.execute("INSERT INTO students (id, student_name) VALUES (?, ?);", student, students_dict[student])
    except ValueError:
        print("Value already Exists.")
for house in houses_dict:
    try:
        n = db.execute("INSERT INTO houses (house_name,head) VALUES (?, ?);", house, houses_dict[house])
    except ValueError:
        print("Value already Exists.")
for student in student_houses_dict:
    try:
        n = db.execute("INSERT INTO student_houses (student_id, house_name) VALUES (?, ?);", student, student_houses_dict[student])
    except ValueError:
        print("Value already Exists.")

#SELECT * FROM students JOIN student_houses ON students.id = student_houses.student_id JOIN houses ON student_houses.house_name = houses.house_name ORDER BY id;

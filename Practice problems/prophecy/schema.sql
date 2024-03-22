CREATE TABLE students(
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);


CREATE TABLE houses (
    house_name TEXT,
    head TEXT,
    PRIMARY KEY(house_name)
);


CREATE TABLE student_houses (
    student_id INTEGER,
    house_name INTEGER,
    PRIMARY KEY(student_id, house_name),
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_name) REFERENCES houses(house_name)
);

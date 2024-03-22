SELECT DISTINCT people2.name
FROM people AS people1
JOIN stars AS stars1 ON people1.id = stars1.person_id
JOIN movies ON stars1.movie_id = movies.id
JOIN stars AS stars2 ON movies.id = stars2.movie_id
JOIN people AS people2 ON stars2.person_id = people2.id
WHERE people1.name = 'Kevin Bacon' AND people2.name != 'Kevin Bacon'
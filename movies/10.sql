SELECT DISTINCT(people.name) FROM directors JOIN movies ON directors.movie_id = movies.id JOIN people ON directors.person_id = people.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >=9.0;

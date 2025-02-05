WITH count_visit AS
		(SELECT person_id, count(*) AS count_of_visits
		FROM person_visits
		GROUP BY person_id)
SELECT p.name, count_of_visits
FROM count_visit cv
JOIN person p ON p.id = cv.person_id
WHERE count_of_visits >= 3
ORDER BY count_of_visits DESC


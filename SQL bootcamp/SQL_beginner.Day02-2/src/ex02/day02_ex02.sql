-- 	(SELECT COALESCE(person.name,'-'), t2.visit_date FROM person
-- 	FULL JOIN (SELECT person_id, visit_date FROM person_visits
-- 			  WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS t2
-- 	ON person.id = t2.person_id)
--  this select creates table with person.name and person_visits.visit_date between 01-01 and 03-01

-- COALESCE(t1.name, '-') replaces NULL with '-' in table
SELECT 	COALESCE(t1.name, '-') AS person_name, 
		t1.visit_date, 
		COALESCE(pizzeria.name, '-') AS pizzeria_name
FROM 	(SELECT person.name, t2.visit_date, t2.pizzeria_id  FROM person
		FULL JOIN (SELECT person_id, visit_date, pizzeria_id FROM person_visits
				  WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS t2
		ON person.id = t2.person_id) AS t1
FULL JOIN pizzeria
ON pizzeria.id = t1.pizzeria_id
ORDER BY
	-- first order by name columns where name = '-'
    CASE
        WHEN COALESCE(t1.name, '-') = '-' THEN 0
        ELSE 1
    END,
	t1.name,
	t1.visit_date, 
	pizzeria.name
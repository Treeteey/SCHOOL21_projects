SELECT name, rating FROM pizzeria
WHERE name <> ALL (SELECT DISTINCT name FROM pizzeria
				   JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id)
-- create second query with pizzerias that were visited
-- and check if name is NOT EQUAL to any name from this list 
-- if not matches = return true  | ALL returns true or false
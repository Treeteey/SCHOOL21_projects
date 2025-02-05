-- SELECT name FROM pizzeria
-- WHERE name NOT IN (SELECT DISTINCT name FROM pizzeria
-- JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id)

-----------------------comment-------------------------------
-- second select creates table with pizzerias that were visited in person_visits
-- name NOT IT - if name is not in this new table then add it to first select table


SELECT name
FROM pizzeria
WHERE NOT EXISTS (
    SELECT 1
    FROM person_visits
    WHERE person_visits.pizzeria_id = pizzeria.id
);

--for each 'id' equal to 'name' second query is checked and if in 'pizzeria_id'
-- no matching to current 'id' of 'pizzeria' - then return false
--with NOT - false turns into true - and that name is listed to output



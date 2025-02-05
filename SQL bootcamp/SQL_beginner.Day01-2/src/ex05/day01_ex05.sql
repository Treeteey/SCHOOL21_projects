SELECT person.id AS "person.id", person.name AS "person.name", person.age, person.gender, person.address, 
       pizzeria.id AS "pizzeria.id", pizzeria.name AS "pizzeria.id", pizzeria.rating
FROM person
JOIN  pizzeria
ON pizzeria.id = person.id
-- SELECT pizzeria.* FROM pizzeria


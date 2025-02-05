SELECT person.name, pizzeria.name FROM person_visits, person, pizzeria
WHERE person_visits.person_id = person.id
AND person_visits.visit_date BETWEEN '2022-01-07' AND '2022-01-09'
AND person_visits.pizzeria_id = pizzeria.id


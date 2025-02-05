--creating materialized view must be separeted from selecting from them
--you cant create and select in one query materialized view ONLY simple view
--1) 
CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
	(SELECT * FROM (WITH dmitriy_visited AS
							(SELECT pizzeria_id FROM person_visits
							LEFT JOIN person
							ON person.id = person_visits.person_id
							WHERE person_id = (SELECT id FROM person WHERE name = 'Dmitriy')
							AND visit_date = '2022-01-08'),
						pizzerias_names AS 
							(SELECT dmitriy_visited.pizzeria_id FROM dmitriy_visited
							JOIN menu ON menu.pizzeria_id = dmitriy_visited.pizzeria_id
							WHERE price < 800)
					SELECT pi.name FROM pizzeria pi
					JOIN pizzerias_names ON pizzerias_names.pizzeria_id = pi.id
				   )
	)

--2) 
-- SELECT *  FROM mv_dmitriy_visits_and_eats

-- DROP MATERIALIZED VIEW IF EXISTS mv_dmitriy_visits_and_eats

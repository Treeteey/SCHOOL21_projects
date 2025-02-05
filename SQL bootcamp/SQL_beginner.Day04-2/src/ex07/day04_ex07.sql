-- 1)
-- SELECT *  FROM mv_dmitriy_visits_and_eats

--2)
INSERT INTO person_visits 
values 	(
		(SELECT MAX(id)+1 FROM person_visits),
		(SELECT id FROM person WHERE name = 'Dmitriy'),
		(SELECT id FROM pizzeria WHERE name = 'DoDo Pizza'),
		'2022-01-08'
		);
		
REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;


--3)
-- SELECT *  FROM mv_dmitriy_visits_and_eats







-- DELETE FROM person_visits WHERE id = 22;
-- SELECT * FROM person_visits

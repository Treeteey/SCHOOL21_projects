------------------------------------------------------------------
--нужно добавить изменения в базу данных из                      |
--  Day03 during Exercises 07-13 and in Day04 during Exercise 07 |
------------------------------------------------------------------

-- day03_07
insert into menu values(19,2,'greek pizza', 800);

-- day03_08
insert into menu values((SELECT MAX(id)+1 FROM menu), 
						(SELECT DISTINCT id FROM pizzeria WHERE name = 'Dominos'), 
						'sicilian pizza', 
						900);

-- day03_09
INSERT INTO person_visits VALUES ((SELECT MAX(id)+1 FROM person_visits),
								 (SELECT id FROM person WHERE name = 'Denis'),
								 (SELECT id FROM pizzeria WHERE name = 'Dominos'),
								 '2022-02-24');
INSERT INTO person_visits VALUES ((SELECT MAX(id)+1 FROM person_visits),
								 (SELECT id FROM person WHERE name = 'Irina'),
								 (SELECT id FROM pizzeria WHERE name = 'Dominos'),
								 '2022-02-24');

-- day03_10
INSERT INTO person_order VALUES ((SELECT MAX(id)+1 FROM person_order), 				--id
								 (SELECT id FROM person WHERE name = 'Denis'), 		--person_id
								 (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),	--menu_id
								 '2022-02-24');
INSERT INTO person_order VALUES ((SELECT MAX(id)+1 FROM person_order), 				--id
								 (SELECT id FROM person WHERE name = 'Irina'), 		--person_id
								 (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),	--menu_id
								 '2022-02-24');		

-- day03_11
UPDATE menu
SET price = price * 0.9
WHERE pizza_name = 'greek pizza';

-- day03_12
WITH new_table AS	
	(SELECT gs.* AS id, 
			person.id AS person_id, 
			(SELECT DISTINCT id FROM menu WHERE pizza_name = 'greek pizza') AS menu_id, 
			DATE'2022-02-25' AS order_date
	 
	 -- make columns with new menu_ids starting from last menu_id + 1 for each person = gs!
	FROM 	generate_series((SELECT MAX(id)+1 AS max_id FROM person_order) ,
							(SELECT (SELECT MAX(id)+1 FROM person_order) + MAX(id) FROM person),
							1) AS gs,
			person
	--connecting new menu_ids to each person id: 23,1 24,2 ... 31,9
	WHERE gs = person.id + (SELECT MAX(id) AS max_id FROM person_order))
	
INSERT INTO person_order

-- day03_13
DELETE FROM person_order WHERE order_date = '2022-02-25';
DELETE FROM menu WHERE pizza_name = 'greek pizza';

-- day04_07
INSERT INTO person_visits 
values 	(
		(SELECT MAX(id)+1 FROM person_visits),
		(SELECT id FROM person WHERE name = 'Dmitriy'),
		(SELECT id FROM pizzeria WHERE name = 'DoDo Pizza'),
		'2022-01-08'
		);

-- выполни предыдущие команды чтобы добавить недостающие данные в БД

SELECT pv.person_id, COUNT(*) AS count_of_visits
FROM person_visits pv
GROUP BY pv.person_id
ORDER BY count_of_visits DESC, pv.person_id ASC;


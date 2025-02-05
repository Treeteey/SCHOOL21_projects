WITH menu_id_gender AS
		(SELECT menu_id, pe.gender FROM person_order po
		JOIN person pe ON pe.id = po.person_id),
	--joined person_order and person
	
	pizzeria_id_gender AS
		(SELECT menu.pizzeria_id,  menu_id_gender.gender FROM menu_id_gender
		JOIN menu ON menu.id = menu_id_gender.menu_id),
	--joined person_order and person and menu
	
	pizzeria_name_gender AS
		(SELECT pi.name, pizzeria_id_gender.gender FROM pizzeria_id_gender
		JOIN pizzeria pi ON pi.id = pizzeria_id_gender.pizzeria_id),
	--joined person_order and person and menu and pizzeria = pizzeria_name and person_gender
	
	pizzeria_name_count AS
		(SELECT pizzeria_name_gender.name, COUNT(*) FROM pizzeria_name_gender
 		GROUP BY pizzeria_name_gender.name),
	--count all people visited each pizzeria
	
	pizzeria_name_males AS 
		(SELECT 
			pizzeria_name_gender.name, 
			COUNT(CASE WHEN gender = 'male' THEN 1 ELSE NULL END) AS male_count
		FROM pizzeria_name_gender
		GROUP BY pizzeria_name_gender.name)
	--count males visited each pizzeria

SELECT pizzeria_name_males.name FROM pizzeria_name_males
JOIN pizzeria_name_count ON pizzeria_name_count.name =pizzeria_name_males.name
WHERE male_count = pizzeria_name_count.count OR male_count = 0
ORDER BY  pizzeria_name_males.name
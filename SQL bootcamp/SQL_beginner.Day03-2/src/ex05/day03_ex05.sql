WITH andrey_visit AS
		(SELECT DISTINCT pizzeria_id FROM person_visits pv
		JOIN person pe ON pe.id = pv.person_id 
		WHERE pe.name = 'Andrey'),
		
	--find menu_id from person_order which Andrey ordered
	andrey_order_menu_id AS 
		(SELECT DISTINCT menu_id AS andrey_menu FROM person_order po
		JOIN person pe ON pe.id = po.person_id 
		WHERE pe.name = 'Andrey'),
		
	--find pizzeria_id from menu which Andrey ordered
	andrey_order_pizzeria_id AS 
		(SELECT DISTINCT menu.pizzeria_id FROM andrey_order_menu_id
		JOIN menu ON menu.id = andrey_order_menu_id.andrey_menu),
	
	--find pizzeria_id which Andrey visited but not ordered
	visited_not_ordered_id AS 
		(SELECT andrey_visit.pizzeria_id FROM andrey_visit
		WHERE andrey_visit.pizzeria_id NOT IN (SELECT pizzeria_id FROM andrey_order_pizzeria_id))

SELECT pi.name FROM pizzeria pi 
JOIN visited_not_ordered_id ON visited_not_ordered_id.pizzeria_id = pi.id

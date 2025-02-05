CREATE VIEW v_price_with_discount AS
	(SELECT * FROM
		(SELECT person_menu.name, 
				menu.pizza_name, 
				menu.price, 
				ROUND(menu.price - 0.1*menu.price) AS discount_price
		FROM menu
		JOIN 	(SELECT pe.name, menu_id FROM person_order po
				JOIN person pe ON pe.id = po.person_id) AS person_menu 
		ON menu.id = person_menu.menu_id
		ORDER BY person_menu.name)
	);

SELECT * FROM v_price_with_discount

-- 	 DROP VIEW IF EXISTS v_price_with_discount








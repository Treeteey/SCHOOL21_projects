SELECT 	p.name, 
		pizza_name, 
		price, 
		round((price*(100-discount)/100),2),
		pi.name 
FROM person_order po
JOIN person p ON p.id = po.person_id
JOIN menu m ON m.id = po.menu_id
JOIN pizzeria pi ON pi.id = m.pizzeria_id
JOIN person_discounts pd ON pd.person_id = p.id AND pi.id = pd.pizzeria_id 
ORDER BY p.name, pizza_name

-- SELECT * FROM person_discounts
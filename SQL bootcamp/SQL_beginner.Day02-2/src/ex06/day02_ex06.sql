-- orders that Denis and Anna made
WITH orders AS
		(SELECT menu_id AS orders_id FROM person_order
		LEFT JOIN person
		ON person.id = person_order.person_id
		WHERE person_id = ANY (SELECT id FROM person WHERE name = 'Denis' OR name = 'Anna'))

SELECT pizzerias.pizza_name, pizzeria.name AS pizzeria_name FROM 
	--pizzerias and pizzas thats in temporary ORDERS table
	(SELECT pizzeria_id, pizza_name FROM menu
	JOIN orders ON orders.orders_id = menu.id) AS pizzerias
JOIN pizzeria
ON pizzeria.id = pizzerias.pizzeria_id
ORDER BY pizza_name, pizzeria_name

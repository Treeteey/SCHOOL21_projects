WITH not_ordered AS (SELECT id FROM menu
					EXCEPT
					SELECT DISTINCT menu_id FROM person_order),
	pizzas AS (SELECT menu.id, pi.name, menu.pizza_name, menu.price FROM menu
			  JOIN pizzeria pi ON menu.pizzeria_id = pi.id)
SELECT pizza_name, price, pizzas.name AS pizzeria_name FROM pizzas
JOIN not_ordered ON pizzas.id = not_ordered.id
ORDER BY pizza_name, price



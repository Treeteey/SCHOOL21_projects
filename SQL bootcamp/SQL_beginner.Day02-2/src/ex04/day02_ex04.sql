SELECT pizzas.pizza_name, pizzeria.name AS pizzeria_name, pizzas.price FROM pizzeria
RIGHT JOIN (SELECT * FROM menu
			WHERE pizza_name = 'mushroom pizza' OR pizza_name = 'pepperoni pizza') AS pizzas
ON pizzeria.id = pizzas.pizzeria_id
ORDER BY pizza_name, pizzeria.name


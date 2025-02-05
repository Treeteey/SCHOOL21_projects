WITH pizzerias_id_table AS
	(SELECT t1.pizza_name, t1.pizzeria_id AS pizzeria_id_1, t2.pizzeria_id AS pizzeria_id_2, t1.price FROM menu t1
	CROSS JOIN menu t2
	WHERE t1.pizza_name = t2.pizza_name
	AND t1.pizzeria_id < t2.pizzeria_id
	AND t1.price = t2.price)



SELECT pizzerias_id_table.pizza_name, pi2.name AS pizzeria_name_1, pi1.name AS pizzeria_name_2, pizzerias_id_table.price
FROM pizzerias_id_table
JOIN pizzeria pi1 ON pizzeria_id_1 = pi1.id 
JOIN pizzeria pi2 ON pizzeria_id_2 = pi2.id 
ORDER BY pizza_name

-- SELECT * FROM pizzerias_id_table

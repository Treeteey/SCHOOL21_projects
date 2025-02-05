-- find persons id who ate pepperoni or mushroom
WITH pizza_eaters AS
	(SELECT person_id FROM person_order
	JOIN menu ON person_order.menu_id = menu.id
	WHERE pizza_name = 'pepperoni pizza' OR pizza_name = 'mushroom pizza')
--then find name of person using id's from pizze_eaters
SELECT name FROM person
--which meets these restrictions
WHERE id IN (SELECT person_id FROM pizza_eaters)
AND gender = 'male'
AND (address ='Moscow' OR address = 'Samara')
ORDER BY name DESC


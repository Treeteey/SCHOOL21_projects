-- НЕ СОВПАДАЕТ !! -----------------
WITH pizzeria_count AS
		(
		(SELECT pizzeria_id, COUNT(*) AS count, 'visit' AS action
		FROM person_visits
		GROUP BY pizzeria_id
		ORDER BY count DESC
		LIMIT 3)
		UNION 
		(SELECT m.pizzeria_id, COUNT(*), 'order' AS action
		FROM person_order po
		JOIN menu m ON m.id = po.menu_id
		GROUP BY m.pizzeria_id
		ORDER BY count DESC
		LIMIT 3)
		)

SELECT p.name, pc.count, pc.action
FROM pizzeria_count pc
JOIN pizzeria p ON p.id = pc.pizzeria_id
ORDER BY action, count DESC
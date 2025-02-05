-- НЕ СОВПАДАЕТ !! -----------------
-- WITH pizzeria_count AS
-- 		(SELECT pizzeria_id, COUNT(*) AS count, 'visit' AS action
-- 		FROM person_visits
-- 		GROUP BY pizzeria_id
-- 		UNION ALL
-- 		(SELECT m.pizzeria_id, COUNT(*), 'order' AS action
-- 		FROM person_order po
-- 		JOIN menu m ON m.id = po.menu_id
-- 		GROUP BY m.pizzeria_id
-- 		))

-- SELECT p.name, pc.pizzeria_id, pc.count, pc.action
-- FROM pizzeria_count pc
-- JOIN pizzeria p ON p.id = pc.pizzeria_id
-- ORDER BY count DESC, action
-- LIMIT 3;

WITH 
	visit_count AS
		(SELECT pizzeria_id, COUNT(*) AS count, 'visit' AS action
		FROM person_visits
		GROUP BY pizzeria_id),
	order_count AS 
		(SELECT m.pizzeria_id, COUNT(*), 'order' AS action
		FROM person_order po
		JOIN menu m ON m.id = po.menu_id
		GROUP BY m.pizzeria_id),
	sum_count AS 
		(SELECT vc.pizzeria_id, vc.count + oc.count AS total_count
		FROM visit_count vc
		FULL JOIN order_count oc ON oc.pizzeria_id = vc.pizzeria_id)
		
SELECT p.name, total_count
FROM sum_count sc
JOIN pizzeria p ON p.id = sc.pizzeria_id
WHERE total_count > 0
ORDER BY total_count DESC, p.name

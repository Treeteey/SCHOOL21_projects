WITH visits AS
		(SELECT pi.id, pi.name, kate_visits. visit_date 
		FROM (SELECT pv.* FROM person_visits pv
			 JOIN person p ON p.id = pv.person_id
			 WHERE p.name = 'Kate') AS kate_visits
		JOIN pizzeria pi ON kate_visits.pizzeria_id = pi.id)

SELECT pizza_name, price, visits.name AS pizzeria_name, visit_date FROM visits
JOIN menu ON visits.id = menu.pizzeria_id
WHERE price BEtWEEN 800 AND 1000
ORDER BY pizza_name, price, pizzeria_name


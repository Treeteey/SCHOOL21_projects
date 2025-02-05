SELECT p.address, pi.name, COUNT(*) AS count  FROM person_order po
JOIN menu m ON m.id = po.menu_id
JOIN pizzeria pi ON pi.id = m.pizzeria_id
JOIN person p ON p.id = po.person_id
GROUP BY pi.name, address
ORDER BY address, pi.name


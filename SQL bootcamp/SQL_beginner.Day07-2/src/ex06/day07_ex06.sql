SELECT p.name AS name,
    COUNT(po.id) AS count_of_orders,
    CASE
        WHEN AVG(m.price) <> ROUND(AVG(m.price), 0) THEN ROUND(AVG(m.price), 2)
        ELSE ROUND(AVG(m.price), 0)
    END AS average_price,
    CASE
        WHEN MAX(m.price) <> ROUND(MAX(m.price), 0) THEN ROUND(MAX(m.price), 2)
        ELSE ROUND(MAX(m.price), 0)
    END AS max_price,
    CASE
        WHEN MIN(m.price) <> ROUND(MIN(m.price), 0) THEN ROUND(MIN(m.price), 2)
        ELSE ROUND(MIN(m.price), 0)
    END AS min_price
FROM pizzeria p
JOIN menu m ON p.id = m.pizzeria_id
JOIN person_order po ON m.id = po.menu_id
GROUP BY p.name
ORDER BY p.name;

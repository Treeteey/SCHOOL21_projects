-- SELECT order_date AS action_date,  person_id FROM person_order
-- INTERSECT
-- SELECT visit_date AS action_date,  person_id FROM person_visits
-- ORDER BY action_date, person_id DESC

(SELECT order_date AS action_date,  name AS person_name FROM person_order
JOIN person ON person.id = person_order.person_id) 
INTERSECT
(SELECT visit_date AS action_date,  name AS person_name FROM person_visits
JOIN person ON person.id = person_visits.person_id) 
ORDER BY action_date, person_name DESC


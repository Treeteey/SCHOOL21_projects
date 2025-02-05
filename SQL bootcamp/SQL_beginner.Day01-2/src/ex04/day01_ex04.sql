SELECT order_date AS action_date,  person_id FROM person_order
WHERE order_date = '2022-01-07'
EXCEPT ALL
SELECT visit_date AS action_date,  person_id FROM person_visits
WHERE visit_date = '2022-01-07'

-- SELECT order_date AS action_date,  person_id FROM person_order
-- WHERE order_date = '2022-01-07'
-- SELECT visit_date AS action_date,  person_id FROM person_visits
-- WHERE visit_date = '2022-01-07'
CREATE UNIQUE INDEX idx_person_discounts_unique ON person_discounts(person_id, pizzeria_id);
SET enable_seqscan = OFF;


EXPLAIN ANALYZE SELECT po.person_id, m.pizzeria_id, pd.discount FROM person_order po
JOIN menu m ON m.id = po.menu_id
JOIN person_discounts pd ON pd.person_id = po.person_id AND pd.pizzeria_id = m.pizzeria_id
WHERE po.person_id = 4 AND m.pizzeria_id = 5;


						-- turn on default planner
-- SET enable_seqscan = ON;

	
-- SELECT person_id, pizzeria_id FROM person_order po
-- JOIN menu m ON m.id = po.menu_id

						-- show all indexes
-- SELECT schemaname, tablename, indexname, indexdef
-- FROM pg_indexes
-- ORDER BY indexname

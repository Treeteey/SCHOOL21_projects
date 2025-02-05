CREATE UNIQUE INDEX  idx_person_order_order_date 
ON person_order (person_id, menu_id)
WHERE order_date = '2022-01-01';

SET enable_seqscan = off;
EXPLAIN ANALYZE SELECT person_id, menu_id FROM person_order
WHERE order_date = '2022-01-01';


-- Index only Scan using ... - appears when you get column added to index
-- Index Scan using .. - will appear if in select you want get another column





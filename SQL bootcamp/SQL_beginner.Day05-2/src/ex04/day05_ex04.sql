--UNIQUE система должна контролировать повторяющиеся значения в таблице 
-- при создании индекса

CREATE UNIQUE INDEX idx_menu_unique ON menu (pizzeria_id, pizza_name);

SET enable_seqscan = OFF;

EXPLAIN ANALYZE SELECT *
FROM menu
WHERE pizzeria_id > 2 AND pizza_name = 'cheese pizza'

-- включить последовательно сканирование по умолчанию
-- SET enable_seqscan = ON;

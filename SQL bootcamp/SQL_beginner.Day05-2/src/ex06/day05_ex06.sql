-- Оконная функция выполняет вычисления для набора строк, некоторым образом связанных с текущей строкой
-- Однако с оконными функциями строки не группируются в одну выходную строку
-- OVER - превращает агрегатную функцию в оконную (то есть не сгруппировывает строки)
--  PARTITION BY разделяет строки по группам объединяя одинаковые значения выражений 

-- UNBOUNDED PRECEDING — указывает, что окно начинается с первой строки группы.
-- UNBOUNDED FOLLOWING — с помощью данной инструкции можно указать, что окно заканчивается на последней строке группы.

CREATE INDEX idx_1 ON pizzeria(rating);
SET enable_seqscan = off;

EXPLAIN ANALYZE SELECT
	m.pizza_name AS pizza_name,
	max(rating) OVER (PARTITION BY rating ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
FROM  menu m
INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1,2;

-- DROP INDEX idx_1;

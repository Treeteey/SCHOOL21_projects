-- Результат выполнения запроса:

-- EXPLAIN ANALYZE SELECT menu.pizza_name, pizzeria.name FROM menu, pizzeria
-- WHERE menu.pizzeria_id = pizzeria.id

-- "Hash Join  (cost=1.41..22.72 rows=18 width=64) (actual time=0.028..0.031 rows=18 loops=1)"
-- "  Hash Cond: (pizzeria.id = menu.pizzeria_id)"
-- "  ->  Seq Scan on pizzeria  (cost=0.00..18.10 rows=810 width=40) (actual time=0.011..0.011 rows=6 loops=1)"
-- "  ->  Hash  (cost=1.18..1.18 rows=18 width=40) (actual time=0.012..0.012 rows=18 loops=1)"
-- "        Buckets: 1024  Batches: 1  Memory Usage: 9kB"
-- "        ->  Seq Scan on menu  (cost=0.00..1.18 rows=18 width=40) (actual time=0.006..0.008 rows=18 loops=1)"
-- "Planning Time: 0.128 ms"
-- "Execution Time: 0.049 ms"

-- 1)
-- индексы могут не работать если в запросе необходимо обращаться 
-- к другим столбцам (или из другой страницы)
-- чтобы индекс работал нужно чтоб в запросе использовались только 
-- столбцы указанные в индексе!
-- пример - создали индекс по столбцу Х:
-- WHERE x > 4 AND z = 0 - индекс не подключиться так как в условии есть другой столбец z
-- WHERE x > 4
-- 2)
-- также в данном примере индекс не используется планировщиком PgSQL
-- потому что объем данных незначителен, и по умолчанию будет использоваться 
-- последовательное сканирование


SET enable_seqscan = OFF; --отключить последовательное сканирование по умолчанию
EXPLAIN ANALYZE SELECT menu.pizza_name, pizzeria.name FROM menu
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id;
-- SET enable_seqscan = ON;



-- EXPLAIN ANALYZE SELECT * FROM menu
--"Seq Scan on menu  (cost=0.00..1.18 rows=18 width=80) (actual time=0.010..0.011 rows=18 loops=1)"
-- seq scan - последовательное сканирование
-- cost - единицей стоимости считается операция чтения страницы с диска
-- 0.00 - приблизительная стоимость запуска
-- 1.18 - приблизительная общая стоимость
-- 18   - ожидаемое число строк
-- 80   - ожидаемый средний размер строк в байтах

-- number of pages and number of strings with data
-- SELECT relpages, reltuples FROM pg_class WHERE relname = 'menu'
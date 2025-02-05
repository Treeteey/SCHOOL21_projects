-- Когда вы создаете индекс на столбец или несколько столбцов таблицы, 
-- PostgreSQL генерирует специальную структуру данных (обычно B-дерево), 
-- которая содержит отсортированные значения указанных столбцов и ссылки
-- на соответствующие строки таблицы. Это позволяет системе быстро 
-- находить строки по значениям индексированных столбцов, выполняя операции поиска
-- в индексе вместо полного сканирования таблицы.

-- upper() -  makes string case INSENSITIVE
-- so in condition if we use 'ANNA' instead of 'Anna'
-- it will work
-- person(upper(name))- makes index column case INSENSITIVE
CREATE INDEX idx_person_name ON person(upper(name));

EXPLAIN ANALYZE SELECT * FROM person
WHERE upper(name) = 'ANNA'


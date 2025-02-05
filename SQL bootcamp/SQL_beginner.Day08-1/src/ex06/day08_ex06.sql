--установка уровня изоляции для обеих сессий 
SET SESSION CHARACTERISTICS AS TRANSACTION  ISOLATION LEVEL REPEATABLE READ;
--проверка уровня изоляции
SHOW TRANSACTION ISOLATION LEVEL;

-- 1
BEGIN;
-- 2
BEGIN;
-- 1
SELECT SUM(rating) FROM pizzeria;
-- 2
UPDATE pizzeria SET rating = 5.0 WHERE name = 'Pizza Hut';
-- 2 
COMMIT;
-- 1
SELECT SUM(rating) FROM pizzeria;
-- 1
COMMIT;
-- после коммита во второй сессии данные для первой сессии НЕ изменились,
-- они изменяться когда завершится текущая транзакция в первой сессии


-- 1
SELECT SUM(rating) FROM pizzeria;
-- 2
SELECT SUM(rating) FROM pizzeria;

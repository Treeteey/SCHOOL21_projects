--установка уровня изоляции для обеих сессий 
SET SESSION CHARACTERISTICS AS TRANSACTION  ISOLATION LEVEL READ COMMITTED;
--проверка уровня изоляции
SHOW TRANSACTION ISOLATION LEVEL;

-- 1
BEGIN;
-- 2
BEGIN;
-- 1
SELECT SUM(rating) FROM pizzeria;
-- 2
UPDATE pizzeria SET rating = 1.0 WHERE name = 'Pizza Hut';
-- 2 
COMMIT;
-- 1
SELECT SUM(rating) FROM pizzeria;
-- 1
COMMIT;
-- после коммита во второй сессии данные для первой сессии тоже изменились,
-- хотя транзакция в первой сессии не завершилась


-- 1
SELECT SUM(rating) FROM pizzeria;
-- 2
SELECT SUM(rating) FROM pizzeria;

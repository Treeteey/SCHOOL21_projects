--установка уровня изоляции для обеих сессий 
SET SESSION CHARACTERISTICS AS TRANSACTION  ISOLATION LEVEL READ COMMITTED;
--проверка уровня изоляции
SHOW TRANSACTION ISOLATION LEVEL;

-- 1
BEGIN;
-- 2
BEGIN;
-- 1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
-- 2 
COMMIT;
-- после коммита во второй сессии данные для первой сессии тоже изменились,
-- хотя транзакция в первой сессии не завершилась

-- 1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 1
COMMIT;



-- 1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
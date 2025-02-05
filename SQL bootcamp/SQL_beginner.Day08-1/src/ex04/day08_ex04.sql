--установка уровня изоляции для обеих сессий 
SET SESSION CHARACTERISTICS AS TRANSACTION  ISOLATION LEVEL SERIALIZABLE;
--проверка уровня изоляции
SHOW TRANSACTION ISOLATION LEVEL;

-- 1
BEGIN;
-- 2
BEGIN;
-- 1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 2
UPDATE pizzeria SET rating = 3.0 WHERE name = 'Pizza Hut';
-- 2 
COMMIT;
-- при уровне изоляции SERIALIZABLE после коммита во второй сессии данные 
-- для первой сессии не изменились, они изменяться только после завершения
-- текущей транзакции в первой сессии
-- 1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 1
COMMIT;



-- 1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
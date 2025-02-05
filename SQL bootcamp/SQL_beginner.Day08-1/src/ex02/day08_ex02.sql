--установка уровня изоляции для обеих сессий 
SET SESSION CHARACTERISTICS AS TRANSACTION  ISOLATION LEVEL REPEATABLE READ;
--проверка уровня изоляции
SHOW TRANSACTION ISOLATION LEVEL;

-- 1
BEGIN;
-- 2
BEGIN;
-- 1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- 1
UPDATE pizzeria SET rating = 4.0 WHERE name = 'Pizza Hut';
-- 2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
-- 1
COMMIT;
-- во сторой сессии появилась ошибка:
-- ОШИБКА:  не удалось сериализовать доступ из-за параллельного изменения

-- 2 
COMMIT;
-- автоматически выводится ROLLBACK
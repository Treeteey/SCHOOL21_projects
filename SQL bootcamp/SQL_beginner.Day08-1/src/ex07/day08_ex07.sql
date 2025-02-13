--установка уровня изоляции для обеих сессий 
SET SESSION CHARACTERISTICS AS TRANSACTION  ISOLATION LEVEL READ COMMITTED;
--проверка уровня изоляции
SHOW TRANSACTION ISOLATION LEVEL;

-- 1
BEGIN;
-- 2
BEGIN;

-- 1
UPDATE pizzeria SET rating = 3.9 WHERE id = 1;
-- 2
UPDATE pizzeria SET rating = 4.4 WHERE id = 2;

-- 1
UPDATE pizzeria SET rating = 5 WHERE id = 2;
-- в первой сессии каретка перешла на новую строку в ожидании
-- изменения во второй сессии, так как изначально во второй 
-- сессии проводились изменения в строке с id = 2
-- поэтому текущий UPDATE находится в режиме ожидания коммита во второй сессии

-- 2
UPDATE pizzeria SET rating = 1 WHERE id = 1;
-- после этой команды в первой сессии успешно завершился второй UPDATE 1
-- однако во второй сессии появилась ошибка: 
    -- ОШИБКА:  обнаружена взаимоблокировка
    -- ПОДРОБНОСТИ:  Процесс 8828 ожидает в режиме ShareLock блокировку "транзакция 920"; заблокирован процессом 17376.
    -- Процесс 17376 ожидает в режиме ShareLock блокировку "транзакция 921"; заблокирован процессом 8828.
    -- ПОДСКАЗКА:  Подробности запроса смотрите в протоколе сервера.
    -- КОНТЕКСТ:  при изменении кортежа (0,29) в отношении "pizzeria"
-- 1
COMMIT;
-- 2 
COMMIT;

-- 1
SELECT * FROM pizzeria WHERE id = 1 OR id = 2;
-- 2
SELECT * FROM pizzeria WHERE id = 1 OR id = 2;

-- в итоге изменения в первой сессии применились нормально
-- а во второй откатились ROLLBACK - автоматически выводится после ошибки взаимоблокировки
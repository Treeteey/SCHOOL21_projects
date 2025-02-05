-- в обоих сессиях
SHOW TRANSACTION ISOLATION LEVEL;

-- read committed

--1)
BEGIN;
--2)
BEGIN;
--1) 
UPDATE pizzeria SET rating = 4.0 WHERE name = 'Pizza Hut';
--2)
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
-- во второй сессии должна зависнуть команда на пустой строке рисунок ex01_0
--1)
COMMIT;
-- во второй сессии должна отвиснуть команда и появится UPDATE 1 в пустой строке
-- рисунок ex01_1

--1) первая сессия покажет 4.0
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
--2) вторая сессия покажет 3.6
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
-- рисунок ex01_2


--2)
COMMIT;

--1) первая сессия покажет 3.6
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
--2) вторая сессия покажет 3.6
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
-- рисунок ex01_3

CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer DEFAULT 10) -- DEFAULT 9 нужно при WHERE id <= pstop, тогда будет выводиться до 10 числа
RETURNS TABLE (numbers NUMERIC) AS $$
BEGIN
    RETURN QUERY WITH RECURSIVE fibonacci_series(id, value, prev_value) AS (
        SELECT
            1 AS id,
            1::NUMERIC AS value,  -- первое значение Фибоначчи
            0::NUMERIC AS prev_value  -- начальное предыдущее значение
        UNION ALL
        SELECT
            id + 1,
            value + prev_value,
            value
        FROM fibonacci_series
        WHERE value + prev_value < pstop  -- условие для ограничения количества шагов рекурсии
    )
    SELECT value FROM fibonacci_series;
END;
$$ LANGUAGE plpgsql;


select * from fnc_fibonacci(20);
-- select * from fnc_fibonacci();

-- DROP FUNCTION fnc_fibonacci(pstop integer)
-- в postgresql результат запроса должен быть куда то присвоен!
-- Так как PL/pgSQL предназначен для процедурного программирования, все операторы SELECT, 
-- которые не возвращают результаты непосредственно (через RETURN), должны либо сохранять
-- результаты в переменную, либо использовать их для какой-то другой операции.

-- 1) первый вариант
CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr numeric[]) RETURNS numeric AS $$
DECLARE
	-- результат сохраняется в эту переменную и возвращается RETURN
	result numeric;
BEGIN
    SELECT min($1[i]) INTO result FROM generate_subscripts($1, 1) g(i);
	RETURN result;
END;
$$ LANGUAGE plpgsql;

-- 2) второй вариант
-- CREATE FUNCTION func_minimum(VARIADIC arr numeric[]) 
-- -- return only one number
-- RETURNS numeric AS $$
-- 	--g(i) - is an alias for result set from function call and returned value
-- 	--min($1[i]) - aggregate min function over array provided as first parameter with subscript i
--     SELECT min($1[i]) FROM generate_subscripts($1, 1) g(i);
-- $$ LANGUAGE SQL;


-- DROP FUNCTION func_minimum(VARIADIC arr numeric[]);


SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);
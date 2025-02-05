CREATE FUNCTION fnc_persons_female() 
-- RETURNS TABLE - add REAL table columns - MUST MATCH the structure of table
RETURNS TABLE (id bigint, name varchar, age integer, gender varchar, address varchar) AS $$ -- $$ means begin of function body
BEGIN
	-- return result of SELECT statement!
	RETURN QUERY SELECT * FROM person p WHERE p.gender = 'female';
END;
$$ LANGUAGE plpgsql;	 

CREATE FUNCTION fnc_persons_male() 
RETURNS TABLE (id bigint, name varchar, age integer, gender varchar, address varchar) AS $$
BEGIN
	RETURN QUERY SELECT * FROM person p WHERE p.gender = 'male';
END;
$$ LANGUAGE plpgsql;	 

-- SELECT * FROM fnc_persons_male();
-- SELECT * FROM fnc_persons_female();
DROP FUNCTION fnc_persons_female(), fnc_persons_male() ;

CREATE OR REPLACE FUNCTION fnc_persons(pgender varchar DEFAULT 'female')
RETURNS TABLE (id bigint, name varchar, age integer, gender varchar, address varchar) AS $$
BEGIN
	IF pgender = 'male' THEN
		RETURN QUERY SELECT * FROM person p WHERE p.gender = 'male';
	ELSE 
		RETURN QUERY SELECT * FROM person p WHERE p.gender = 'female';
	END IF;
END;
$$ LANGUAGE plpgsql;	 

-- select *
-- from fnc_persons(pgender := 'male');

select *
from fnc_persons();


-- DROP FUNCTION fnc_persons(pgender varchar);
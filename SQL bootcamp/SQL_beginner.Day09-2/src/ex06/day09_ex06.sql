		-- DEFAULT - means if i dont add argument to function it takes default value
		-- foo() = foo('Dmitriy', 500, '2022-01-08');

CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(pperson varchar DEFAULT 'Dmitriy', 
												   pprice numeric DEFAULT 500,
												   pdate date DEFAULT '2022-01-08')
-- return only pizzeria names
RETURNS TABLE (name varchar) AS $$
BEGIN
	RETURN QUERY 
		WITH pizzerias_visited AS
			(SELECT DISTINCT pi.name AS pizzeria_name, pi.id AS pizzeria_id, p.name, pv.visit_date FROM person_visits pv
			JOIN pizzeria pi ON pi.id = pv.pizzeria_id
			JOIN person p ON p.id = pv.person_id
			WHERE  p.name = pperson AND pv.visit_date = pdate
			ORDER BY p.name, visit_date)	

		SELECT DISTINCT pv1.pizzeria_name FROM pizzerias_visited pv1
		JOIN menu ON menu.pizzeria_id = pv1.pizzeria_id
		WHERE price <= pprice;
END;
$$ LANGUAGE plpgsql;

select * from fnc_person_visits_and_eats_on_date(pprice := 800);

-- select *
-- from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');

-----------------NOT DONE YET
-------- check second way, and ask peers

------------ first way!
-- if R (1,3,3,5,4) AND S (1,2,5,6,7,9)
-- then R-S (3,4)  ?  just use EXCEPT

CREATE VIEW v_symmetric_union AS
	(SELECT person_id 
	 FROM 	(WITH 
			 	R AS
				(SELECT person_id FROM person_visits
				WHERE visit_date = '2022-01-02'),
				S AS
				(SELECT person_id FROM person_visits
				WHERE visit_date = '2022-01-06')

			((SELECT person_id FROM R)
			EXCEPT
			(SELECT person_id FROM S))
			UNION
			((SELECT person_id FROM S)
			EXCEPT
			(SELECT person_id FROM R))) 
	);


------------ second way!
-- if R (1,3,3,5,4) AND S (1,2,5,6,7,9)
-- R-S (1-1, 3-2, 3-5, 5-6, 4-7, 0-9) -> R-S (0,1,-2,-1,-3,-9) ???
	
	
	
-- 	SELECT person_id FROM v_symmetric_union
-- 	 DROP VIEW IF EXISTS v_symmetric_union
	 
	 
	 
	 
	 

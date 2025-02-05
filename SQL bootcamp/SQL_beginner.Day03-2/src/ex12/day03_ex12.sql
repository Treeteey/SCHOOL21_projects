-- 22	6	20	"2022-02-24" - last line in person_order before new INSERTing
-- menu_ id = 19  - greek pizza

-- person_order table
	-- id
	-- person_id
	-- menu_id
	-- order_date
	
WITH new_table AS	
	(SELECT gs.* AS id, 
			person.id AS person_id, 
			(SELECT DISTINCT id FROM menu WHERE pizza_name = 'greek pizza') AS menu_id, 
			DATE'2022-02-25' AS order_date
	 
	 -- make columns with new menu_ids starting from last menu_id + 1 for each person = gs!
	FROM 	generate_series((SELECT MAX(id)+1 AS max_id FROM person_order) ,
							(SELECT (SELECT MAX(id)+1 FROM person_order) + MAX(id) FROM person),
							1) AS gs,
			person
	--connecting new menu_ids to each person id: 23,1 24,2 ... 31,9
	WHERE gs = person.id + (SELECT MAX(id) AS max_id FROM person_order))
	
INSERT INTO person_order
SELECT * FROM new_table;

-- DELETE FROM person_order WHERE id > 22;

--SELECT * FROM person_order
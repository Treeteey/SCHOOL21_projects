--if use expression then '(SELECT ...) AS name' - that expr must be in (...)!
SELECT
	(SELECT name FROM person WHERE id = person_order.person_id) AS name,	
	(SELECT --add new column to output, not to table!   EVERY SELECT means one column!
	 	CASE	--column fills with data depending on condition
	 	WHEN name = 'Denis' THEN TRUE ELSE FALSE --condition
	 	END		--end of condition
	 FROM person 	--where to look for 'name's  for condition
	 WHERE  id = person_order.person_id) 
	 AS check_name	--set name to new column
FROM person_order --we should check person_order columns not person
WHERE order_date = '2022-01-07'
AND (menu_id = '13' OR menu_id = '14' OR menu_id = '18')
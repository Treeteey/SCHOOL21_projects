WITH raw_table AS
	-- DISTINCT probably wrong - what if balance table had two same rows?
	(SELECT DISTINCT
	 		-- left join user = if user table doesnt have id thats in balance
	 		-- this case will create row with empty name
	 		-- same with lastname and currency_name
	 		-- left joins keeps all rows in first table! 
			CASE 
				WHEN u.name IS NOT NULL THEN u.name
				ELSE 'not defined'
			END AS name, 
			CASE 
				WHEN u.lastname IS NOT NULL THEN u.lastname
				ELSE 'not defined'
			END AS lastname,
	 		u.id AS user_id,
			b.money,
			b.type,
			b.updated,
			CASE
				WHEN c.name IS NOT NULL THEN  c.name
				ELSE 'not defined'
			END AS currency_name,
	 		c.id AS currency_id
	FROM balance b
	LEFT JOIN "user" u ON u.id = b.user_id
	LEFT JOIN currency c ON c.id = b.currency_id
	)

SELECT 
	name, 
	lastname, 
	type, 
	SUM(money) AS volume, 
	currency_name,
	-- COALESCE: if select cant return value it sets value to DEFAULT (number after select is 1) 
	COALESCE(
		(SELECT rate_to_usd 
		 FROM currency c
		 WHERE c.name = raw_table.currency_name
		 ORDER BY updated DESC
		 LIMIT 1), 1) AS last_rate_to_usd,
	SUM(money) * COALESCE(
		(SELECT rate_to_usd 
		 FROM currency c
		 WHERE c.name = raw_table.currency_name
		 ORDER BY updated DESC
		 LIMIT 1), 1) AS total_volume_in_usd
FROM raw_table
GROUP BY name, lastname, type, currency_name
ORDER BY name DESC, lastname ASC, type
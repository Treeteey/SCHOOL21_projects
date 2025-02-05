WITH raw_table AS (
SELECT DISTINCT
	u.name as name, 
	u.lastname, 
	c.name AS currency_name,
	-- choose date: if there is currency updated less than balance updated date -> choose closest date on the left
	-- if there is none then choose next currency updated -> choose closest date on the right
	-- по-русски: если есть дата обновления валюты раньше чем текущая дата в балансе, то выбрать ее
	-- если нет то выбрать следующую ближашую дату обновления валюты
	b.money * COALESCE((SELECT rate_to_usd 
			   FROM currency 
			   WHERE b.updated > updated
			   AND b.currency_id = id
			   ORDER BY updated DESC
			   LIMIT 1),
			(SELECT rate_to_usd 
			   FROM currency 
			   WHERE b.updated <= updated
			   AND b.currency_id = id
			   ORDER BY updated ASC
			   LIMIT 1)) AS currency_in_usd
FROM balance b
LEFT JOIN "user" u ON u.id = b.user_id 
--inner join so there wont be not-existing currencies
JOIN currency c ON c.id = b.currency_id)

SELECT
	CASE
		WHEN name IS NOT NULL THEN name
		ELSE 'not defined'
	END AS name,
	CASE
		WHEN lastname IS NOT NULL THEN lastname
		ELSE 'not defined'
	END AS lastname,
	currency_name, currency_in_usd
FROM raw_table
ORDER BY name DESC, lastname ASC, currency_name ASC

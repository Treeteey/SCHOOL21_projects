SELECT missing.missing_date
FROM (SELECT date_trunc('day', dd)::date AS missing_date
  	  FROM generate_series('2022-01-01'::timestamp, 
							'2022-01-10'::timestamp,
							 '1 day'::interval)dd) AS missing
LEFT JOIN (SELECT DISTINCT visit_date FROM person_visits
		   WHERE person_id = 1 OR person_id = 2) AS pv
ON missing.missing_date = pv.visit_date
WHERE pv.visit_date IS NULL
-- first and second select = creating list of dates from 1st to 10th january
-- second need to get access to 'missing_date' column
-- third select creating list of dates when pizzerias were visited by persons 1 and 2
-- left join = to save all days of first table 'missing' and combine to it second table 'pv'
-- if there is no data in second table for some 'missing.missing_date' thats the answer

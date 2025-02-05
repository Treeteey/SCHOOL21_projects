-- SELECT dates.all_dates
-- FROM (SELECT date_trunc('day', dd)::date AS all_dates
--   	  FROM generate_series('2022-01-01'::timestamp, 
-- 							'2022-01-10'::timestamp,
-- 							 '1 day'::interval)dd) AS dates
-- LEFT JOIN (SELECT DISTINCT visit_date FROM person_visits
-- 		   WHERE person_id = 1 OR person_id = 2) AS pv
-- ON dates.all_dates = pv.visit_date
-- WHERE pv.visit_date IS NULL

--common table expressions - creating temporary table for easy understangind and using 
WITH dates AS
		(SELECT date_trunc('day', dd)::date AS all_dates
	 	FROM generate_series('2022-01-01'::timestamp, 
							'2022-01-10'::timestamp,
						 	'1 day'::interval)dd)
							
SELECT dates.all_dates FROM dates
LEFT JOIN (SELECT DISTINCT visit_date FROM person_visits
		   WHERE person_id = 1 OR person_id = 2) AS pv
ON dates.all_dates = pv.visit_date
WHERE pv.visit_date IS NULL
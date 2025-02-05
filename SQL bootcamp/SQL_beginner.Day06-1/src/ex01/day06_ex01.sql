-- WITH amount_orders AS (
-- 		SELECT 
-- 			person_id, 
-- 			pizzeria_id, 
-- 			CASE -- COUNT(*) count rows with same person_id and pizzeria_id!
-- 				WHEN COUNT(*) = 1 THEN 10.5
-- 				WHEN COUNT(*) = 2 THEN 22
-- 				WHEN COUNT(*) > 2 THEN 30
-- 				ELSE 0
-- 			END as discount
-- 		FROM person_order
-- 		JOIN menu ON person_order.menu_id = menu.id
-- 		GROUP BY person_id, pizzeria_id
-- 		)

-- INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
-- SELECT 
-- 	row_number() OVER () AS id,
-- 	ao.person_id,
-- 	ao.pizzeria_id,
-- 	ao.discount
-- FROM amount_orders ao

select count(*) > 0 as check
from person_discounts


-- SELECT * FROM person_discounts

-- row_number() - assign unique sequentional integer to rows starting from 1
-- OVER ()  - defines the window over which the ROW_NUMBER() function operates.
-- in this case for ALL rows (since there's no PARTITION BY clause to divide the rows into subsets).

-- 1) check person_order before
-- SELECT * FROM person_order

-- orders with id = 23...32 should exist according to previous tasks !
-- 2) delete lines from person_order
DELETE FROM person_order WHERE order_date = '2022-02-25';

-- 3) check person_order after
-- SELECT * FROM person_order

-- 4) check menu before
-- SELECT * FROM menu

-- menu 19 with 'greek pizza' should exits!
-- 5) delete lines from menu
DELETE FROM menu WHERE pizza_name = 'greek pizza';

-- 6) check menu after
-- SELECT * FROM menu
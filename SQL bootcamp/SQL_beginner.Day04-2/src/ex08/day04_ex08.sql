--------- to get list of created VIEWS
-- SELECT table_name
-- FROM information_schema.views
-- WHERE table_schema = 'public';

--------- to get list of created MATERIALIZED VIEWS
-- SELECT schemaname, matviewname FROM pg_matviews;


-------- create single string for a drop command , BUT doesnt actually drop views!
-- SELECT 'DROP VIEW ' || string_agg (table_name, ', ') || ' cascade;'
--   FROM information_schema.views
--  WHERE table_schema NOT IN ('pg_catalog', 'information_schema')
--    AND table_name !~ '^pg_';



DROP VIEW IF EXISTS v_generated_dates;
DROP VIEW IF EXISTS v_symmetric_union;
DROP VIEW IF EXISTS v_price_with_discount;
DROP VIEW IF EXISTS v_persons_female;
DROP VIEW IF EXISTS v_persons_male;

DROP MATERIALIZED VIEW IF EXISTS mv_dmitriy_visits_and_eats;

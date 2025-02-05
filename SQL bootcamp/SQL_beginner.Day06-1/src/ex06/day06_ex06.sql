-- sequence - object that generates series of numbers - good for assigning IDs
-- for example it helps to start ID not only from number 1 
-- make periods, etc.
-- SELECT nextval('serial');  -- select next value from sequence




-- this piece of script finds max id in person_discounts table and saves it in start_val variable
--then writes to that variable new incremented number 
--and creates command of creating sequence with that variable
DO $$
DECLARE
  start_val bigint;
BEGIN
  SELECT COALESCE(MAX(id), 0) + 1 INTO start_val FROM person_discounts;
  EXECUTE 'CREATE SEQUENCE seq_person_discounts START WITH ' || start_val;
END
$$;

-- or there is another way:
-- one has to manually find number to start with - if there is 10 rows in table,
-- then sequence must start with 11
-- CREATE SEQUENCE seq_person_discounts  START WITH 11; -- just BRUTE FORCE number

--this alter will add new mechanism of assigning ids based on seq_person_discounts
--so in next rows in person_discounts table, id column data will be extracted from seq_person_discounts
-- which will be calculated each step
ALTER TABLE person_discounts ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');

-- ошибка  !!!
-- Checks for the file day06_ex06.sql
-- - The SQL script looks like below.

--         create sequence seq_person_discounts start 1;
--         alter table person_discounts alter column id set default nextval('seq_person_discounts');
--         select setval('seq_person_discounts', (select count(*)+1 from person_discounts));

-- - The SQL script looks like below.

--       select count(*)=1 as check1,
--           max("start_value") = 1 as check2,
--           max("last_value") > 5 as check3
--       from pg_sequences
--       where sequencename  = 'seq_person_discounts'                     

-- - The result is below (raw ordering should be the same like below)

--     "true" "true" "true"
                   
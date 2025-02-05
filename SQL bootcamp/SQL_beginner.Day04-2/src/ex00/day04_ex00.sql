--views can be created once, then they are saved in database
--executing same VIEW creation script would lead to error

CREATE VIEW v_persons_female AS
	SELECT * FROM person
	WHERE gender = 'female';

CREATE VIEW v_persons_male AS
	SELECT * FROM person
	WHERE gender = 'male';


---------- example using VIEWS and UNION
-- (SELECT v_persons_female.* FROM v_persons_female)
-- UNION 
-- (SELECT v_persons_male.* FROM  v_persons_male)

--------- to get list of created VIEWS execute next script
-- SELECT table_name
-- FROM information_schema.views
-- WHERE table_schema = 'public';


--------- to delete VIEW from DB!
-- DROP VIEW IF EXISTS v_persons_female;
DROP table person_audit;
CREATE TABLE person_audit
(created 	timestamp with time zone 	NOT NULL,
 type_event char 	default 'I' 		NOT NULL,
 row_id 	bigint 	NOT NULL, 							-- person.id
 name 		varchar not null,
 age 		integer not null 			default 10,
 gender 	varchar default 'female' 	not null ,
 address 	varchar);

alter table person_audit add constraint ch_type_event check (type_event in ('I','U','D'));


CREATE FUNCTION fnc_trg_person_insert_audit() RETURNS trigger AS $trg_person_insert_audit$
	BEGIN
		-- now() - to get current time|date
		-- NEW.* - тип данных RECORD. Переменная содержит новую строку базы данных для команд INSERT/UPDATE в триггерах уровня строки. 
		-- означает добавить все данные в person_audit, которые были добавлены в таблицу person
		-- OLD.* все данные которые были удалены из строки
		-- OLD.age возраст из удаленной строки. Столбец age имеется в таблице person
		INSERT INTO person_audit SELECT now(), 'I', NEW.*;
		RETURN NULL;
	END;
$trg_person_insert_audit$ LANGUAGE plpgsql;		

CREATE TRIGGER trg_person_insert_audit
	AFTER INSERT ON person			-- when inserting to person table trigger
	FOR EACH ROW					-- when insert has few rows of insertion so trigger for each row
	EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');

-- when INSERT works in person table, trigger trg_person_insert_audit activates and calls funtion fnc_trg_person_insert_audit()
-- also INSERT data is saved in object NEW and this object in function is inserted to person_audit table


-- SELECT * FROM person;
-- SELECT * FROM person_audit;


















-- create table person
-- ( id bigint primary key ,
--   name varchar not null,
--   age integer not null default 10,
--   gender varchar default 'female' not null ,
--   address varchar
-- );
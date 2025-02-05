-- when UPDATE you can get OLD values before update and NEW values after

CREATE OR REPLACE FUNCTION fnc_trg_person_update_audit() RETURNS trigger AS $trg_person_update_audit$
	BEGIN
		-- OLD.* все данные которые были удалены или заменены на новые
		INSERT INTO person_audit SELECT now(), 'U', OLD.*;
		RETURN NULL;
	END;
$trg_person_update_audit$ LANGUAGE plpgsql;		

CREATE OR REPLACE TRIGGER trg_person_update_audit
	AFTER UPDATE ON person			-- when inserting to person table trigger
	FOR EACH ROW					-- when insert has few rows of insertion so trigger for each row
	EXECUTE FUNCTION fnc_trg_person_update_audit();
	

UPDATE person SET name = 'Bulat' WHERE id = 10; UPDATE person SET name = 'Damir' WHERE id = 10;

-- SELECT * FROM person;
-- SELECT * FROM person_audit;
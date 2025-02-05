-- when DELETE you can get OLD values before deletion

CREATE FUNCTION fnc_trg_person_delete_audit() RETURNS trigger AS $trg_person_delete_audit$
	BEGIN
		-- OLD.* все данные которые были удалены или заменены на новые
		INSERT INTO person_audit SELECT now(), 'D', OLD.*;
		RETURN NULL;
	END;
$trg_person_delete_audit$ LANGUAGE plpgsql;		

CREATE TRIGGER trg_person_delete_audit
	AFTER DELETE ON person
	FOR EACH ROW
	EXECUTE FUNCTION fnc_trg_person_delete_audit();
	

DELETE FROM person WHERE id = 10;

-- SELECT * FROM person;
-- SELECT * FROM person_audit;
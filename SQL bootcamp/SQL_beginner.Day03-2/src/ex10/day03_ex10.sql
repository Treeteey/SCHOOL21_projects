--make sure the changes from exercises 7,8,9 were MADE !!
--выполни все изменения в заданиях 7,8,9 !!
-- сицилийская пицца в menu под номером 20 задание 8

INSERT INTO person_order VALUES ((SELECT MAX(id)+1 FROM person_order), 				--id
								 (SELECT id FROM person WHERE name = 'Denis'), 		--person_id
								 (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),	--menu_id
								 '2022-02-24');
INSERT INTO person_order VALUES ((SELECT MAX(id)+1 FROM person_order), 				--id
								 (SELECT id FROM person WHERE name = 'Irina'), 		--person_id
								 (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),	--menu_id
								 '2022-02-24');

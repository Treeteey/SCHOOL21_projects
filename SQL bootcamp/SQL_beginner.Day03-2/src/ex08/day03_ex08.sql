-- you can insert row of date using subqueries!!!
-- сицилийская пицца в menu под номером 20
insert into menu values((SELECT MAX(id)+1 FROM menu), 
						(SELECT DISTINCT id FROM pizzeria WHERE name = 'Dominos'), 
						'sicilian pizza', 
						900);
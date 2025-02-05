-- create table person_discounts
-- (id bigint primary key,
--  person_id bigint not null,
--  pizzeria_id bigint not null,
--  discount numeric(5, 2),
--  constraint uk_person_discount unique (person_id, pizzeria_id, discount),
--  constraint fk_person_discounts_person_id foreign key (person_id) references person(id),
--  constraint fk_person_discounts_pizzeria_id foreign key (pizzeria_id) references pizzeria(id),
-- )

-- COMMENT ON TABLE person_discounts IS  'Table shows what discount each person gets in different pizzerias';
-- COMMENT ON COLUMN person_discounts.id IS 'ID of current row';
-- COMMENT ON COLUMN person_discounts.person_id IS 'Person id';
-- COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Pizzeria id';
-- COMMENT ON COLUMN person_discounts.discount IS 'Discount in that pizzeria for current person';

  SELECT count(*) = 5 as check
      FROM   pg_description
      WHERE  objoid = 'person_discounts'::regclass    
	  
--comments shown in properties tab of table (right click) - in pgAdmin!
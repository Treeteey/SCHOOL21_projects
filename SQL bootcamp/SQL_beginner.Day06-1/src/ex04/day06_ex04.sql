-- create table person_discounts
-- (id bigint primary key,
--  person_id bigint not null,
--  pizzeria_id bigint not null,
--  discount numeric(5, 2),
--  constraint uk_person_discount unique (person_id, pizzeria_id, discount),
--  constraint fk_person_discounts_person_id foreign key (person_id) references person(id),
--  constraint fk_person_discounts_pizzeria_id foreign key (pizzeria_id) references pizzeria(id),
-- )


-- ALTER TABLE person_discounts
-- 	ADD CONSTRAINT ch_nn_person_id CHECK (person_id is NOT NULL) NOT VALID,
-- 	ADD CONSTRAINT ch_nn_pizzeria_id CHECK (pizzeria_id is NOT NULL) NOT VALID,
-- 	ADD CONSTRAINT ch_nn_discount CHECK (discount is NOT NULL) NOT VALID,

--ошибка!!!
-- 	ALTER COLUMN discount SET DEFAULT 0.00,

-- 	ADD CONSTRAINT ch_range_discount CHECK (discount BETWEEN 0 AND 100);
	
     select count(*) = 4 as check
      from pg_constraint
      where conname in ('ch_nn_person_id','ch_nn_pizzeria_id','ch_nn_discount','ch_range_discount')	

      select column_default::integer = 0 as check
      from information_schema.columns
      where column_name = 'discount' and table_name = 'person_discounts'          
-- create table person_discounts
-- (id bigint primary key,
--  person_id bigint not null,
--  pizzeria_id bigint not null,
--  discount numeric(5, 2),
--  constraint uk_person_discount unique (person_id, pizzeria_id, discount),
--  constraint fk_person_discounts_person_id foreign key (person_id) references person(id),
--  constraint fk_person_discounts_pizzeria_id foreign key (pizzeria_id) references pizzeria(id)
-- --  CONSTRAINT chk_discount_range CHECK (discount BETWEEN 0 AND 100)  -- need in 4 ex
-- )

SELECT count(*) = 1 as check
FROM pg_tables
where tablename = 'person_discounts'
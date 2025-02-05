--индексы нужны для ускорения поиска
--вроде как создают тип сортированные по выбранному столбцу таблицы
--а затем при сравнении < <= >= > методом двоичного дерева проводят
--поиск, вместо сканирования всей таблицы
CREATE INDEX idx_person_visits_person_id ON person_visits (person_id);
CREATE INDEX idx_person_visits_pizzeria_id ON person_visits (pizzeria_id);
CREATE INDEX idx_menu_pizzeria_id ON menu (pizzeria_id);
CREATE INDEX idx_person_order_person_id ON person_order (person_id);
CREATE INDEX idx_person_order_menu_id ON person_order (menu_id);

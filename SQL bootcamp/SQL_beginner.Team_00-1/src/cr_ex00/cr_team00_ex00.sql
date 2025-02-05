CREATE TABLE nodes (
  id SERIAL PRIMARY KEY,
  point1 TEXT NOT NULL,
  point2 TEXT NOT NULL,
  cost INTEGER NOT NULL
 );
 
INSERT INTO nodes (point1, point2, cost) 
VALUES ('a', 'b', 10), 
       ('b', 'a', 10),
       ('a', 'c', 15),
       ('c', 'a', 15),
       ('c', 'b', 35),
       ('b', 'c', 35),
       ('a', 'd', 20),
       ('d', 'a', 20),
       ('d', 'b', 25),
       ('b', 'd', 25),
       ('d', 'c', 30),
       ('c', 'd', 30);

WITH RECURSIVE 
	all_combinations AS(
		SELECT 	point1 AS start_point, 
				point2 AS end_point, 
				ARRAY[point1,point2] AS tour, 
				cost AS total_cost
		FROM nodes
		WHERE point1 = 'a'

		UNION 

		-- ac.tour || n.point2  = concatenation
		SELECT n.point1, n.point2, ac.tour || n.point2, ac.total_cost + n.cost
		FROM nodes n
		JOIN all_combinations ac ON ac.end_point = n.point1
		WHERE n.point2 <> ALL(ac.tour) -- n.point2 NOT IN array "ac.tour"
	),
	-- at first step it finds all routes that start with 'a' : a-b, a-d, a-c   - table1
	-- then unions this with table2 that consist of routes that finished at each point:
	-- from a-b created: a-b-c, a-b-d
	-- from a-d : a-d-b, a-d-c
	-- from a-c : a-c-d, a-c-b
	-- also there must not be repetitive elements!
	
	-- at second iteration it again unions table12 with table3 
	-- which consist of routes that finished at each point:
	-- from a-b-c : a-b-c-d, a-b-c-a wont be added because a is already in array
	-- from a-d-c : a-d-c-b
	-- ... etc
	-- so resulting table would be 	a-b, a-c, a-d   							- table1
	-- 								a-b-c, a-b-d, a-d-b, a-d-c, a-c-d, a-c-b  	- table2
	-- 								a-b-c-d, a-d-c-b ...						- table3
	final_combinations AS (
		SELECT ac.total_cost + n.cost AS total_cost, array_append(ac.tour, 'a') AS tour
		FROM all_combinations ac
		JOIN Nodes n ON ac.end_point = n.point1
		WHERE array_length(ac.tour, 1) = 4 -- find all lines with 5 elements in array: a,b,c,d,a ...
	)

SELECT *
FROM final_combinations
WHERE total_cost = (
    SELECT MIN(total_cost) 
    FROM final_combinations
)



 

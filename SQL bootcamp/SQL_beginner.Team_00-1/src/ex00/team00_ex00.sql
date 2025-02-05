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

WITH RECURSIVE temp(tour, total_cost) AS (
     SELECT string_to_array(start, ',') AS tour,
            total_cost
       FROM r
	  WHERE array_length(string_to_array(start, ','), 1) = 4
),
r(start, total_cost) AS (
     SELECT 'a', 0
      UNION 
     SELECT concat(start, ',', point2),
            cost + total_cost
       FROM r
	  CROSS JOIN nodes
      WHERE point1 = right(r.start, 1)
            AND point2 != SPLIT_PART(r.start, ',', 1)
            AND point2 != SPLIT_PART(r.start, ',', 2)
            AND point2 != SPLIT_PART(r.start, ',', 3)
)

SELECT total_cost + cost AS total_cost,
       array_append(tour, 'a') AS tour
  FROM temp
 CROSS JOIN nodes
 WHERE point1 = tour[4] 
       AND point2 = 'a'
       AND total_cost + cost = (
           SELECT MIN(total_cost + cost) AS total_cost
             FROM temp
            CROSS JOIN nodes
            WHERE point1 = tour[4]
                  AND point2 = 'a')
 ORDER BY total_cost, tour;
 

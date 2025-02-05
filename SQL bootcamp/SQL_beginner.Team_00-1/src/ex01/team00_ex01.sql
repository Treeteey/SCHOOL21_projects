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
 ORDER BY total_cost, tour;

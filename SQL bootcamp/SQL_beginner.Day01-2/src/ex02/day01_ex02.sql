SELECT pizza_name FROM menu
UNION --combine two columns and save only one duplicate if lines equal!
SELECT pizza_name FROM menu
ORDER BY pizza_name
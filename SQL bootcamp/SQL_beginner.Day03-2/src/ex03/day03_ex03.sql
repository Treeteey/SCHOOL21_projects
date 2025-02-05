WITH pizzeria_id_gender AS
		(SELECT pizzeria_id, pe.gender FROM person_visits pv
		JOIN person pe ON pe.id = pv.person_id
		ORDER BY pizzeria_id),
	pizzeria_gender AS
		(SELECT pi.name,  pizzeria_id_gender.gender FROM pizzeria_id_gender
		JOIN pizzeria pi ON pi.id = pizzeria_id_gender.pizzeria_id),
	pizzeria_gender_counts AS
		(SELECT 
		 	name, 
		 	COUNT(CASE WHEN gender = 'male' THEN 1 ELSE NULL END) AS male_count, 
		 	COUNT(CASE WHEN gender = 'female' THEN 1 ELSE NULL END) AS female_count
		FROM pizzeria_gender
		GROUP BY name)
		
SELECT name FROM pizzeria_gender_counts
WHERE male_count != female_count
ORDER BY name
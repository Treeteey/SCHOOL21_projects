WITH 
	person_visit_count AS  
		(SELECT pv.person_id, COUNT(*) AS visit_count
		FROM person_visits pv
		GROUP BY pv.person_id)

SELECT p.name, pvc.visit_count 
FROM person_visit_count pvc
JOIN person p ON p.id = pvc.person_id
ORDER BY pvc.visit_count DESC, p.name
LIMIT 4;


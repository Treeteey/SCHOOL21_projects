(SELECT generated_date FROM v_generated_dates)
EXCEPT
(SELECT DISTINCT visit_date FROM person_visits)
ORDER BY generated_date
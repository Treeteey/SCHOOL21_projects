-- SELECT gs::date FROM generate_series('2022-01-01', '2022-01-31', interval '1 day') as gs;

CREATE VIEW v_generated_dates AS
	(SELECT gs::date AS generated_date 
	 FROM generate_series('2022-01-01', '2022-01-31', interval '1 day') as gs
	 ORDER BY generated_date );
	


-- SELECT generated_date FROM v_generated_dates

-- DROP VIEW IF EXISTS v_generated_dates;


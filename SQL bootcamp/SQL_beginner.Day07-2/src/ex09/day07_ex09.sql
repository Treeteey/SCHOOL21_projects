SELECT 
    address, 
    ROUND(CAST(max(age) AS decimal) - (CAST(min(age) AS decimal)/CAST(max(age) AS decimal)), 2) AS formula,
    ROUND(avg(age),2) AS average,
    CASE
        WHEN ROUND(CAST(max(age) AS decimal) - (CAST(min(age) AS decimal)/CAST(max(age) AS decimal)), 2) > ROUND(avg(age),2) THEN 'true'
        ELSE 'false'
    END AS comparison
FROM person
GROUP BY address
ORDER BY address
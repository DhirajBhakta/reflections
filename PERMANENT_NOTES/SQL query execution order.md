https://devforth.io/blog/sql-query-optimization-understanding-key-principle/

---
FROM
JOIN
WHERE
GROUP BY
HAVING
SELECT  <---
DISTINCT
ORDER BY <-- 
LIMIT

---

First subquery is executed:

GET second highest salary:
```
SELECT max(salary) from employee
WHERE salary < (select max(salary) from employee);
```
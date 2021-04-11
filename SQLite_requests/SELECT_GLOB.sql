-- SQLite
SELECT * FROM Customers WHERE cust_state GLOB '[AM]*' ORDER BY cust_contact LIMIT 1;
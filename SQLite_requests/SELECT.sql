-- SQLite, LIKE
SELECT cust_id, cust_name FROM Customers WHERE cust_name LIKE "%Toy%";
-- SQLite, GLOB
SELECT * FROM Customers WHERE cust_state GLOB '[AM]*' ORDER BY cust_contact LIMIT 2;

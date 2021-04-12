-- -- SQLite,

-- LIKE
-- SELECT cust_id, cust_name
-- FROM Customers
-- WHERE cust_name LIKE "%Toy%";

--  GLOB:
-- SELECT * FROM Customers
-- WHERE cust_state GLOB '[^AM]*' -- not A or M letter
-- /* WHERE cust_email IS NULL -- not A or M letter */
-- ORDER BY cust_contact LIMIT 5;

-- Concatenation, RTRIM
-- SELECT RTRIM(LTRIM(vend_id || ' ' || vend_name || '         '))
-- AS INFORMATION FROM Vendors;

-- INNER JOIN
-- SELECT OrderItems.order_num, order_item, prod_id, quantity, Orders.cust_id FROM OrderItems
-- INNER JOIN Orders
-- ON OrderItems.order_num = Orders.order_num;

-- Calculated field
-- SELECT DISTINCT order_num, -- order_item, quantity, item_price, --  prod_id, quantity, item_price,
-- quantity * item_price AS total_item_price
-- FROM OrderItems
-- WHERE order_num = 20008;

-- FUNCTIONS:
 -- DATE() and TIME()
  -- SELECT DATE('now') AS current_date, strftime('%H:%M:%S') /* TIME() */ AS current_time;
 -- UPPER, LENGTH
    -- SELECT vend_name,
    --        UPPER(vend_name) AS vend_name_upcase,
    --        vend_address,
    --        LENGTH(vend_address)
    -- FROM Vendors
    -- ORDER BY vend_name;

-- DATA comparing
-- SELECT *
-- FROM Orders
-- WHERE CAST(strftime('%m', order_date) as decimal) = 01;
-- OR =>   strftime('%m', order_date) = "01";

-- Summarazing Functions
-- 1:
-- SELECT AVG(prod_price) AS AVG_PRICE,
--        MAX(prod_price) AS MAX_PRICE,
--        MIN(prod_name) AS FIRST_PRODUCT, -- check test Products
--        COUNT(*) AS NUM_OF_PRODUCTS
-- FROM Products;
-- 2: subquery
-- SELECT *
-- FROM Products
-- WHERE prod_price = (SELECT MIN(prod_price) FROM Products);
-- 3: SUM
-- SELECT SUM(quantity) AS ORDERED_NUMBER,
--        SUM(item_price * quantity) AS TOTAL_PRICE
-- FROM OrderItems
-- WHERE order_num = 20005;
-- 4: AVG by unique values (DISTINCT keyword)
SELECT AVG(DISTINCT prod_price) AS AVERAGE_OF_UNIQUE_PRICES
FROM Products
WHERE vend_id = 'DLL01';
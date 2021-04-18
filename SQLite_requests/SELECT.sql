-- -- SQLite,

-- SELECE basics: LIKE
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
-- WHERE strftime('%m', order_date) = "01" AND
--       strftime('%Y', order_date) = "2020"
-- OR =>  CAST(strftime('%m', order_date) as decimal) = 01;

-- *** Data Manipulation Functions and Summarazing Functions ***
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
-- 4. SUBSTR example
-- SELECT UPPER(cust_id) AS ID,
--        UPPER(cust_name) AS NAME,
--        UPPER(cust_contact) AS CONTACT,
--        UPPER(cust_city) AS CITY,
--        UPPER(SUBSTR(cust_contact, 1, 2) || SUBSTR(cust_city, 1, 3)) AS LOGIN
-- FROM Customers
-- ORDER BY cust_id;
-- 4: AVG by unique values (DISTINCT keyword)
-- SELECT AVG(DISTINCT prod_price) AS AVERAGE_OF_UNIQUE_PRICES
-- FROM Products
-- WHERE vend_id = 'DLL01';

-- SELECT MAX(prod_price) AS MaxPrice
-- FROM Products
-- WHERE prod_price < 10; -- WHERE has more priority than MAX

-- *** GROUP BY ***
-- 1.
    -- SELECT vend_id, COUNT() AS NUM_OF_PRODUCTS_PER_VENDOR --, prod_id, COUNT()
    -- FROM Products
    -- -- WHERE prod_price >= 4
    -- GROUP BY vend_id HAVING COUNT() >= 0 AND vend_id GLOB "[BDF]*";
-- 2.
    -- SELECT order_num, SUM(quantity)
    -- FROM OrderItems
    -- GROUP BY order_num
    -- ORDER BY order_num;
-- 3 Challenge from Book:
    -- SELECT vend_id, COUNT(*) AS num_prods
    -- FROM Products
    -- GROUP BY vend_id HAVING COUNT(*) >= 2 AND prod_price >= 4;
-- Number of items (positions) in every orders
    -- SELECT order_num, COUNT() AS NUM_OF_ITEMS_PER_ORDER
    -- FROM OrderItems
    -- GROUP BY order_num
    -- ORDER BY order_num;
-- MIN_PRICE of a vendor's items
    -- SELECT vend_id, MIN(prod_price) as MIN_PRICE
    -- FROM Products
    -- GROUP BY vend_id
    -- ORDER BY MIN_PRICE;
-- Orders having more then 200 total items
    -- SELECT order_num, SUM(quantity)
    -- FROM OrderItems
    -- GROUP BY order_num
    -- HAVING SUM(quantity) >= 100;
--  Total price (>= 1000) for orders by Customers (using INNER JOIN to show cust_id from Orders and cust_name from Customers)
    -- SELECT OrderItems.order_num, SUM(item_price * quantity) AS MONEY_SPENT, Orders.cust_id, Customers.cust_name
    -- FROM OrderItems
    -- INNER JOIN Orders ON OrderItems.order_num = Orders.order_num
    -- INNER JOIN Customers ON Orders.cust_id = Customers.cust_id
    -- GROUP BY OrderItems.order_num HAVING MONEY_SPENT >= 1000;

-- #11, Book: SUBQUERIES
-- 1. OrderItems -> Orders -> Customers
    -- SELECT * FROM Customers
    -- WHERE cust_id IN (SELECT cust_id
    --                   FROM Orders
    --                   WHERE order_num IN (SELECT order_num
    --                                       FROM OrderItems
    --                                       WHERE prod_id = 'RGAN01'));
-- Strange example of a subquery
    -- SELECT cust_name,
    --        cust_state,
    --        cust_id,
    --        (SELECT COUNT(*)
    --         FROM Orders
    --         WHERE Customers.cust_id = Orders.cust_id) AS ORDERS
-- FROM Customers
-- ORDER BY cust_id;
-- Crossjoin (result as INNER JOIN)
    -- SELECT Vendors.vend_id, Products.vend_id, vend_name, prod_name
    -- FROM Vendors, Products
    -- WHERE Vendors.vend_id = Products.vend_id;
-- #12, Book: JOINS
--INNER JOIN
    -- SELECT Vendors.vend_id, vend_name, prod_name, prod_price
    -- FROM Vendors
    -- INNER JOIN Products
    -- ON Vendors.vend_id = Products.vend_id;
 -- CrossJOIN: OrderItems, Products, Vendors
    -- SELECT prod_name, vend_name, prod_price, quantity
    -- FROM OrderItems, Products, Vendors
    -- WHERE Products.vend_id = Vendors.vend_id
    -- AND OrderItems.prod_id = Products.prod_id
    -- AND order_num = 20007;
-- INNER JOIN: OrderItems->Products->Vendors
    -- SELECT prod_name, vend_name, prod_price, quantity, order_num
    -- FROM OrderItems
    -- INNER JOIN Products ON OrderItems.prod_id = Products.prod_id
    -- INNER JOIN Vendors ON Products.vend_id = Vendors.vend_id
    -- WHERE order_num = 20007;

-- #13 Book: Advanced Joins
SELECT cust_id, cust_name, cust_contact
FROM Customers
WHERE cust_name = (SELECT cust_name FROM Customers WHERE
                   cust_contact = 'Jim Jones');


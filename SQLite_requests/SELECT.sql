-- ### SQLite SQL examples ###

-- ### This setting is to follow refferantial constraing ###
PRAGMA foreign_keys = 1;

-- ### Print out SCHEMA definitions for SQLite ###
SELECT sql
FROM sqlite_master;                             -- shows the entire schema: tables, triggers and so on
-- WHERE name = 'Customers';                    -- or particular entity

-- SELECT basics: LIKE
    SELECT cust_id, cust_name
    FROM Customers
    WHERE cust_name LIKE "%Toy%";

--  GLOB:
    SELECT * FROM Customers
    WHERE cust_state GLOB '[^AM]*'      -- the first letter is neither A nor M
    ORDER BY cust_contact LIMIT 5;

-- Concatenation, RTRIM
    SELECT RTRIM(LTRIM(vend_id || ' ' || vend_name || '         '))     -- The last added right part is trimmed
    AS INFORMATION FROM Vendors;

-- Calculated field
    SELECT DISTINCT order_num, -- order_item, quantity, item_price, --  prod_id, quantity, item_price,
    quantity * item_price AS total_item_price
    FROM OrderItems
    -- WHERE order_num = 20008;

-- ### Functions ###
-- DATE() and TIME()
    SELECT DATE('now') AS current_date;
    SELECT strftime('%H:%M:%S') /* TIME() */ AS current_time;
 -- UPPER, LENGTH
    SELECT vend_name,
           UPPER(vend_name) AS vend_name_upcase,
           vend_address,
           LENGTH(vend_address)
    FROM Vendors
    ORDER BY vend_name;

-- DATE comparing
    SELECT *
    FROM Orders
    WHERE strftime('%m', order_date) = "01" AND
          strftime('%Y', order_date) = "2020";
    -- OR =>  CAST(strftime('%m', order_date) as decimal) = 01;

-- ### Data Manipulation Functions and Summarazing Functions ###
-- 1:
    SELECT AVG(prod_price) AS AVG_PRICE,
           MAX(prod_price) AS MAX_PRICE,
           MIN(prod_name) AS FIRST_PRODUCT, -- check test Products
           COUNT(*) AS NUM_OF_PRODUCTS
    FROM Products;

-- 2: Subqueries:
    SELECT *
    FROM Products
    WHERE prod_price = (SELECT MIN(prod_price) FROM Products)
     OR prod_price = (SELECT MAX(prod_price) FROM Products);

-- 3: SUM
    SELECT SUM(quantity) AS ORDERED_NUMBER,
           SUM(item_price * quantity) AS TOTAL_PRICE
    FROM OrderItems
    WHERE order_num = 20005;

-- 4. SUBSTR example
    SELECT UPPER(cust_id) AS ID,
           UPPER(cust_name) AS NAME,
           UPPER(cust_contact) AS CONTACT,
           UPPER(cust_city) AS CITY,
           UPPER(SUBSTR(cust_contact, 1, 2) || SUBSTR(cust_city, 1, 3)) AS LOGIN
    FROM Customers
    ORDER BY cust_id;
-- 4: AVG by unique values (DISTINCT keyword)
    SELECT AVG(DISTINCT prod_price) AS AVERAGE_OF_UNIQUE_PRICES
    FROM Products
    WHERE vend_id = 'DLL01';

    SELECT MAX(prod_price) AS MaxPrice
    FROM Products
    WHERE prod_price < 10; -- WHERE has more priority than MAX

-- ### GROUP BY ###
-- 1. First, WHERE filters the result for all rows. And HAVING filters after grouping
    SELECT vend_id, COUNT(*) AS NUM_OF_PRODUCTS_PER_VENDOR --, prod_id, COUNT()
    FROM Products
        WHERE prod_price >= 4
    GROUP BY vend_id
        HAVING COUNT(*) >= 2 AND vend_id GLOB "[BDF]*";
-- 2.
    SELECT order_num, SUM(quantity)
    FROM OrderItems
    GROUP BY order_num
    ORDER BY order_num;
-- 3 Challenge from Book:
    SELECT vend_id, COUNT(*) AS num_prods
        FROM Products
    GROUP BY vend_id
        HAVING COUNT(*) >= 2 AND prod_price >= 4;
-- Number of items (positions) in every order
    SELECT order_num, COUNT() AS NUM_OF_ITEMS_PER_ORDER
    FROM OrderItems
    GROUP BY order_num
    ORDER BY order_num;

-- MIN_PRICE of a vendor's items
    SELECT vend_id, MIN(prod_price) as MIN_PRICE
    FROM Products
    GROUP BY vend_id
    ORDER BY MIN_PRICE;

-- Orders having more than 200 total items
    SELECT order_num, SUM(quantity)
    FROM OrderItems
    GROUP BY order_num
    HAVING SUM(quantity) >= 100;

-- Print out orders, money spent, customer ID and name for the orders having price more than 1000
-- (use INNER JOIN to show cust_id from Orders and cust_name from Customers)
    SELECT OrderItems.order_num, SUM(item_price * quantity) AS MONEY_SPENT, Orders.cust_id, Customers.cust_name
    FROM OrderItems
        INNER JOIN Orders ON OrderItems.order_num = Orders.order_num
        INNER JOIN Customers ON Orders.cust_id = Customers.cust_id
    GROUP BY OrderItems.order_num
    HAVING MONEY_SPENT >= 1000;

-- #11, Book: SUBQUERIES
-- 1. OrderItems -> Orders -> Customers
-- Print out Customers info who ordered 'RGAN01' product:
    SELECT * FROM Customers
    WHERE cust_id IN (SELECT cust_id
                      FROM Orders
                      WHERE order_num IN (SELECT order_num
                                          FROM OrderItems
                                          WHERE prod_id = 'RGAN01'));
-- Strange example of a subquery
-- FROM Customers executed first. Then outer SELECT processed, and inner SELECT is executed for each customer row
    SELECT cust_name,
        cust_state,
        cust_id,
        (SELECT COUNT(*)
            FROM Orders
            WHERE Customers.cust_id = Orders.cust_id) AS ORDERS
    FROM Customers
    ORDER BY cust_id;


-- #12, Book: JOINS
-- INNER JOIN
-- The request below prints out vendors and products info for the vendors who has products, that is
-- there are products in the Products table.
-- (LEFT JOIN will print out vendors also who has no products)
    SELECT ROW_NUMBER() OVER() ROW_NUM,
           Vendors.vend_id, vend_name, prod_name, prod_price
    FROM Vendors
    INNER JOIN Products
        ON Vendors.vend_id = Products.vend_id
    ORDER BY Vendors.vend_id;

-- Crossjoin (result as INNER JOIN)
    -- SELECT Vendors.vend_id, Products.vend_id, vend_name, prod_name
    -- FROM Vendors, Products
    -- WHERE Vendors.vend_id = Products.vend_id;

 -- INNER JOIN on the same table (use AS):
-- Prints info of Customers twice in a row
    SELECT *
    FROM Customers AS T1
    INNER JOIN Customers
    ON T1.cust_id = Customers.cust_id;

-- INNER JOIN:
-- Print out Product, Vendor and OrderItems info for items of a specific order
-- Vendors->Products->OrderItems
    SELECT P.prod_name, P.prod_price, V.vend_name, OI.quantity, OI.order_num
    FROM Vendors V
    INNER JOIN Products P ON V.vend_id = P.vend_id
    INNER JOIN OrderItems OI ON P.prod_id = OI.prod_id
    WHERE OI.order_num = 20007;

 -- CrossJOIN (the same as INNER above):
    SELECT prod_name, vend_name, prod_price, quantity
    FROM OrderItems, Products, Vendors
    WHERE Products.vend_id = Vendors.vend_id
    AND OrderItems.prod_id = Products.prod_id
    AND order_num = 20007;

-- #13 Book: Advanced Joins
-- 1. Show Customer's Order numbers (LEFT JOIN will print out Customers which haven't done orders yet):
    SELECT C.cust_id, O.order_num
    FROM Customers C
    INNER JOIN Orders O
        ON C.cust_id = O.cust_id
    ORDER BY C.cust_id;

--(+) Count how many Orders every Customer has:
    SELECT C.cust_id, COUNT(order_num) AS NUM_OF_ORDERS
    FROM Customers C
        LEFT JOIN Orders O
        ON C.cust_id = O.cust_id
    GROUP BY C.cust_id
    ORDER BY C.cust_id;

--2. Count in how many Orders a particular Product presents:
-- LEFT JOIN is used to print out Products which are not ordered at all;
-- COUNT(OI.order_num) is used to not count NULLs
    SELECT P.prod_id, P.prod_name, COUNT(OI.order_num) INCLUDED_IN_ORDERS
    FROM Products P
    LEFT JOIN OrderItems OI
        ON P.prod_id = OI.prod_id
    GROUP BY P.prod_id
    ORDER BY P.prod_id;

-- 3. How many Products every Vendor has
    SELECT V.vend_id, V.vend_name, COUNT(P.prod_id) NUM_OF_PRODUCTS
    FROM Vendors V
        LEFT JOIN Products P
        ON V.vend_id = P.vend_id
    GROUP BY V.vend_id
    ORDER BY V.vend_id;

-- #14 Book: UNIONS
-- 1. Example from the book
    -- SELECT cust_name, cust_contact, cust_email
    -- FROM Customers
    -- WHERE cust_state IN ('IL','IN','MI')
    -- UNION ALL
    -- SELECT cust_name, cust_contact, cust_email
    -- FROM Customers
    -- WHERE cust_name = 'Fun4All'
    -- ORDER BY cust_name, cust_contact;
-- 2. Challenges:
    -- SELECT prod_id, quantity
    -- FROM OrderItems
    -- WHERE quantity = 100
    --     UNION
    -- SELECT prod_id, quantity
    -- FROM OrderItems
    -- WHERE prod_id LIKE "BNBG%"
    -- ORDER BY prod_id, quantity;
-- The same with WHERE with OR
    -- SELECT prod_id, quantity
    -- FROM OrderItems
    -- WHERE quantity = 100 OR prod_id LIKE "BNBG%"
    -- ORDER BY prod_id, quantity;
-- UNION from different tables (different fields)
    -- SELECT prod_name FROM Products
    -- UNION
    -- SELECT cust_name FROM Customers
    -- ORDER BY prod_name;

-- #15 Book: INSERT
    -- INSERT INTO Customers(cust_id, cust_name, cust_address,
    -- cust_city, cust_state, cust_zip, cust_country, cust_contact, cust_email)
    -- VALUES ('1000000006',
    -- 'Toy Land',
    -- '123 Any Street',
    -- 'New York',
    -- 'NY',
    -- '11111',
    -- 'USA',
    -- NULL,
    -- NULL);
-- COPY TABLE
    -- CREATE TABLE CustCopy
    --        AS SELECT *
    --           FROM Customers;
-- INSERT values from one to anoter existing(!) table
    -- INSERT INTO CustCopy (cust_id, cust_contact,
    --                     cust_email, cust_name,
    --                     cust_address, cust_city,
    --                     cust_state, cust_zip,
    --                     cust_country)
    --         SELECT cust_id, cust_contact,
    --                 cust_email, cust_name,
    --                 cust_address, cust_city,
    --                 cust_state, cust_zip,
    --                 cust_country
    --         FROM Customers;

-- #16 Book: UPDATE, DELETE
-- 1. Update one field
    -- UPDATE Customers
    -- SET cust_email = 'kim@thetoystore.com'
    -- WHERE cust_id = '1000000005';
-- 2. Update two fields
    -- UPDATE Customers
    -- SET cust_contact = 'Sam Roberts', cust_email = 'sam@toyland.com'
    -- WHERE cust_id = '1000000006';
-- 3. DELETE
    -- DELETE FROM Customers WHERE cust_id = '1000000006';

--#17 Book: CREATE TABLE, ALTER TABLE
    -- ALTER TABLE Vendors ADD COLUMN vend_phone CHAR(20);
    -- ALTER TABLE Vendors DROP vend_phone;
--#18 Book: VIEWS
-- 1. New VIEW:
    -- CREATE VIEW CustomersWithOrders2 AS
    -- SELECT *
    -- FROM Customers
    -- INNER JOIN Orders ON Customers.cust_id = Orders.cust_id;
    -- SELECT *
    -- FROM CustomersWithOrders2;
-- Check that VIEW works:
    -- SELECT * FROM CustomersWithOrders2;

-- ### Referential integrity, CONSTRAINTS, ON DELETE CASCADE
    -- CREATE TABLE departments
    -- ( department_id INTEGER PRIMARY KEY AUTOINCREMENT,
    --   department_name VARCHAR UNIQUE
    -- );
    --
    -- CREATE TABLE employees
    -- ( employee_id INTEGER PRIMARY KEY AUTOINCREMENT,
    --   first_name VARCHAR NOT_NULL,
    --   department_id INTEGER,
    --   CONSTRAINT fk_departments
    --     FOREIGN KEY (department_id)
    --     REFERENCES departments(department_id)
    --     ON DELETE CASCADE
    -- );
    --
    -- INSERT INTO departments (department_name) VALUES ('DEPT1');
    -- INSERT INTO departments (department_name) VALUES ('DEPT4');
    -- INSERT INTO employees (first_name, department_id) VALUES ('Misha2', 6);
    -- INSERT INTO employees (first_name, department_id) VALUES ('Deptless', NULL);
    -- SELECT * FROM employees;
    -- SELECT * FROM departments;
    -- DELETE FROM departments WHERE department_id = 2;
    -- DELETE FROM employees WHERE employee_id BETWEEN 5 AND 12;

    -- ## INNER JOIN departments <-> employees
    -- SELECT employees.department_id, department_name, COUNT(employee_id) AS NUM_OF_EMPLOYEES
    -- FROM employees
    -- INNER JOIN departments ON employees.department_id = departments.department_id
    -- GROUP BY departments.department_id;

    SELECT department_id, COUNT(employee_id) AS NUM_OF_EMPLOYEES
    FROM employees
    GROUP BY department_id;
-- ##################################

-- #20 Book: Transactions
-- BEGIN TRANSACTION;
-- SAVEPOINT delete2;
-- DELETE FROM OrderItems
--     WHERE order_num = 20005;
-- SAVEPOINT delete1;
-- DELETE FROM Orderb
--     WHERE order_num = 12333;
-- COMMIT TRANSACTION;

-- #22 Book: Indexes, Triggers
-- Create INDEX
    -- CREATE INDEX prod_name_IDX
    -- ON Products (prod_name);
-- Create TRIGGER
    -- CREATE TRIGGER customer_state_UP
    --    AFTER INSERT ON Customers
    -- BEGIN
    --     UPDATE Customers
    --     SET cust_state = UPPER(cust_state)
    --     WHERE Customers.cust_id = new.cust_id;
    -- END;
    -- SELECT * FROM Customers;
    -- INSERT INTO Customers VALUES (1, 'NAME', 'TEST_ADDR', 'City', 'ru',  123, 'RUS', 'Contact', 'email@email.ru');
    -- SELECT * FROM Customers;



/**** Employees and managers in one table example ***/
CREATE TABLE employees_VANYA
     ( employee_id INTEGER PRIMARY KEY AUTOINCREMENT,
       hire_date TEXT,
       chief_id INTEGER,
       salary INTEGER,
       CONSTRAINT fk_chif
         FOREIGN KEY (chief_id)
         REFERENCES employees(employee_id)
         ON DELETE CASCADE
    );

INSERT INTO employees_VANYA (hire_date, chief_id, salary)
VALUES ('2017-05-01', 4, 500);

--DROP TABLE employees_VANYA;
-- List all employees
SELECT * FROM employees_VANYA;

--List only employees with managers and which works longer then their managers
SELECT * FROM employees_VANYA as E1
    INNER JOIN employees_VANYA as E2
    ON E1.chief_id = E2.employee_id
WHERE date(E1.hire_date) < date(E2.hire_date);
/***************************************************/
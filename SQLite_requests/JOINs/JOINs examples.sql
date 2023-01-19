-- Create tables containing only numbers
CREATE TABLE T1 (ID INT);
CREATE TABLE T2 (ID INT);

-- Populate tables:
INSERT INTO T1 (ID) VALUES
(1), (7), (1), (6), (5), (null);

INSERT INTO T2 (ID) VALUES
(1), (1), (2), (3), (null), (5);

-- Different JOINs example:

-- 1. CROSS JOIN: prints out full Cartesian product (Decartes):
-- Note: RIGHT and FULL OUTER joins are not supported by SQLite, but can be construct using
SELECT T1.ID AS T1_ID, T2.ID AS T2_ID
FROM T1
CROSS JOIN T2;

-- 2. INNER JOIN:
-- Prints out only (!) rows of CROSS JOIN where the condition is met:
-- Print 24 rows excluding (T1.ID = 5) and (T1.ID IS NULL) since NULL is non-comparable:
SELECT T1.ID AS T1_ID, T2.ID AS T2_ID
    FROM T1
    INNER JOIN T2
    ON T1.ID <> 5
    -- OR T1.ID IS NULL;    -- with this condition, T1.ID IS NULL is covered

-- 3. LEFT JOIN:
-- It prints out rows of CROSS JOIN where the ON condition is met
-- AND the rows containing keys from T1 which weren't appeared before,
-- that is rows which weren't pass the condition (in that case, the columns from T2 are all NULL):

-- Example below prints out 26 rows adding T1.ID = 5 and T1.ID is NULL
SELECT T1.ID AS T1_ID, T2.ID AS T2_ID
    FROM T1
    LEFT JOIN T2
    ON T1.ID <> 5;

-- The ON condition below is always FALSE, so only rows with T1 (left table) IDs are printed out with NULLed T2 fields:
SELECT T1.ID AS T1_ID, T2.ID AS T2_ID
    FROM T1
    LEFT JOIN T2
    ON FALSE;

-- 4. RIGHT JOIN:
-- RIGHT JOIN is not supported by SQLite, but it can be easily modeled with using LEFT JOIN, use T2 first before T1:

-- This prints out 6 rows when T2.ID matched 3 AND the rest rows containing T2 IDs and NULLed T1 fields
SELECT T1.ID AS T1_ID, T2.ID AS T2_ID
    FROM T2
    LEFT JOIN T1
    ON T2.ID = 3
ORDER BY T2.ID, T1.ID ASC;

-- Only rows of T2 with NULLed T1 fields, since condition is always FALSE:
SELECT T1.ID AS T1_ID, T2.ID AS T2_ID
    FROM T2
    LEFT JOIN T1
    ON FALSE;

-- 5. FULL OUTER JOIN:
-- FULL OUTER JOIN is not supported in SQLite. But can be easily modeled using LEFT and RIGHT joins:

-- Example below prints out rows 12 containing IDs from both T1 and T2 which weren't passed the condition.
-- UNION removes duplicates, so UNION ALL is used.
SELECT T1.ID, T2.ID
    FROM T1
    LEFT JOIN T2
    ON FALSE
UNION ALL
SELECT T1.ID, T2.ID
    FROM T2
    LEFT JOIN T1
    ON FALSE;
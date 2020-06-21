

-- 23.
SELECT Product.maker, Product.model, PC.price, speed, ram, hd, cd
FROM Product, PC, (SELECT maker, MAX(price) AS price
                   FROM Product, PC
                   WHERE Product.model = PC.model
                   GROUP BY maker) AS max_price
WHERE Product.model = PC.model AND PC.price = max_price.price AND Product.maker = max_price.maker;


-- 25.
SELECT maker
FROM (SELECT maker
      FROM Product
      INNER JOIN PC ON Product.model = PC.model AND speed >= 750
      GROUP BY maker

      UNION

      SELECT maker
      FROM Product
      INNER JOIN Laptop ON Product.model = Laptop.model AND speed >= 750
      GROUP BY maker) AS makers
GROUP BY maker
HAVING COUNT(1) > 1;

-- 26.
SELECT maker
FROM Product, PC
WHERE Product.model = PC.model AND
      maker IN (SELECT maker
                FROM Product
                WHERE type = 'Printer') AND
      ram = (SELECT MIN(ram) FROM PC) AND
      speed = (SELECT MAX(speed)
               FROM PC
               WHERE ram = (SELECT MIN(ram)
                            FROM PC));

-- Returns all makers that satisfy the condition 
-- SELECT maker
-- FROM 
-- (
--     SELECT min_ram_pcs.model, MAX(min_ram_pcs.speed) AS max_speed
--     FROM PC, (
--         SELECT *
--         FROM PC, (
--             SELECT  MIN(ram) AS min_ram
--             FROM (SELECT printers.maker, speed, ram 
--                     FROM (SELECT DISTINCT maker
--                             FROM Product
--                             WHERE type = 'Printer') AS printers
--                     INNER JOIN (SELECT maker, speed, ram
--                                     FROM Product
--                                     INNER JOIN PC
--                                     ON Product.model = PC.model) AS pcs
--                     ON printers.maker = pcs.maker) AS nonuinque_possible_makers
--             ) AS min_ram
--         WHERE PC.ram = min_ram.min_ram
--     ) AS min_ram_pcs
--     WHERE PC.speed = min_ram_pcs.speed
--     GROUP BY min_ram_pcs.model
-- ) AS min_ram_max_speed_pcs
-- INNER JOIN
-- Product
-- ON min_ram_max_speed_pcs.model = Product.model;

-- Returns a maker that satisfies the condition
-- SELECT maker
-- FROM (SELECT *
--       FROM (SELECT printers.maker, speed, ram
--             FROM (SELECT DISTINCT maker
--                   FROM Product
--                   WHERE type = 'Printer') AS printers
            
--                   INNER JOIN (SELECT maker, speed, ram
--                               FROM Product
--                               INNER JOIN PC
--                               ON Product.model = PC.model) AS pcs
--                   ON printers.maker = pcs.maker) AS nonuinque_possible_makers
--            ) unique_possible_makers
--     ) AS min_ram
-- ORDER BY ram, speed DESC
-- LIMIT 1;

-- 27.
SELECT AVG(price) AS 'avg price'
      FROM (SELECT price
            FROM Product, PC
            WHERE maker = 'A' AND PC.model = Product.model
            
            UNION ALL

            SELECT price
            FROM Product, Laptop
            WHERE maker = 'A' AND Laptop.model = Product.model
      ) AS laptop_pc_prices;

-- 28.
SELECT maker, AVG(hd) AS 'avg hd'
FROM Product, PC
WHERE Product.model = PC.model AND
      maker IN (SELECT maker
                FROM Product
                WHERE type = 'Printer')
GROUP BY maker;

-- 29.

DROP VIEW new_data_view;
CREATE VIEW new_data_view AS
SELECT maker, Product.model, code, speed, ram, hd, price
FROM Product
INNER JOIN (SELECT (MAX(code) + 20) AS code, 
                    model, 
                    MAX(speed) AS speed, 
                    (MAX(ram) * 2) AS ram, 
                    (MAX(hd) * 2) AS hd,
                    '' AS cd,
                    (MAX(price) / 1.5) AS price 
            FROM Laptop
            GROUP BY model) AS new_data
ON Product.model = new_data.model;

INSERT INTO Product
SELECT maker, model + 1000, 'PC'
FROM new_data_view

INSERT INTO PC
SELECT code, model + 1000, speed, ram, hd, '', price
FROM new_data_view

-- 30.

SET @min_hd = (SELECT MIN(hd) FROM PC);
SET @min_ram = (SELECT MIN(ram) FROM PC);

DELETE FROM PC
WHERE ram = @min_ram OR
      hd = @min_hd;
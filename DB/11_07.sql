DROP TABLE book_inventory;
CREATE TABLE book_inventory
(
	id INT ,
	title VARCHAR(100) ,
	author VARCHAR(50) ,
	publication VARCHAR(30),
	pub_year YEAR,
	isbn CHAR(13),
	price INT
);
LOAD DATA LOCAL INFILE 'c:\\data\\book.csv'
INTO TABLE book_inventory FIELDS TERMINATED BY ",";

ALTER TABLE book_inventory 
ADD COLUMN inventory_quantity INT DEFAULT 0;

CREATE TABLE book_copy SELECT * FROM book_inventory;


DESC book_inventory;

ALTER TABLE book_inventory
ADD COLUMN pub_location VARCHAR(20);

UPDATE book_inventory
SET pub_location = 
CASE 
	WHEN price < 20000 THEN 'Seoul Kr'
    WHEN price BETWEEN 20001 AND 30000 THEN 'Busan Kr'
    ELSE 'LosAngelus NA'
END;

SELECT * FROM book_inventory;

ALTER TABLE book_inventory
ADD COLUMN pub_loc_city VARCHAR(20),
ADD COLUMN pub_loc_nation VARCHAR(10);

UPDATE book_inventory
SET pub_loc_city = SUBSTRING_INDEX(pub_location, ' ', 1),
pub_loc_nation = SUBSTRING_INDEX(pub_location, ' ', -1);

ALTER TABLE book_inventory
CHANGE pub_loc_nation pub_loc_nation VARCHAR(20);

UPDATE book_inventory
SET pub_loc_nation = 
CASE
	WHEN pub_loc_nation = 'Kr' THEN 'Korea'
    WHEN pub_loc_nation = 'NA' THEN 'North America'
    ELSE null
END;

UPDATE book_inventory SET inventory_quantity = FLOOR(10 + RAND()*100);
SELECT SUM(inventory_quantity), publication FROM book_inventory GROUP BY publication ORDER BY SUM(inventory_quantity) DESC, pub_loc_nation, pub_loc_city;

CREATE TABLE book_sales
(
	title VARCHAR(50) PRIMARY KEY,
	sales_quantity INT DEFAULT 0,
	sales_price INT DEFAULT 0,
	sales_date DATE
);

LOAD DATA LOCAL INFILE 'c:\\data\\book_sales.csv'
INTO TABLE book_sales FIELDS terminated BY ",";

SELECT SUM(sales_price) * SUM(sales_quantity), title FROM book_sales GROUP BY title HAVING title = '이기적 유전자';

SELECT SUM(sales_price) * SUM(sales_quantity), title FROM book_sales GROUP BY title ORDER BY sales_quantity DESC LIMIT 1;

SELECT SUM(sales_price) * SUM(sales_quantity), title FROM book_sales GROUP BY title ORDER BY sales_quantity ASC LIMIT 1;

SELECT SUM(sales_price) * SUM(sales_quantity) as total, title FROM book_sales 
GROUP BY title HAVING total > 200000;

SELECT SUM(sales_price) * SUM(sales_quantity) as total, title FROM book_sales 
GROUP BY title HAVING total <= 20000;




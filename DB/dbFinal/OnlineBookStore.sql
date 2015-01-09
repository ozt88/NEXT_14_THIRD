SHOW DATABASES;

USE ozt;

CREATE TABLE Customer(
  c_Id INT NOT NULL,
  c_Address VARCHAR(45) NULL,
  c_Phone VARCHAR(45) NULL,
  c_Email VARCHAR(45) NULL,
  c_CellPhone VARCHAR(45) NULL,
  PRIMARY KEY (c_Id)
);
 
CREATE TABLE _Order(
  o_Id INT NOT NULL,
  o_OrderingDate DATE NULL,
  o_PayPlan VARCHAR(45) NULL,
  o_ShippingPhone VARCHAR(45) NULL,
  o_ShippingAddress VARCHAR(45) NULL,
  o_ShippingPlan VARCHAR(45) NULL,
  Customer_c_Id INT NULL,
  ShippingCompany_s_Id INT NULL,
  PRIMARY KEY (o_Id),
  CONSTRAINT `fk_Customer`
    FOREIGN KEY (Customer_c_Id)
    REFERENCES Customer (c_Id)
);

CREATE TABLE Book (
  b_Id INT NOT NULL,
  b_Title VARCHAR(45) NULL,
  b_Author VARCHAR(45) NULL,
  b_PublishDate DATE NULL,
  b_Price INT NULL,
  Publisher_p_Id INT NOT NULL,
  PRIMARY KEY (b_Id)
);

CREATE TABLE Order_has_Book (
  Order_o_Id INT NOT NULL,
  Book_b_Id INT NULL,
  PRIMARY KEY (Order_o_Id, Book_b_Id),
  INDEX `fk_Order_has_Book_Book1_idx` (Book_b_Id ASC),
  INDEX `fk_Order_has_Book_Order1_idx` (Order_o_Id ASC),
  CONSTRAINT `fk_Order_has_Book_Order1`
    FOREIGN KEY (Order_o_Id)
    REFERENCES _Order (o_Id),
  CONSTRAINT `fk_Order_has_Book_Book1`
    FOREIGN KEY (Book_b_Id)
    REFERENCES Book (b_Id)
);

SELECT * FROM Customer;
SELECT * FROM _Order;
SELECT * FROM Book;
SELECT * FROM Order_has_Book;
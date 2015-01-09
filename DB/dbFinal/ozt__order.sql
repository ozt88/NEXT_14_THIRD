CREATE DATABASE  IF NOT EXISTS `ozt` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `ozt`;
-- MySQL dump 10.13  Distrib 5.6.17, for Win64 (x86_64)
--
-- Host: 10.73.43.77    Database: ozt
-- ------------------------------------------------------
-- Server version	5.6.20

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `_order`
--

DROP TABLE IF EXISTS `_order`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `_order` (
  `o_Id` int(11) NOT NULL,
  `o_OrderingDate` date DEFAULT NULL,
  `o_PayPlan` varchar(45) DEFAULT NULL,
  `o_ShippingPhone` varchar(45) DEFAULT NULL,
  `o_ShippingAddress` varchar(45) DEFAULT NULL,
  `o_ShippingPlan` varchar(45) DEFAULT NULL,
  `Customer_c_Id` int(11) DEFAULT NULL,
  `ShippingCompany_s_Id` int(11) DEFAULT NULL,
  PRIMARY KEY (`o_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `_order`
--

LOCK TABLES `_order` WRITE;
/*!40000 ALTER TABLE `_order` DISABLE KEYS */;
INSERT INTO `_order` VALUES (1,'2014-01-01','신용카드','010-2222-3333','경기도 안산시 팔곡동','일반택배',2,1),(2,'2014-01-01','계좌이체','010-2222-3333','경기도 안산시 팕곡동','항공운수',2,2),(3,'2014-01-01','무료','010-3332-4632','서울시 성북구 안암동','특급택배',1,1),(4,'2014-01-01','신용카드','010-2232-1123','부산시 부산구 부산동','빠른배',3,2);
/*!40000 ALTER TABLE `_order` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-01-02 16:47:42

-- MySQL dump 10.15  Distrib 10.0.29-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: 127.0.0.1    Database: 127.0.0.1
-- ------------------------------------------------------
-- Server version	10.1.21-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `CAN_network`
--

DROP TABLE IF EXISTS `CAN_network`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CAN_network` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `CAN_ID` int(10) unsigned NOT NULL,
  `requestedFloor` tinyint(4) NOT NULL,
  `doorState` text NOT NULL,
  `currentFloor` tinyint(4) NOT NULL,
  `dateID` date NOT NULL,
  `timeID` time NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CAN_network`
--

LOCK TABLES `CAN_network` WRITE;
/*!40000 ALTER TABLE `CAN_network` DISABLE KEYS */;
INSERT INTO `CAN_network` VALUES (1,201,1,'close',3,'2017-08-01','22:38:20'),(2,202,2,'close',2,'2017-08-01','22:43:31'),(3,100,3,'',0,'2017-08-01','22:53:34'),(4,100,0,'close',0,'2017-08-01','22:53:39'),(5,100,1,'',0,'2017-08-01','23:06:44'),(6,100,1,'',0,'2017-08-01','23:07:07'),(7,100,1,'',0,'2017-08-01','23:07:19'),(8,100,2,'',0,'2017-08-01','23:07:29'),(9,100,2,'',0,'2017-08-01','23:08:05'),(10,100,2,'',0,'2017-08-01','23:08:43'),(11,100,2,'',0,'2017-08-01','23:09:23'),(12,100,1,'',0,'2017-08-02','00:39:08'),(13,100,3,'',0,'2017-08-02','00:40:24'),(14,100,3,'',0,'2017-08-02','00:42:11'),(15,100,3,'',0,'2017-08-02','11:28:45'),(16,100,3,'',0,'2017-08-02','12:55:15'),(17,100,3,'',0,'2017-08-02','12:57:49'),(18,100,3,'',0,'2017-08-02','12:57:58'),(19,100,3,'',0,'2017-08-02','12:58:03'),(20,100,3,'',0,'2017-08-02','12:58:15');
/*!40000 ALTER TABLE `CAN_network` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `authorized_users`
--

DROP TABLE IF EXISTS `authorized_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `authorized_users` (
  `userID` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(30) NOT NULL,
  `password` varchar(30) NOT NULL,
  PRIMARY KEY (`userID`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `authorized_users`
--

LOCK TABLES `authorized_users` WRITE;
/*!40000 ALTER TABLE `authorized_users` DISABLE KEYS */;
INSERT INTO `authorized_users` VALUES (1,'dinkar','sharma'),(3,'anas','yassin'),(4,'hello','2'),(5,'mike','galle'),(7,'mikel','akl'),(8,'ali','123456');
/*!40000 ALTER TABLE `authorized_users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cFloor_table`
--

DROP TABLE IF EXISTS `cFloor_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cFloor_table` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `currentFloor` int(10) unsigned NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cFloor_table`
--

LOCK TABLES `cFloor_table` WRITE;
/*!40000 ALTER TABLE `cFloor_table` DISABLE KEYS */;
INSERT INTO `cFloor_table` VALUES (1,2);
/*!40000 ALTER TABLE `cFloor_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `elevator_network`
--

DROP TABLE IF EXISTS `elevator_network`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `elevator_network` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `nodeID` int(10) unsigned NOT NULL,
  `requestedFloor` tinyint(3) unsigned NOT NULL,
  `controllerType` text NOT NULL,
  `doorState` text NOT NULL,
  `currentFloor` tinyint(4) NOT NULL,
  `dateID` date NOT NULL,
  `timeID` time NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `elevator_network`
--

LOCK TABLES `elevator_network` WRITE;
/*!40000 ALTER TABLE `elevator_network` DISABLE KEYS */;
INSERT INTO `elevator_network` VALUES (1,100,3,'EC','',0,'2017-08-01','22:49:10'),(2,100,2,'EC','',0,'2017-08-01','22:49:13'),(3,100,1,'EC','',0,'2017-08-01','22:49:16'),(4,100,3,'EC','',0,'2017-08-01','22:49:56'),(5,100,1,'EC','',0,'2017-08-01','22:49:57'),(6,100,2,'FC','',0,'2017-08-01','22:49:57'),(7,100,3,'FC','',0,'2017-08-01','22:49:58'),(8,100,3,'EC','',0,'2017-08-01','22:51:07'),(9,100,3,'EC','',0,'2017-08-01','22:51:59'),(10,100,3,'EC','',0,'2017-08-01','22:53:34'),(11,100,0,'EC','close',0,'2017-08-01','22:53:39'),(12,100,2,'EC','',0,'2017-08-01','22:54:30'),(13,100,2,'EC','',0,'2017-08-01','22:55:35'),(14,100,1,'EC','',0,'2017-08-01','23:06:44'),(15,100,1,'EC','',0,'2017-08-01','23:07:07'),(16,100,1,'EC','',0,'2017-08-01','23:07:19'),(17,100,2,'EC','',0,'2017-08-01','23:07:29'),(18,100,2,'EC','',0,'2017-08-01','23:08:05'),(19,100,2,'EC','',0,'2017-08-01','23:08:43'),(20,100,2,'EC','',0,'2017-08-01','23:09:22'),(21,100,1,'EC','',0,'2017-08-02','00:39:08'),(22,100,3,'EC','',0,'2017-08-02','00:40:24'),(23,100,3,'EC','',0,'2017-08-02','00:42:11'),(24,100,3,'EC','',0,'2017-08-02','11:28:45'),(25,100,3,'EC','',0,'2017-08-02','12:55:15'),(26,100,3,'EC','',0,'2017-08-02','12:57:49'),(27,100,3,'EC','',0,'2017-08-02','12:57:58'),(28,100,3,'EC','',0,'2017-08-02','12:58:03'),(29,100,3,'EC','',0,'2017-08-02','12:58:15');
/*!40000 ALTER TABLE `elevator_network` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `queue_table`
--

DROP TABLE IF EXISTS `queue_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `queue_table` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `nodeID` int(10) unsigned NOT NULL,
  `requestedFloor` tinyint(3) unsigned NOT NULL,
  `doorState` text NOT NULL,
  `currentFloor` tinyint(4) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `queue_table`
--

LOCK TABLES `queue_table` WRITE;
/*!40000 ALTER TABLE `queue_table` DISABLE KEYS */;
INSERT INTO `queue_table` VALUES (3,100,3,'',0),(4,100,1,'',0),(5,100,1,'',0),(6,100,2,'',0),(7,100,3,'',0),(8,100,2,'',0),(9,100,1,'',0),(10,100,2,'',0),(11,100,3,'',0),(12,201,1,'close',3),(13,202,2,'close',2),(14,100,3,'',0),(15,100,2,'',0),(16,100,1,'',0),(17,100,3,'',0),(18,100,1,'',0),(19,100,2,'',0),(20,100,3,'',0),(21,100,3,'',0),(22,100,3,'',0),(23,100,3,'',0),(24,100,0,'close',0),(25,100,1,'',0),(26,100,1,'',0),(27,100,1,'',0),(28,100,2,'',0),(29,100,2,'',0),(30,100,2,'',0),(31,100,2,'',0),(32,100,1,'',0),(33,100,3,'',0),(34,100,3,'',0),(35,100,3,'',0),(36,100,3,'',0),(37,100,3,'',0),(38,100,3,'',0),(39,100,3,'',0);
/*!40000 ALTER TABLE `queue_table` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-08-02 13:06:28

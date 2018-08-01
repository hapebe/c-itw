-- MySQL dump 10.13  Distrib 5.7.21, for Win64 (x86_64)
--
-- Host: localhost    Database: raumbelegung
-- ------------------------------------------------------
-- Server version	5.7.21-log

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
-- Current Database: raumbelegung
--

/*!40000 DROP DATABASE IF EXISTS raumbelegung*/;

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `raumbelegung` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE raumbelegung;

--
-- Table structure for table `arbeitsplaetze`
--

DROP TABLE IF EXISTS arbeitsplaetze;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE arbeitsplaetze (
  apid int(11) NOT NULL AUTO_INCREMENT,
  raumid int(11) NOT NULL,
  PRIMARY KEY (apid),
  KEY fk_arbeitsplaetze_raeume1_idx (raumid),
  CONSTRAINT fk_arbeitsplaetze_raeume1 FOREIGN KEY (raumid) REFERENCES raeume (raumid) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=239 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `arbeitsplaetze`
--

LOCK TABLES arbeitsplaetze WRITE;
/*!40000 ALTER TABLE arbeitsplaetze DISABLE KEYS */;
INSERT INTO arbeitsplaetze (apid, raumid) VALUES (222,25),(223,25),(224,25),(225,25),(226,25),(227,25),(228,25),(229,25),(230,25),(231,25),(232,25),(205,26),(206,26),(207,26),(208,26),(209,26),(210,26),(211,26),(212,26),(213,26),(214,26),(215,26),(216,26),(217,26),(218,26),(219,26),(220,26),(221,26),(233,27),(234,27),(235,27),(236,27),(237,28),(238,28);
/*!40000 ALTER TABLE arbeitsplaetze ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `belegung`
--

DROP TABLE IF EXISTS belegung;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE belegung (
  belegungid int(11) NOT NULL AUTO_INCREMENT,
  mitarbeiterid int(11) DEFAULT NULL,
  computerid int(11) DEFAULT NULL,
  apid int(11) NOT NULL,
  PRIMARY KEY (belegungid),
  UNIQUE KEY computerid_UNIQUE (computerid),
  UNIQUE KEY mitarbeiterid_UNIQUE (mitarbeiterid),
  KEY fk_arbeitsplaetze_mitarbeiter1_idx (mitarbeiterid),
  KEY fk_arbeitsplaetze_computer1_idx (computerid),
  KEY fk_belegung_arbeitsplaetze1_idx (apid),
  CONSTRAINT fk_arbeitsplaetze_computer1 FOREIGN KEY (computerid) REFERENCES computer (computerid) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT fk_arbeitsplaetze_mitarbeiter1 FOREIGN KEY (mitarbeiterid) REFERENCES mitarbeiter (mitarbeiterid) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT fk_belegung_arbeitsplaetze1 FOREIGN KEY (apid) REFERENCES arbeitsplaetze (apid) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=38 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `belegung`
--

LOCK TABLES belegung WRITE;
/*!40000 ALTER TABLE belegung DISABLE KEYS */;
INSERT INTO belegung (belegungid, mitarbeiterid, computerid, apid) VALUES (31,36,43,216),(34,32,NULL,208),(35,34,NULL,237),(36,35,48,238),(37,33,45,216);
/*!40000 ALTER TABLE belegung ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `belegung_lesbar`
--

DROP TABLE IF EXISTS belegung_lesbar;
/*!50001 DROP VIEW IF EXISTS belegung_lesbar*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `belegung_lesbar` AS SELECT 
 1 AS Raum,
 1 AS AP_ID,
 1 AS Vorname,
 1 AS Nachname,
 1 AS PC_Marke,
 1 AS PC_Modell,
 1 AS Netzwerk_Name,
 1 AS RAM_MB,
 1 AS IP_Addr*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `computer`
--

DROP TABLE IF EXISTS computer;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE computer (
  computerid int(11) NOT NULL AUTO_INCREMENT,
  herstellerid int(11) NOT NULL,
  modell varchar(80) NOT NULL,
  ram_mibyte int(11) NOT NULL,
  ipaddr bigint(20) unsigned NOT NULL,
  networkname varchar(60) NOT NULL,
  PRIMARY KEY (computerid),
  UNIQUE KEY ipaddr_UNIQUE (ipaddr),
  UNIQUE KEY networkname_UNIQUE (networkname),
  KEY fk_computer_computerhersteller_idx (herstellerid),
  CONSTRAINT fk_computer_computerhersteller FOREIGN KEY (herstellerid) REFERENCES computerhersteller (herstellerid) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=50 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `computer`
--

LOCK TABLES computer WRITE;
/*!40000 ALTER TABLE computer DISABLE KEYS */;
INSERT INTO computer (computerid, herstellerid, modell, ram_mibyte, ipaddr, networkname) VALUES (43,26,'ThinkCentre Edge',4096,3232240727,'PC10'),(45,26,'ThinkCentre Edge',4096,3232240694,'PC12'),(46,26,'ThinkCentre Edge',4096,3232240763,'PC04'),(47,25,'(Eigenbau)',1024,167772161,'Strange-01'),(48,26,'ThinkCentre Edge',4096,2886755940,'PC102-17'),(49,27,'Vostro V131',8192,3232281109,'nixname');
/*!40000 ALTER TABLE computer ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `computer_lesbar`
--

DROP TABLE IF EXISTS computer_lesbar;
/*!50001 DROP VIEW IF EXISTS computer_lesbar*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `computer_lesbar` AS SELECT 
 1 AS computerid,
 1 AS name,
 1 AS modell,
 1 AS networkname,
 1 AS ram_mibyte,
 1 AS ipaddr,
 1 AS Arbeitsplatz_ID*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `computerhersteller`
--

DROP TABLE IF EXISTS computerhersteller;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE computerhersteller (
  herstellerid int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(60) NOT NULL,
  PRIMARY KEY (herstellerid),
  UNIQUE KEY name_UNIQUE (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `computerhersteller`
--

LOCK TABLES computerhersteller WRITE;
/*!40000 ALTER TABLE computerhersteller DISABLE KEYS */;
INSERT INTO computerhersteller (herstellerid, name) VALUES (27,'Dell'),(28,'HP'),(26,'Lenovo'),(25,'N.N.');
/*!40000 ALTER TABLE computerhersteller ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `freie_ap_raum`
--

DROP TABLE IF EXISTS freie_ap_raum;
/*!50001 DROP VIEW IF EXISTS freie_ap_raum*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `freie_ap_raum` AS SELECT 
 1 AS raumid,
 1 AS Raum,
 1 AS Freie_Arbeitsplaetze*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `freie_arbeitsplaetze`
--

DROP TABLE IF EXISTS freie_arbeitsplaetze;
/*!50001 DROP VIEW IF EXISTS freie_arbeitsplaetze*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `freie_arbeitsplaetze` AS SELECT 
 1 AS apid,
 1 AS raumid,
 1 AS bezeichnung*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `freie_computer`
--

DROP TABLE IF EXISTS freie_computer;
/*!50001 DROP VIEW IF EXISTS freie_computer*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `freie_computer` AS SELECT 
 1 AS computerid,
 1 AS hersteller,
 1 AS modell,
 1 AS networkname,
 1 AS ram_mibyte*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `mitarbeiter`
--

DROP TABLE IF EXISTS mitarbeiter;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE mitarbeiter (
  mitarbeiterid int(11) NOT NULL AUTO_INCREMENT,
  vorname varchar(60) NOT NULL,
  nachname varchar(60) NOT NULL,
  gebdatum date DEFAULT NULL,
  adresse varchar(80) DEFAULT NULL,
  ort varchar(60) DEFAULT NULL,
  plz int(11) DEFAULT NULL,
  PRIMARY KEY (mitarbeiterid)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mitarbeiter`
--

LOCK TABLES mitarbeiter WRITE;
/*!40000 ALTER TABLE mitarbeiter DISABLE KEYS */;
INSERT INTO mitarbeiter (mitarbeiterid, vorname, nachname, gebdatum, adresse, ort, plz) VALUES (31,'Lisa','Leichtfu├ƒ','1983-11-17','Lindenstr. 10','Berlin',10439),(32,'Max','Mustermann','1971-03-25','Karl-Marx-Alle 153','Berlin',12609),(33,'Erika','Musterfrau','1970-10-04','Fritz-Erler-Allee 19C','Berlin',12733),(34,'Lisbeth','Droste-H├╝lshoff','1952-02-02','H├╝ttenweg 11','Berlin',14953),(35,'Melissa','Managerin','1988-08-10','Auenwald 1a','Schildow',16552),(36,'Hans-Peter','Bergner','1976-05-05','Thulestr. 8','Berlin',13189);
/*!40000 ALTER TABLE mitarbeiter ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `mitarbeiter_ohne_ap`
--

DROP TABLE IF EXISTS mitarbeiter_ohne_ap;
/*!50001 DROP VIEW IF EXISTS mitarbeiter_ohne_ap*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `mitarbeiter_ohne_ap` AS SELECT 
 1 AS mitarbeiterid,
 1 AS vorname,
 1 AS nachname,
 1 AS gebdatum,
 1 AS adresse,
 1 AS ort,
 1 AS plz*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `raeume`
--

DROP TABLE IF EXISTS raeume;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE raeume (
  raumid int(11) NOT NULL AUTO_INCREMENT,
  bezeichnung varchar(30) NOT NULL,
  flaeche float NOT NULL,
  PRIMARY KEY (raumid),
  UNIQUE KEY bezeichnung_UNIQUE (bezeichnung)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `raeume`
--

LOCK TABLES raeume WRITE;
/*!40000 ALTER TABLE raeume DISABLE KEYS */;
INSERT INTO raeume (raumid, bezeichnung, flaeche) VALUES (25,'Raum 101',39.7),(26,'Raum 102',81.4),(27,'Raum 111',39.7),(28,'Rezeption',18.5);
/*!40000 ALTER TABLE raeume ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `raeume_ap`
--

DROP TABLE IF EXISTS raeume_ap;
/*!50001 DROP VIEW IF EXISTS raeume_ap*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `raeume_ap` AS SELECT 
 1 AS Raum,
 1 AS flaeche,
 1 AS Arbeitsplaetze,
 1 AS Freie_Arbeitsplaetze*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `volle_raeume`
--

DROP TABLE IF EXISTS volle_raeume;
/*!50001 DROP VIEW IF EXISTS volle_raeume*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `volle_raeume` AS SELECT 
 1 AS raumid,
 1 AS Raum,
 1 AS Freie_Arbeitsplaetze*/;
SET character_set_client = @saved_cs_client;

--
-- Current Database: raumbelegung
--

USE raumbelegung;

--
-- Final view structure for view `belegung_lesbar`
--

/*!50001 DROP VIEW IF EXISTS belegung_lesbar*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW belegung_lesbar AS select raeume.bezeichnung AS Raum,belegung.apid AS AP_ID,mitarbeiter.vorname AS Vorname,mitarbeiter.nachname AS Nachname,computer_lesbar.`name` AS PC_Marke,computer_lesbar.modell AS PC_Modell,computer_lesbar.networkname AS Netzwerk_Name,computer_lesbar.ram_mibyte AS RAM_MB,computer_lesbar.ipaddr AS IP_Addr from ((((belegung left join mitarbeiter on((belegung.mitarbeiterid = mitarbeiter.mitarbeiterid))) join arbeitsplaetze on((belegung.apid = arbeitsplaetze.apid))) join raeume on((arbeitsplaetze.raumid = raeume.raumid))) left join computer_lesbar on((belegung.computerid = computer_lesbar.computerid))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `computer_lesbar`
--

/*!50001 DROP VIEW IF EXISTS computer_lesbar*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW computer_lesbar AS select computer.computerid AS computerid,computerhersteller.`name` AS `name`,computer.modell AS modell,computer.networkname AS networkname,computer.ram_mibyte AS ram_mibyte,concat(((computer.ipaddr & 0xff000000) >> 24),'.',((computer.ipaddr & 0x00ff0000) >> 16),'.',((computer.ipaddr & 0x0000ff00) >> 8),'.',((computer.ipaddr & 0x000000ff) >> 0)) AS ipaddr,belegung.apid AS Arbeitsplatz_ID from ((computer join computerhersteller on((computer.herstellerid = computerhersteller.herstellerid))) left join belegung on((computer.computerid = belegung.computerid))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `freie_ap_raum`
--

/*!50001 DROP VIEW IF EXISTS freie_ap_raum*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW freie_ap_raum AS select raeume.raumid AS raumid,raeume.bezeichnung AS Raum,count(freie_arbeitsplaetze.apid) AS Freie_Arbeitsplaetze from (raeume left join freie_arbeitsplaetze on((raeume.raumid = freie_arbeitsplaetze.raumid))) group by raeume.raumid order by Freie_Arbeitsplaetze desc */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `freie_arbeitsplaetze`
--

/*!50001 DROP VIEW IF EXISTS freie_arbeitsplaetze*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW freie_arbeitsplaetze AS select arbeitsplaetze.apid AS apid,raeume.raumid AS raumid,raeume.bezeichnung AS bezeichnung from (arbeitsplaetze left join raeume on((arbeitsplaetze.raumid = raeume.raumid))) where (not(exists(select belegung.belegungid from belegung where ((arbeitsplaetze.apid = belegung.apid) and (belegung.mitarbeiterid is not null))))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `freie_computer`
--

/*!50001 DROP VIEW IF EXISTS freie_computer*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW freie_computer AS select computer_lesbar.computerid AS computerid,computer_lesbar.`name` AS hersteller,computer_lesbar.modell AS modell,computer_lesbar.networkname AS networkname,computer_lesbar.ram_mibyte AS ram_mibyte from computer_lesbar where (not(exists(select belegung.belegungid from belegung where (belegung.computerid = computer_lesbar.computerid)))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `mitarbeiter_ohne_ap`
--

/*!50001 DROP VIEW IF EXISTS mitarbeiter_ohne_ap*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW mitarbeiter_ohne_ap AS select mitarbeiter.mitarbeiterid AS mitarbeiterid,mitarbeiter.vorname AS vorname,mitarbeiter.nachname AS nachname,mitarbeiter.gebdatum AS gebdatum,mitarbeiter.adresse AS adresse,mitarbeiter.ort AS ort,mitarbeiter.plz AS plz from mitarbeiter where (not(exists(select belegung.belegungid from belegung where (mitarbeiter.mitarbeiterid = belegung.mitarbeiterid)))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `raeume_ap`
--

/*!50001 DROP VIEW IF EXISTS raeume_ap*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW raeume_ap AS select raeume.bezeichnung AS Raum,raeume.flaeche AS flaeche,count(arbeitsplaetze.apid) AS Arbeitsplaetze,(select freie_ap_raum.Freie_Arbeitsplaetze from freie_ap_raum where (raeume.raumid = freie_ap_raum.raumid)) AS Freie_Arbeitsplaetze from (raeume join arbeitsplaetze on((raeume.raumid = arbeitsplaetze.raumid))) group by raeume.raumid */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `volle_raeume`
--

/*!50001 DROP VIEW IF EXISTS volle_raeume*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = cp850 */;
/*!50001 SET character_set_results     = cp850 */;
/*!50001 SET collation_connection      = cp850_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=root@localhost SQL SECURITY DEFINER */
/*!50001 VIEW volle_raeume AS select freie_ap_raum.raumid AS raumid,freie_ap_raum.Raum AS Raum,freie_ap_raum.Freie_Arbeitsplaetze AS Freie_Arbeitsplaetze from freie_ap_raum where (freie_ap_raum.Freie_Arbeitsplaetze = 0) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-07-30 12:01:29

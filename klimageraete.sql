/* Table structure for table `klimageraete` */
DROP TABLE IF EXISTS `klimageraete`;

CREATE TABLE `klimageraete` (
  `uid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Index Number',
  `modellBezeichnung` varchar(255) NOT NULL,
  `kaelteLeistung` int(10) unsigned NOT NULL,
  `stromVerbrauch` int(10) unsigned NOT NULL,
  `breite` int(10) unsigned NOT NULL,
  `hoehe` int(10) unsigned NOT NULL,
  `tiefe` int(10) unsigned NOT NULL,
  `preis` float unsigned NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


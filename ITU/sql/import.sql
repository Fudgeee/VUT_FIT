-- Adminer 4.8.1 MySQL 8.0.27-0ubuntu0.20.04.1 dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

DROP TABLE IF EXISTS `car`;
CREATE TABLE `car` (
  `ID` int unsigned NOT NULL AUTO_INCREMENT,
  `brand` varchar(45) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `drive` varchar(45) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'Diesel',
  `tank` int unsigned NOT NULL DEFAULT '75',
  `seats` int unsigned NOT NULL DEFAULT '4',
  `prevodovka` varchar(45) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'Manuálna',
  `photopath` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `dojezd` int unsigned NOT NULL DEFAULT '100',
  `active` tinyint unsigned NOT NULL DEFAULT '0',
  `class` smallint unsigned NOT NULL DEFAULT '0',
  `najezd` smallint unsigned NOT NULL DEFAULT '15000',
  `state` smallint unsigned NOT NULL DEFAULT '1',
  `lock` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

INSERT INTO `car` (`ID`, `brand`, `drive`, `tank`, `seats`, `prevodovka`, `photopath`, `dojezd`, `active`, `class`, `najezd`, `state`) VALUES
(1,	'BMW M3',	'Diesel',	55,	5,	'Automatická',	'ITUimg/bmw_m3.jpg',	400,	1,	0,	15000,	1),
(2,	'Audi A4',	'Diesel',	75,	5,	'Automatická',	'ITUimg/audi_a4.jpg',	700,	1,	0,	15000,	0),
(3,	'Škoda Scala',	'Diesel',	75,	4,	'Manuálna',	'ITUimg/Skoda_Scala.jpg',	700,	1,	0,	15000,	1),
(4,	'Škoda Fabia',	'Diesel',	80,	5,	'Manuálna',	'ITUimg/skoda_fabia.jpg',	500,	1,	0,	15000,	0),
(5,	'Kia Ceed',	'Diesel',	55,	5,	'Manuálna',	'ITUimg/kia.jpg',	400,	1,	1,	15000,	1),
(6,	'Hyundai Ioniq',	'Elektromobil',	60,	5,	'Automatická',	'ITUimg/hyundai.jpg',	100,	1,	0,	15000,	1),
(7,	'Fiat 500',	'Elektromobil',	60,	2,	'Automatická',	'ITUimg/fiat.jpeg',	100,	1,	1,	15000,	1),
(8,	'Tesla S',	'Diesel',	55,	5,	'Automatická',	'ITUimg/tesla_s.jpg',	400,	1,	2,	15000,	2);

DROP TABLE IF EXISTS `reservation`;
CREATE TABLE `reservation` (
  `ID` int unsigned NOT NULL AUTO_INCREMENT,
  `ID_car` int unsigned NOT NULL,
  `ID_user` int unsigned NOT NULL,
  `datum_rezervacie` datetime NOT NULL,
  `datum_vratenia` datetime NOT NULL,
  `dovod` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT 'Služební jízda',
  `schvalene` int unsigned DEFAULT '0',
  PRIMARY KEY (`ID` DESC),
  KEY `ID_car` (`ID_car`),
  KEY `ID_user` (`ID_user`),
  CONSTRAINT `reservation_ibfk_1` FOREIGN KEY (`ID_car`) REFERENCES `car` (`ID`) ON DELETE CASCADE,
  CONSTRAINT `reservation_ibfk_2` FOREIGN KEY (`ID_user`) REFERENCES `user` (`ID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;


DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `ID` int unsigned NOT NULL AUTO_INCREMENT,
  `email` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `role` varchar(48) NOT NULL DEFAULT 'user',
  `name` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `surname` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `town` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `street` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `pc` varchar(8) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `phone` varchar(16) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `verified` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;


-- 2022-01-18 17:10:39
-- Adminer 4.8.1 MySQL 8.0.27-0ubuntu0.20.04.1 dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

SET NAMES utf8mb4;

DROP TABLE IF EXISTS `autor`;
CREATE TABLE `autor` (
  `ID_titul` varchar(48) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `diskriminant` int unsigned NOT NULL AUTO_INCREMENT,
  `meno` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `priezvisko` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`diskriminant`,`ID_titul`),
  KEY `ID_titul` (`ID_titul`),
  CONSTRAINT `autor_ibfk_1` FOREIGN KEY (`ID_titul`) REFERENCES `titul` (`ID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `autor`;
INSERT INTO `autor` (`ID_titul`, `diskriminant`, `meno`, `priezvisko`) VALUES
('Knight Of Tomorrow',	31,	'Jan',	'Nový'),
('Knight Of Tomorrow',	32,	'Helena',	'Nováková'),
('Harmony With Strength',	33,	'Vladimir',	'Ančovič'),
('Wrong About The Mines',	34,	'Ahmed',	'Levičovič'),
('Duke Of Time',	35,	'Adelá',	'Marková'),
('Chleba',	36,	'Jaroslav',	'Dosvítil'),
('Houska',	38,	'Jan',	'Humer'),
('Houska',	39,	'Lenka',	'Strakatá'),
('Chleba',	40,	'Vladislav',	'Dvořák'),
('Salvy pod plachtami',	42,	'Drahomír',	'Rybníček'),
('Temné dědictví',	43,	'Wilbur',	'Smith'),
('Temné dědictví',	44,	'David',	'Churchill');

DROP TABLE IF EXISTS `hlas`;
CREATE TABLE `hlas` (
  `ID_uzivatel` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ID_titul` varchar(48) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`ID_uzivatel`,`ID_titul`),
  KEY `ID_titul` (`ID_titul`),
  CONSTRAINT `hlas_ibfk_1` FOREIGN KEY (`ID_uzivatel`) REFERENCES `uzivatel` (`ID`) ON DELETE CASCADE,
  CONSTRAINT `hlas_ibfk_2` FOREIGN KEY (`ID_titul`) REFERENCES `titul` (`ID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `hlas`;
INSERT INTO `hlas` (`ID_uzivatel`, `ID_titul`) VALUES
('admin',	'Chleba'),
('distributor',	'Chleba'),
('user1',	'Wrong About The Mines');

DROP TABLE IF EXISTS `knihovna`;
CREATE TABLE `knihovna` (
  `ID` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `popis` varchar(2048) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `adresa` varchar(512) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `oteviraci_doba` varchar(1024) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_as_ci;

TRUNCATE `knihovna`;
INSERT INTO `knihovna` (`ID`, `popis`, `adresa`, `oteviraci_doba`) VALUES
('Knihovna Jiřího Mahena v Brně',	'Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Quisque tincidunt scelerisque libero. Vestibulum erat nulla, ullamcorper nec, rutrum non, nonummy ac, erat. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Aliquam in lorem sit amet leo accumsan lacinia. Etiam neque. Morbi leo mi, nonummy eget tristique non, rhoncus non leo. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Nulla turpis magna, cursus sit amet, suscipit a, interdum id, felis. Nullam faucibus mi quis velit. Fusce tellus odio, dapibus id fermentum quis, suscipit id erat. Duis sapien nunc, commodo et, interdum suscipit, sollicitudin et, dolor. Curabitur vitae diam non enim vestibulum interdum. In sem justo, commodo ut, suscipit at, pharetra vitae, orci. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Proin pede metus, vulputate nec, fermentum fringilla, vehicula vitae, justo. Sed vel lectus. Donec odio tempus molestie, porttitor ut, iaculis quis, sem.',	'Kolaříkova 3, 621 00 Brno-Řečkovice a Mokrá Hora',	'po-ut 8:00-10:00'),
('Městská knihovna v Praze - Stodůlky',	'Nulla quis diam. Etiam commodo dui eget wisi. In rutrum. Aliquam ante. Maecenas libero. Vivamus ac leo pretium faucibus. Duis risus. Itaque earum rerum hic tenetur a sapiente delectus, ut aut reiciendis voluptatibus maiores alias consequatur aut perferendis doloribus asperiores repellat. Mauris metus. Etiam quis quam. Vestibulum erat nulla, ullamcorper nec, rutrum non, nonummy ac, erat. Maecenas fermentum, sem in pharetra pellentesque, velit turpis volutpat ante, in pharetra metus odio a lectus. Praesent id justo in neque elementum ultrices. In rutrum. Praesent id justo in neque elementum ultrices. Quisque tincidunt scelerisque libero. Aliquam ornare wisi eu metus. Sed vel lectus. Donec odio tempus molestie, porttitor ut, iaculis quis, sem. Quisque porta.\n\nDuis condimentum augue id magna semper rutrum. Nullam eget nisl. Nulla quis diam. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Pellentesque sapien. Curabitur bibendum justo non orci. Praesent vitae arcu tempor neque lacinia pretium. Mauris metus. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Morbi leo mi, nonummy eget tristique non, rhoncus non leo. Maecenas ipsum velit, consectetuer eu lobortis ut, dictum at dui. Maecenas sollicitudin. Vestibulum fermentum tortor id mi. Integer tempor. Duis viverra diam non justo. Aenean vel massa quis mauris vehicula lacinia.',	'Kovářova 1615/4, 155 00 Praha 13',	'pondělí	Zavřeno\núterý	9–16\nstředa  Zavřeno\nčtvrtek	13–19\npátek	9–16\nsobota	Zavřeno\nneděle	Zavřeno'),
('Moravská zemská knihovna v Brně',	'Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Quisque tincidunt scelerisque libero. Vestibulum erat nulla, ullamcorper nec, rutrum non, nonummy ac, erat. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Aliquam in lorem sit amet leo accumsan lacinia. Etiam neque. Morbi leo mi, nonummy eget tristique non, rhoncus non leo. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Nulla turpis magna, cursus sit amet, suscipit a, interdum id, felis. Nullam faucibus mi quis velit. Fusce tellus odio, dapibus id fermentum quis, suscipit id erat. Duis sapien nunc, commodo et, interdum suscipit, sollicitudin et, dolor. Curabitur vitae diam non enim vestibulum interdum. In sem justo, commodo ut, suscipit at, pharetra vitae, orci. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Proin pede metus, vulputate nec, fermentum fringilla, vehicula vitae, justo. Sed vel lectus. Donec odio tempus molestie, porttitor ut, iaculis quis, sem.',	'Kounicova 65a, 601 87 Brno-střed',	'po-ut 8:00-11:00'),
('Ústřední knihovna Filozofické fakulty Masarykovy Univerzity',	'Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Quisque tincidunt scelerisque libero. Vestibulum erat nulla, ullamcorper nec, rutrum non, nonummy ac, erat. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Aliquam in lorem sit amet leo accumsan lacinia. Etiam neque. Morbi leo mi, nonummy eget tristique non, rhoncus non leo. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Nulla turpis magna, cursus sit amet, suscipit a, interdum id, felis. Nullam faucibus mi quis velit. Fusce tellus odio, dapibus id fermentum quis, suscipit id erat. Duis sapien nunc, commodo et, interdum suscipit, sollicitudin et, dolor. Curabitur vitae diam non enim vestibulum interdum. In sem justo, commodo ut, suscipit at, pharetra vitae, orci. Nullam lectus justo, vulputate eget mollis sed, tempor sed magna. Proin pede metus, vulputate nec, fermentum fringilla, vehicula vitae, justo. Sed vel lectus. Donec odio tempus molestie, porttitor ut, iaculis quis, sem.',	'Brno, Zahonova 523',	'po-st 8:00-11:00 , ');

DROP TABLE IF EXISTS `objednavka`;
CREATE TABLE `objednavka` (
  `ID` int unsigned NOT NULL AUTO_INCREMENT,
  `ID_knihovna` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ID_uzivatel_distr` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `stav` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT 'vytvořena',
  `datum_zalozenia` datetime DEFAULT NULL,
  `datum_podani` datetime DEFAULT NULL,
  `datum_vyrizeni` datetime DEFAULT NULL,
  PRIMARY KEY (`ID` DESC),
  KEY `ID_knihovna` (`ID_knihovna`),
  KEY `ID_uzivatel_distr` (`ID_uzivatel_distr`),
  CONSTRAINT `objednavka_ibfk_1` FOREIGN KEY (`ID_knihovna`) REFERENCES `knihovna` (`ID`) ON DELETE CASCADE,
  CONSTRAINT `objednavka_ibfk_4` FOREIGN KEY (`ID_uzivatel_distr`) REFERENCES `uzivatel` (`ID`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `objednavka`;
INSERT INTO `objednavka` (`ID`, `ID_knihovna`, `ID_uzivatel_distr`, `stav`, `datum_zalozenia`, `datum_podani`, `datum_vyrizeni`) VALUES
(9,	'Moravská zemská knihovna v Brně',	NULL,	'vytvořena',	'2021-11-18 00:40:03',	NULL,	NULL),
(7,	'Moravská zemská knihovna v Brně',	'distributor',	'odeslano',	'2021-11-18 00:37:46',	'2021-11-18 00:37:51',	NULL),
(5,	'Knihovna Jiřího Mahena v Brně',	'distributor2',	'vyřízeno',	'2021-11-18 00:34:02',	'2021-11-18 00:34:06',	'2021-11-18 00:36:13'),
(4,	'Knihovna Jiřího Mahena v Brně',	'distributor',	'vyřízeno',	'2021-11-17 23:09:03',	'2021-11-17 23:09:11',	'2021-11-17 23:09:23'),
(2,	'Knihovna Jiřího Mahena v Brně',	'distributor',	'vyřízeno',	'2021-11-17 23:06:36',	'2021-11-17 23:07:50',	'2021-11-18 00:32:49'),
(1,	'Knihovna Jiřího Mahena v Brně',	'distributor',	'vyřízeno',	'2021-11-17 23:06:04',	'2021-11-17 23:06:26',	'2021-11-18 00:32:53');

DROP TABLE IF EXISTS `polozka_objednavky`;
CREATE TABLE `polozka_objednavky` (
  `ID_objednavka` int unsigned NOT NULL,
  `ID_titul` varchar(48) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `mnozstvi` int unsigned NOT NULL,
  PRIMARY KEY (`ID_objednavka`,`ID_titul`),
  KEY `ID_titul` (`ID_titul`),
  CONSTRAINT `polozka_objednavky_ibfk_4` FOREIGN KEY (`ID_objednavka`) REFERENCES `objednavka` (`ID`) ON DELETE CASCADE ON UPDATE RESTRICT,
  CONSTRAINT `polozka_objednavky_ibfk_5` FOREIGN KEY (`ID_titul`) REFERENCES `titul` (`ID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `polozka_objednavky`;
INSERT INTO `polozka_objednavky` (`ID_objednavka`, `ID_titul`, `mnozstvi`) VALUES
(1,	'Duke Of Time',	1),
(1,	'Knight Of Tomorrow',	2),
(1,	'Wrong About The Mines',	1),
(2,	'Houska',	1),
(2,	'Wrong About The Mines',	1),
(4,	'Chleba',	1),
(5,	'Chleba',	1),
(7,	'Chleba',	1),
(9,	'Chleba',	1);

DROP TABLE IF EXISTS `poskytuje`;
CREATE TABLE `poskytuje` (
  `ID_titul` varchar(48) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `ID_knihovna` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `mnozstvi` int unsigned NOT NULL DEFAULT '0',
  `vydano` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID_titul`,`ID_knihovna`),
  KEY `ID_knihovna` (`ID_knihovna`),
  CONSTRAINT `poskytuje_ibfk_2` FOREIGN KEY (`ID_knihovna`) REFERENCES `knihovna` (`ID`) ON DELETE CASCADE,
  CONSTRAINT `poskytuje_ibfk_3` FOREIGN KEY (`ID_titul`) REFERENCES `titul` (`ID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `poskytuje`;
INSERT INTO `poskytuje` (`ID_titul`, `ID_knihovna`, `mnozstvi`, `vydano`) VALUES
('Chleba',	'Knihovna Jiřího Mahena v Brně',	1,	0),
('Duke Of Time',	'Knihovna Jiřího Mahena v Brně',	1,	0),
('Houska',	'Knihovna Jiřího Mahena v Brně',	1,	0),
('Knight Of Tomorrow',	'Knihovna Jiřího Mahena v Brně',	2,	2),
('Wrong About The Mines',	'Knihovna Jiřího Mahena v Brně',	2,	0);

DROP TABLE IF EXISTS `spravuje`;
CREATE TABLE `spravuje` (
  `ID_uzivatel` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ID_knihovna` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`ID_uzivatel`,`ID_knihovna`),
  KEY `ID_knihovna` (`ID_knihovna`),
  CONSTRAINT `spravuje_ibfk_1` FOREIGN KEY (`ID_uzivatel`) REFERENCES `uzivatel` (`ID`) ON DELETE CASCADE,
  CONSTRAINT `spravuje_ibfk_2` FOREIGN KEY (`ID_knihovna`) REFERENCES `knihovna` (`ID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `spravuje`;
INSERT INTO `spravuje` (`ID_uzivatel`, `ID_knihovna`) VALUES
('knihovnik1',	'Knihovna Jiřího Mahena v Brně'),
('knihovnik2',	'Městská knihovna v Praze - Stodůlky'),
('knihovnik1',	'Moravská zemská knihovna v Brně'),
('knihovnik2',	'Moravská zemská knihovna v Brně'),
('knihovnik3',	'Ústřední knihovna Filozofické fakulty Masarykovy Univerzity');

DROP TABLE IF EXISTS `titul`;
CREATE TABLE `titul` (
  `ID` varchar(48) NOT NULL,
  `popis` varchar(2048) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `vydavatelstvo` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `zanry` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `tagy` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `datumVydani` date DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `titul`;
INSERT INTO `titul` (`ID`, `popis`, `vydavatelstvo`, `zanry`, `tagy`, `datumVydani`) VALUES
('Chleba',	'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Nunc tincidunt ante vitae massa. Duis risus. Nunc dapibus tortor vel mi dapibus sollicitudin. Aenean id metus id velit ullamcorper pulvinar. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet ut et voluptates repudiandae sint et molestiae non recusandae. Sed ac dolor sit amet purus malesuada congue. Proin mattis lacinia justo. Nullam rhoncus aliquam metus. Aliquam ante. Mauris dictum facilisis augue. Curabitur vitae diam non enim vestibulum interdum. Mauris suscipit, ligula sit amet pharetra semper, nibh ante cursus purus, vel sagittis velit mauris vel metus. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Mauris dolor felis, sagittis at, luctus sed, aliquam non, tellus. Duis viverra diam non justo.',	'My book',	'drama, komedie',	'#naJenise',	'2021-11-15'),
('Duke Of Time',	'Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Curabitur vitae diam non enim vestibulum interdum. Mauris elementum mauris vitae tortor. Ut tempus purus at lorem. Etiam bibendum elit eget erat. Vivamus ac leo pretium faucibus. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Mauris elementum mauris vitae tortor. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Etiam dictum tincidunt diam. Fusce wisi. Pellentesque sapien. Duis risus. Etiam commodo dui eget wisi. Nullam eget nisl. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Duis sapien nunc, commodo et, interdum suscipit, sollicitudin et, dolor.\n\nNunc auctor. Etiam dictum ti',	'Nice books',	'akční',	'',	'2016-01-21'),
('Harmony With Strength',	'Aliquam ornare wisi eu metus. Mauris suscipit, ligula sit amet pharetra semper, nibh ante cursus purus, vel sagittis velit mauris vel metus. Duis condimentum augue id magna semper rutrum. Cras pede libero, dapibus nec, pretium sit amet, tempor quis. Aliquam erat volutpat. Aliquam erat volutpat. Phasellus faucibus molestie nisl. Donec quis nibh at felis congue commodo. Fusce tellus odio, dapibus id fermentum quis, suscipit id erat. Maecenas lorem. Vivamus porttitor turpis ac leo. Vestibulum fermentum tortor id mi. Mauris dolor felis, sagittis at, luctus sed, aliquam non, tellus. Nullam justo enim, consectetuer nec, ullamcorper ac, vestibulum in, elit. Morbi leo mi, nonummy eget tristique non, rhoncus non leo.\n\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Nunc tincidunt ante vitae massa. Duis risus. Nunc dapibus tortor vel mi dapibus sollicitudin. Aenean id metus id velit ullamcorper pulvinar. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet ut et voluptates repudiandae sint et molestiae non recusandae. Sed ac dolor sit amet purus malesuada congue. Proin mattis lacinia justo. Nullam rhoncus aliquam metus. Aliquam ante. Mauris dictum facilisis augue. Curabitur vitae diam non enim vestibulum interdum. Mauris suscipit, ligula sit amet pharetra semper, nibh ante cursus purus, vel sagittis velit mauris vel metus. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Mauris dolor felis, sagittis at, luctus sed, aliquam non, tellus. Duis viverra diam non justo.',	'Black Fox',	'komedie',	'#topSeler',	'2017-06-09'),
('Houska',	'Integer malesuada. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Morbi leo mi, nonummy eget tristique non, rhoncus non leo. Mauris dictum facilisis augue. Nunc auctor. Morbi scelerisque luctus velit. Morbi imperdiet, mauris ac auctor dictum, nisl ligula egestas nulla, et sollicitudin sem purus in lacus. Curabitur vitae diam non enim vestibulum interdum. Phasellus enim erat, vestibulum vel, aliquam a, posuere eu, velit. Aenean placerat. Praesent dapibus. Nunc dapibus tortor vel mi dapibus sollicitudin. Maecenas lorem. Duis condimentum augue id magna semper rutrum. Aliquam erat volutpat. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet ut et voluptates repudiandae sint et molestiae non recusandae. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.',	'Pekařství',	'Pečivo',	'#naJenise',	'2010-02-17'),
('Knight Of Tomorrow',	'Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Curabitur vitae diam non enim vestibulum interdum. Mauris elementum mauris vitae tortor. Ut tempus purus at lorem. Etiam bibendum elit eget erat. Vivamus ac leo pretium faucibus. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Mauris elementum mauris vitae tortor. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Etiam dictum tincidunt diam. Fusce wisi. Pellentesque sapien. Duis risus. Etiam commodo dui eget wisi. Nullam eget nisl. Duis ante orci, molestie vitae vehicula venenatis, tincidunt ac pede. Duis sapien nunc, commodo et, interdum suscipit, sollicitudin et, dolor.\n\nNunc auctor. Etiam dictum tincidunt diam. Vestibulum fermentum tortor id mi. In enim a arcu imperdiet malesuada. Morbi scelerisque luctus velit. Integer rutrum, orci vestibulum ullamcorper ultricies, lacus quam ultricies odio, vitae placerat pede sem sit amet enim. Sed vel lectus. Donec odio tempus molestie, porttitor ut, iaculis quis, sem. Aliquam id dolor. Nullam rhoncus aliquam metus. Nunc auctor. Integer imperdiet lectus quis justo. Fusce suscipit libero eget elit. Nulla est. Nunc auctor. Ut tempus purus at lorem. Duis bibendum, lectus ut viverra rhoncus, dolor nunc faucibus libero, eget facilisis enim ipsum id lacus.',	'Moravia',	'Akční, Fantasy',	'#new',	'1995-04-30'),
('Salvy pod plachtami',	'Salvy pod plachtami jsou příběhem soupeření mezi Francií a Velkou Británií o vládu nad moři a oceány. Nepřátelství mezi oběma zeměmi, které se zrodilo koncem vlády Ludvíka XIV., pokračovalo ve válce o dědictví rakouské, v sedmileté válce a vrcholilo, když se Francie zařadila po bok amerických kolonií, které zahájily proti Británii válku za svou nezávislost. Bojovalo se ve Středomoří, u západních břehů Francie, v Antilách, u kanadských i severoamerických břehů a v Indickém oceánu. Řadové lodě sváděly bitvy u Toulonu a Menorky, u mysu Finisterre, u ostrova Ouessant a skalisek Cardinaux, v zálivu Chesapeake, kde se Francouzi podstatnou měrou přičinili o vítězství USA u ostrovů Saintes či u Cuddalore a francouzská Marine Royale v těchto bojích byla důstojným soupeřem Royal Navy.',	'Drahomír Rybníček - vyd.Akcent',	'Naučná',	'#piráti',	'2017-06-07'),
('Temné dědictví',	'Válka je u konce a Hitler mrtev. Saffron Courtney a její milovaný manžel Gerhard jen o vlásek unikli smrti. Po návratu do Keni je však nečeká žádná idylka. Mladí muži, kteří bojovali ve „válce bílého muže“, zjistili, že si tím nevysloužili ani uznání, ani lepší práci. Potlačovaná touha po svobodě se dere na povrch a neštítí se násilí.',	'Alpress',	'Literatura světová, Dobrodružné, Romány',	'',	'2021-11-12'),
('Wrong About The Mines',	'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Nunc tincidunt ante vitae massa. Duis risus. Nunc dapibus tortor vel mi dapibus sollicitudin. Aenean id metus id velit ullamcorper pulvinar. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet ut et voluptates repudiandae sint et molestiae non recusandae. Sed ac dolor sit amet purus malesuada congue. Proin mattis lacinia justo. Nullam rhoncus aliquam metus. Aliquam ante. Mauris dictum facilisis augue. Curabitur vitae diam non enim vestibulum interdum. Mauris suscipit, ligula sit amet pharetra semper, nibh ante cursus purus, vel sagittis velit mauris vel metus. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Mauris dolor felis, sagittis at, luctus sed, aliquam non, tellus. Duis viverra diam non justo.\n\nInteger malesuada. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Morbi leo mi, nonummy eget tristique non, rhoncus non leo. Mauris dictum facilisis augue. Nunc auctor. Morbi scelerisque luctus velit. Morbi imperdiet, mauris ac auctor dictum, nisl ligula egestas nulla, et sollicitudin sem purus in lacus. Curabitur vitae diam non enim vestibulum interdum. Phasellus enim erat, vestibulum vel, aliquam a, posuere eu, velit. Aenean placerat. Praesent dapibus. Nunc dapibus tortor vel mi dapibus sollicitudin. Maecenas lorem. Duis condimentum augue id magna semper rutrum. Aliquam erat volutpat. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet ut et voluptates repudiandae sint et molestiae non recusandae. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.',	'Nové hrady',	'drama',	'',	'2020-05-06');

DROP TABLE IF EXISTS `uzivatel`;
CREATE TABLE `uzivatel` (
  `ID` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `heslo` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `role` varchar(20) CHARACTER SET ascii COLLATE ascii_general_ci NOT NULL DEFAULT 'registrated',
  `meno` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `priezvisko` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `telefon` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `email` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `mesto` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `ulice` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `psc` varchar(6) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `uzivatel`;
INSERT INTO `uzivatel` (`ID`, `heslo`, `role`, `meno`, `priezvisko`, `telefon`, `email`, `mesto`, `ulice`, `psc`) VALUES
('admin',	'$2y$10$kgqqAYodf9qr9TX7ueihbuiKibxif1ZWwDhNqIJ.1lpAtD49m98rG',	'admin',	'Václav',	'Klaus',	'236585969',	'admin@fbi.com',	'Berlín',	'Aloisova',	'49494'),
('distributor',	'$2y$10$YcLHJsKqsRY3LRkoeeHwWeCJ7aVkY1muISREJBXVNtHvQ0ffwO5Wy',	'distributor',	'Pavel',	'Novák',	'65482245',	'4doorsNoMore@gmail.com',	'Hradec Králové',	'Jezerní 12',	'32457'),
('distributor2',	'$2y$10$VYGhhJVU/RnyxQyZj/MQ5eXPRp68GNAzwTqmUVSnNaz6is/6PWvde',	'distributor',	'Pepa',	'Pašerák',	'112',	'1234@noEmail.here',	'',	'',	''),
('knihovnik1',	'$2y$10$9sRPv/QCTbiWVqTz1N7xTOsi6PRtg7aoQ1BCXN9Qysl8y0GdwlCU.',	'knihovnik',	'Andrej',	'Hárlej',	'123456789',	'kokos12@fit.cz',	'Brno',	'Sokolská 395',	'45912'),
('knihovnik2',	'$2y$10$cvhBe/Ac0TZB/EapZSs7veKtnhTwys/eypBYYT8c895yOoiZ5UubS',	'knihovnik',	'Jan',	'Nepomuk',	'546985623',	'nepomuk@gmail.com',	'Praha',	'Nová 321',	'95596'),
('knihovnik3',	'$2y$10$NT9McQqILW1cBlJgfmRuS.d0DoNbLXQela.PVhh5DNz0aDvQFUDUK',	'knihovnik',	'Lojza',	'Kraus',	'6028452165',	'Kraus@Lojza.cz',	'Brnel',	'',	''),
('user1',	'$2y$10$A5G1mdCug7cPSJpltoiWRuoRriTGGenuZeqTsz11GctP5oTbkIJ6q',	'registered',	'Pavla',	'Heřmanová',	'954546445',	'email@email.cz',	'Moravské Budějice',	'Nové sady 12/5',	'65874'),
('user2',	'$2y$10$O6RT.KY3LGQEk/1uiQj8b.JRgUQm7YiZn/cshS9rosOn933URE.aW',	'registered',	'Franta',	'Uživatel',	'654665533',	'bfu@alik.cz',	'Soběslav',	'Námořní 321',	'54981'),
('user3',	'$2y$10$vtftdfjygWxAnTGhLTebm.yHBJQOQzMayGeMGGkga0iW6Cg/8XPpy',	'registered',	'Jaroslav',	'Malý',	'',	'',	'',	'',	''),
('user4',	'$2y$10$Efw4AfGYlmEhv8TIBw0kY.7CgCHLxEVVKTHUmeYT8GD7JqGWDWZTC',	'registered',	'Jana',	'Máchalová',	'',	'',	'',	'',	'');

DROP TABLE IF EXISTS `vypujcka`;
CREATE TABLE `vypujcka` (
  `ID` int unsigned NOT NULL AUTO_INCREMENT,
  `ID_titul` varchar(48) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `ID_uzivatel` varchar(48) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ID_knihovna` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stav` varchar(16) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT 've frontě',
  `prodlouzeni` tinyint NOT NULL DEFAULT '0',
  `datum_vytvoreno` datetime NOT NULL,
  `datum_vydano` datetime DEFAULT NULL,
  `datum_vraceno` datetime DEFAULT NULL,
  PRIMARY KEY (`ID`),
  KEY `ID_uzivatel` (`ID_uzivatel`),
  KEY `ID_knihovna` (`ID_knihovna`),
  KEY `ID_titul` (`ID_titul`),
  CONSTRAINT `vypujcka_ibfk_1` FOREIGN KEY (`ID_uzivatel`) REFERENCES `uzivatel` (`ID`) ON DELETE CASCADE,
  CONSTRAINT `vypujcka_ibfk_3` FOREIGN KEY (`ID_knihovna`) REFERENCES `knihovna` (`ID`) ON DELETE CASCADE,
  CONSTRAINT `vypujcka_ibfk_4` FOREIGN KEY (`ID_titul`) REFERENCES `titul` (`ID`) ON UPDATE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

TRUNCATE `vypujcka`;
INSERT INTO `vypujcka` (`ID`, `ID_titul`, `ID_uzivatel`, `ID_knihovna`, `stav`, `prodlouzeni`, `datum_vytvoreno`, `datum_vydano`, `datum_vraceno`) VALUES
(1,	'Chleba',	'user1',	'Knihovna Jiřího Mahena v Brně',	'vráceno',	0,	'2021-11-17 23:32:48',	'2021-11-18 00:34:32',	'2021-11-18 00:34:41'),
(2,	'Chleba',	'distributor',	'Knihovna Jiřího Mahena v Brně',	'zamítnuto',	0,	'2021-11-18 00:32:29',	NULL,	NULL),
(3,	'Chleba',	'knihovnik1',	'Knihovna Jiřího Mahena v Brně',	'vráceno',	0,	'2021-11-18 00:33:30',	'2021-11-18 00:34:48',	'2021-11-18 00:34:50'),
(4,	'Knight Of Tomorrow',	'user4',	'Knihovna Jiřího Mahena v Brně',	'rezervováno',	0,	'2021-11-18 00:45:01',	NULL,	NULL);

-- 2021-11-18 01:34:34

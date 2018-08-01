-- diese Sammlung von SQL-Befehlen lässt sich auch als Skript ausführen:
-- mysql -u root -p < raumbelegung-daten.sql

USE raumbelegung;

-- User anlegen, der nur abfragen darf; das aber von überall
-- (keine Struktur-Befehle; kein INSERT, kein DELETE)
DROP USER IF EXISTS 'zuschauer'@'%';
CREATE USER zuschauer@'%' IDENTIFIED BY 'passwort';
GRANT SELECT ON raumbelegung.* TO zuschauer@'%';
SHOW GRANTS FOR zuschauer@'%';

-- User anlegen, der Belegungen bearbeiten darf 
-- (sonst nur lesen, wenn überhaupt)
DROP USER IF EXISTS planer@'%';
CREATE USER planer@'%' IDENTIFIED BY 'passwort';
GRANT SELECT, UPDATE, INSERT, DELETE ON raumbelegung.belegung TO planer@'%';
GRANT SELECT ON raumbelegung.belegung_lesbar TO planer@'%';
SHOW GRANTS FOR planer@'%';


-- Geht sowas? Ja!
-- SHOW CREATE VIEW belegung_lesbar;


-- erstmal alle Daten löschen (aufpassen wegen foreign keys...):
DELETE FROM belegung;
DELETE FROM arbeitsplaetze;
DELETE FROM computer;
DELETE FROM computerhersteller;
DELETE FROM raeume;
DELETE FROM mitarbeiter;

INSERT INTO computerhersteller (name) VALUES
('N.N.'),
('Lenovo'),
('Dell'),
('HP');

-- Prozedur zum "menschenlesbaren" Einfügen von Computern:
DROP PROCEDURE IF EXISTS insert_computer;
DELIMITER //
CREATE PROCEDURE insert_computer(hersteller VARCHAR(60), modell VARCHAR(80), networkname VARCHAR(60), ram INT, ip1 BIGINT, ip2 BIGINT, ip3 BIGINT, ip4 BIGINT)
BEGIN
	INSERT INTO computer (herstellerid, modell, ram_mibyte, ipaddr, networkname)
	VALUES
	(
		(SELECT herstellerid FROM computerhersteller WHERE `name`=hersteller), 
		modell, 
		ram, 
		ip1*16777216 + ip2*65536 + ip3*256 + ip4,
		networkname
	);
END
//
DELIMITER ;

CALL insert_computer('Lenovo', 'ThinkCentre Edge', 'PC10', 4096, 192, 168, 20, 87);
CALL insert_computer('Lenovo', 'ThinkCentre Edge', 'PC09', 4096, 192, 168, 20, 76);
CALL insert_computer('Lenovo', 'ThinkCentre Edge', 'PC12', 4096, 192, 168, 20, 54);
CALL insert_computer('Lenovo', 'ThinkCentre Edge', 'PC04', 4096, 192, 168, 20, 123);
CALL insert_computer('N.N.', '(Eigenbau)', 'Strange-01', 1024, 10, 0, 0, 1);
CALL insert_computer('Lenovo', 'ThinkCentre Edge', 'PC102-17', 4096, 172, 16, 102, 100);
CALL insert_computer('Dell', 'Vostro V131', 'nixname', 8192, 192, 168, 178, 21);
-- Check (der View wurde im MySQL-Schema angelegt):
SELECT * FROM computer_lesbar;

INSERT INTO raeume (bezeichnung, flaeche) VALUES
('Raum 101', 39.7),
('Raum 102', 81.4),
('Raum 111', 39.7),
('Rezeption', 18.5);

-- 17 Arbeitsplätze in Raum 102 erstellen:
INSERT INTO arbeitsplaetze (raumid) VALUES
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 102'));
-- 11 Arbeitsplätze in Raum 101 erstellen:
INSERT INTO arbeitsplaetze (raumid) VALUES
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 101'));
-- 4 Arbeitsplätze in Raum 111 erstellen:
INSERT INTO arbeitsplaetze (raumid) VALUES
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 111')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 111')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 111')),
((SELECT raumid FROM raeume WHERE bezeichnung='Raum 111'));
-- 2 Arbeitsplätze in der Rezeption erstellen:
INSERT INTO arbeitsplaetze (raumid) VALUES
((SELECT raumid FROM raeume WHERE bezeichnung='Rezeption')),
((SELECT raumid FROM raeume WHERE bezeichnung='Rezeption'));

-- Check:
-- SELECT raeume.bezeichnung AS Raum, COUNT(apid) AS Anzahl_Arbeitsplaetze FROM arbeitsplaetze NATURAL JOIN raeume GROUP BY raumid;

-- dieser View wurde schon im MySQL-Schema angelegt:
SELECT 'Freie Arbeitsplaetze pro Raum:' AS Liste;
SELECT * FROM freie_ap_raum;

INSERT INTO mitarbeiter (vorname, nachname, gebdatum, adresse, ort, plz) VALUES 
('Lisa', 'Leichtfuß', '1983-11-17', 'Lindenstr. 10', 'Berlin', 10439),
('Max', 'Mustermann', '1971-03-25', 'Karl-Marx-Alle 153', 'Berlin', 12609),
('Erika', 'Musterfrau', '1970-10-04', 'Fritz-Erler-Allee 19C', 'Berlin', 12733),
('Lisbeth', 'Droste-Hülshoff', '1952-02-02', 'Hüttenweg 11', 'Berlin', 14953),
('Melissa', 'Managerin', '1988-08-10', 'Auenwald 1a', 'Schildow', 16552),
('Hans-Peter', 'Bergner', '1976-05-05', 'Thulestr. 8', 'Berlin', 13189);


-- Belegungen anlegen
DROP PROCEDURE IF EXISTS insert_belegung;
DELIMITER //
CREATE PROCEDURE insert_belegung(pRaum VARCHAR(30), pVorname VARCHAR(60), pNachname VARCHAR(60), pNetworkname VARCHAR(60))
BEGIN
	-- wenn ich das hier nicht initialisiere, bekomme ich eben kein NULL 
	-- aus dem Sub-Query, weil gar keine Ergebnisse anfallen:
	SET @freie_apid = NULL;
	-- dies gibt mir genau einen Datensatz aus dem View,
	-- oder NULL - dann gibt es einen (korrekten) Fehler, weil kein Platz frei ist
	SET @dummy = (
		SELECT @freie_apid:=`apid` AS Freier_Arbeitsplatz FROM freie_arbeitsplaetze WHERE raumid=(
			SELECT raumid FROM raeume WHERE bezeichnung=pRaum
		) LIMIT 0,1
	);
	INSERT INTO belegung (mitarbeiterid, computerid, apid) VALUES
	(
		(SELECT mitarbeiterid FROM mitarbeiter WHERE vorname=pVorname AND nachname=pNachname),
		(SELECT computerid FROM computer WHERE networkname=pNetworkname),
		@freie_apid
	);
END
//
DELIMITER ;

CALL insert_belegung('Raum 102', 'Hans-Peter', 'Bergner', 'PC10');
-- das haut nicht mehr hin, wenn jeder Mitarbeiter nur einmal in belegung vorkommen darf...
-- CALL insert_belegung('Raum 102', 'Hans-Peter', 'Bergner', NULL);
CALL insert_belegung('Raum 102', NULL, NULL, 'Strange-01');
CALL insert_belegung('Raum 102', 'Lisa', 'Leichtfuß', 'PC09');
CALL insert_belegung('Raum 102', 'Max', 'Mustermann', NULL);
-- das funktioniert erwartungsgemäß nicht, wenn nur 4 Arbeitsplätze im Raum 102 vorhanden sind:
-- CALL insert_belegung('Raum 102', 'Erika', 'Musterfrau', NULL);
-- die Rezeption voll belegen:
CALL insert_belegung('Rezeption', 'Lisbeth', 'Droste-Hülshoff', NULL);
CALL insert_belegung('Rezeption', 'Melissa', 'Managerin', 'PC102-17');
-- das funktioniert erwartungsgemäß nicht:
-- CALL insert_belegung('Rezeption', 'Erika', 'Musterfrau', NULL);

SELECT 'Arbeitsplatz-Belegung, Rohdaten:' AS Liste;
SELECT * FROM belegung;

SELECT 'Arbeitsplatz-Belegung, lesbar:' AS Liste;
SELECT * FROM belegung_lesbar;

-- dieser View wurde schon im MySQL-Schema angelegt:
SELECT 'Freie Arbeitsplaetze nach Raum:' AS Liste;
SELECT * FROM freie_ap_raum;

-- dieser View wurde schon im MySQL-Schema angelegt:
SELECT 'Voll belegte Raeume:' AS Liste;
SELECT Raum FROM volle_raeume;

-- dieser View wurde schon im MySQL-Schema angelegt:
SELECT 'Mitarbeiter ohne Arbeitsplatz:' AS Liste;
SELECT * FROM mitarbeiter_ohne_ap;

-- dieser View wurde schon im MySQL-Schema angelegt:
SELECT 'Freie Computer:' AS Liste;
SELECT * FROM freie_computer;

-- Test: ein verwendeter Computer wird gelöscht - funktioniert das Löschen der Belegung?
SELECT 'PC09 wird gelöscht; macht das Frau Leichtfuß Arbeitsplatz-los?' AS Computer_Loeschen;
DELETE FROM computer WHERE networkname='PC09';
SELECT 'Mitarbeiter ohne Arbeitsplatz:' AS Liste;
SELECT * FROM mitarbeiter_ohne_ap;
SELECT 'Freie Arbeitsplaetze pro Raum:' AS Liste;
SELECT * FROM freie_ap_raum;



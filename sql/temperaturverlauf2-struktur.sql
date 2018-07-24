-- Zeile-Kommentare in SQL fangen mit "--" an.
# funktioniert allerdings bei MySQL auch, 
/* ebenso wie: */

-- diese Sammlung von SQL-Befehlen lässt sich auch als Skript ausführen:
-- mysql -u root -p < temperaturverlauf-struktur2.sql

-- GROß GESCHRIEBENE WÖRTER sind (My)SQL-Schlüsselwörter bzw. Befehle - 
-- - sie müssen zum Funktionieren nicht zwingend groß geschrieben werden.
DROP DATABASE IF EXISTS temperaturverlauf;
CREATE DATABASE temperaturverlauf;

USE temperaturverlauf;

-- 2. Normalform ()
DROP TABLE IF EXISTS koordinaten;
CREATE TABLE koordinaten (
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	plz INT NOT NULL,
	ort VARCHAR(80) NOT NULL,
	laenge FLOAT NOT NULL,
	breite FLOAT NOT NULL
);
-- zeigt die Struktur der Tabelle an (Spalten, deren Typen und Attribute):
SHOW FIELDS FROM koordinaten;

INSERT INTO koordinaten 
(plz, ort, laenge, breite)
VALUES
(10000, 'Berlin', 13.3, 52.533),
(83043, 'Bad Aibling', 12.017, 47.867),
(03025, 'Calau', 13.958, 51.75)
;


DROP TABLE IF EXISTS daten;
CREATE TABLE daten (id INT NOT NULL PRIMARY KEY AUTO_INCREMENT);
ALTER TABLE daten ADD COLUMN ort INT NOT NULL;
ALTER TABLE daten ADD COLUMN datum DATE NOT NULL;
ALTER TABLE daten ADD COLUMN uhrzeit TIME NOT NULL;
ALTER TABLE daten ADD COLUMN temperatur FLOAT NOT NULL;

-- zeigt die Struktur der Tabelle an (Spalten, deren Typen und Attribute):
SHOW FIELDS FROM daten;

INSERT INTO daten 
(ort, datum, uhrzeit, temperatur) 
VALUES 
((SELECT id FROM koordinaten WHERE ort='Berlin'), '2018-07-24', '09:00', 23.4),
((SELECT id FROM koordinaten WHERE ort='Berlin'), '2018-07-24', '10:00', 24.8),
((SELECT id FROM koordinaten WHERE ort='Berlin'), '2018-07-24', '14:00', 27.5),
((SELECT id FROM koordinaten WHERE ort='Calau'), '2018-07-24', '14:00', 27.0),
((SELECT id FROM koordinaten WHERE ort='Bad Aibling'), '2018-07-24', '13:00', 24.0)
;


-- FOREIGN KEY definieren (gehört nicht zum Unterrichts-Umfang!)
ALTER TABLE daten 
	ADD 
	CONSTRAINT daten_fk_ort
	FOREIGN KEY (ort)
	REFERENCES koordinaten(id)
	ON DELETE CASCADE
	ON UPDATE CASCADE;
-- ON DELETE CASCADE: wenn ein Ort gelöscht wird, werden alle daten-Einträge von dort mit gelöscht.
-- IN UPDATE CASCADE: wenn ein Ort die ID ändert, wird das in daten übernommen.


SELECT * FROM koordinaten;

SELECT * FROM daten;

-- SELECT aus zwei Tabellen:
SELECT 
--		LPAD(koordinaten.plz, 5, '0') AS PLZ, 
		koordinaten.ort, 
--		daten.datum, 
		daten.uhrzeit, 
	FORMAT(daten.temperatur,1) AS Temp
	FROM koordinaten, daten
	WHERE daten.ort = koordinaten.id
	ORDER by ort, uhrzeit ASC;

-- SELECT mit JOIN:
SELECT koordinaten.ort, uhrzeit, FORMAT(daten.temperatur,1) AS Temp
FROM daten 
JOIN koordinaten ON daten.ort = koordinaten.id;




SELECT '

Ab hier: Umbau auf 3. Normalform, bzw. Ausgliederung der Orte via Referenzierung der PLZ.

' AS Umbau;

-- und jetzt Umbau auf 3. Normalform (Ortsnamen über PLZ)
ALTER TABLE daten DROP FOREIGN KEY daten_fk_ort;
ALTER TABLE daten CHANGE ort koordid INT NOT NULL;

SELECT 'Daten komplett' AS Tabelle;
SELECT * FROM daten;

ALTER TABLE koordinaten DROP COLUMN ort;
ALTER TABLE koordinaten CHANGE id koordid INT;

SELECT 'Koordinaten komplett' AS Tabelle;
SELECT * FROM koordinaten;

CREATE TABLE orte (
	plz INT NOT NULL PRIMARY KEY,
	name VARCHAR(80)
);
INSERT INTO orte (plz, name) VALUES
(10000, 'Berlin'),
(83043, 'Bad Aibling'),
(3025, 'Calau')
;

SELECT 'Orte komplett' AS Tabelle;
SELECT * FROM orte;


-- FOREIGN KEY definieren (gehört nicht zum Unterrichts-Umfang!)
ALTER TABLE koordinaten
	ADD 
	CONSTRAINT koordinaten_fk_plz
	FOREIGN KEY (plz)
	REFERENCES orte(plz)
	ON DELETE CASCADE
	ON UPDATE CASCADE;


SELECT 'Unsere eigentliche "Payload"-Aufgabe: Liste von Orten mit Temperatur:' AS Payload;
-- wenn der Primär- und Fremdschlüssel gleich heißen (hier: koordid und plz), dann kann man NATURAL JOIN benutzen:
SELECT plz, name, laenge, breite, uhrzeit, temperatur FROM daten NATURAL JOIN koordinaten NATURAL JOIN orte ORDER BY name, datum, uhrzeit ASC;

-- jetzt bekommt Calau probehalber eine neue PLZ: 
UPDATE orte SET plz=3222 WHERE name='Calau';

SELECT 'Funktioniert es noch, nachdem Calau eine andere PLZ bekommen hat?' AS FremdSchluesselTest;
SELECT plz, name, laenge, breite, uhrzeit, temperatur FROM daten NATURAL JOIN koordinaten NATURAL JOIN orte ORDER BY name, datum, uhrzeit ASC;


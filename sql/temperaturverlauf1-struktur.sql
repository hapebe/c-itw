-- Zeile-Kommentare in SQL fangen mit "--" an.
# funktioniert allerdings bei MySQL auch, 
/* ebenso wie: */

/* diese Sammlung von SQL-Befehlen lässt sich auch als Skript ausführen:
 *
 
mysql -u root -p < temperaturverlauf1-struktur.sql

 *
 */

-- GROß GESCHRIEBENE WÖRTER sind (My)SQL-Schlüsselwörter bzw. Befehle - 
-- - sie müssen zum Funktionieren nicht zwingend groß geschrieben werden.
DROP DATABASE IF EXISTS temperaturverlauf;
CREATE DATABASE temperaturverlauf;

USE temperaturverlauf;

-- Tabelle "daten": Alles in der 1. Normalform (atomisiert, ohne Wiederholungsgruppen)
DROP TABLE IF EXISTS daten;
DROP TABLE IF EXISTS datten;
CREATE TABLE datten (
	ort VARCHAR(80),
	breite FLOAT,
	laenge FLOAT,
	datum DATE,
	zeit TIME,
	temperatur FLOAT
);
-- Beim Namen der Tabelle vertippt ...
RENAME TABLE datten TO daten;
-- ... und den Primärschlüssel vergessen!
-- FIRST bezieht sich auf die Reihenfolge der Spalten: 
-- obwohl die Spalte id zuletzt definiert wurde, soll sie ganz vorn stehen.
ALTER TABLE daten ADD COLUMN id INT AUTO_INCREMENT NOT NULL PRIMARY KEY FIRST;
-- ach ja: Länge sollte vor der Breite stehen:
ALTER TABLE daten CHANGE breite breite FLOAT AFTER laenge;
-- und Zeit nennen wir Uhrzeit:
ALTER TABLE daten DROP COLUMN zeit;
ALTER TABLE daten ADD COLUMN uhrzeit TIME AFTER datum;
-- sicherstellen, dass immer ein Ort eingegeben werden muss:
ALTER TABLE daten MODIFY ort VARCHAR(80) NOT NULL;

-- zeigt die Struktur der Tabelle an (Spalten, deren Typen und Attribute):
SHOW FIELDS FROM daten;

-- einen ersten Datensatz anlegen:
INSERT INTO daten (
	ort, breite, laenge, datum, uhrzeit, temperatur
) VALUES (
	'Berlin', 52.533, 13.3, '2018-07-24', '10:04', 23.4
);
-- die Zeit korrigieren:
UPDATE daten SET uhrzeit='09:00' WHERE ort='Berlin' AND uhrzeit='10:04';

-- zweiter Datensatz:
INSERT INTO daten (
	ort, breite, laenge, datum, uhrzeit, temperatur
) VALUES (
	'Berlin', 52.533, 13.3, '2018-07-24', '10:00', 24.8
);

-- und noch ein paar Zusatz-Daten, damit wir "sinnvolle" Abfragen machen können:
-- hier benutzen wir "extended insert": die Struktur wird nur einmal angegeben, 
-- aber dann gleich mehrere Datensätze in immer der gleichen Form:
INSERT INTO daten 
(ort, breite, laenge, datum, uhrzeit, temperatur) 
VALUES 
('Hamburg', 53.567, 10.033, '2018-07-24', '09:00', 24.1),
('Hamburg', 53.567, 10.033, '2018-07-24', '10:00', 25.8),
('Bonn', 50.733, 7.1, '2018-07-24', '09:00', 25.3),
('Bonn', 50.733, 7.1, '2018-07-24', '10:00', 26.3),
('Berlin', 53.533, 13.3, '2018-07-24', '13:00', 29.0)
;
-- Der letzte Berlin-Eintrag hat absichtlich eine falsche Breiten-Angabe.

-- an dieser Stelle könnte man auch die Datei staedte.sql ausführen, 
-- dann hätte man SEEEEHR viele Datensätze.

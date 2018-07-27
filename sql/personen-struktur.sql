-- SET character_set_client=CP850;
-- SET character_set_results=CP850;

DROP DATABASE IF EXISTS personen;
CREATE DATABASE personen;

USE personen;

CREATE TABLE pDaten (
	id INT PRIMARY KEY AUTO_INCREMENT,
	vorname VARCHAR(80),
	nachname VARCHAR(80),
	geschlechtid INT NOT NULL
);

CREATE TABLE geschlecht (
	geschlechtid INT NOT NULL AUTO_INCREMENT,
	bezeichnung VARCHAR(30) NOT NULL,
	PRIMARY KEY (geschlechtid),
	UNIQUE KEY uq_bezeichnung(bezeichnung)
);
-- oder UNIQUE INDEX später anlegen:
-- CREATE UNIQUE INDEX bezeichnung ON geschlecht(bezeichnung);
-- SHOW CREATE TABLE geschlecht;
-- SHOW INDEXES FROM geschlecht;

ALTER TABLE pDaten
	ADD CONSTRAINT fk_geschlecht
	FOREIGN KEY (geschlechtid) REFERENCES geschlecht(geschlechtid)
	ON UPDATE CASCADE
	ON DELETE CASCADE
;
-- SHOW CREATE TABLE pDaten;
-- SHOW INDEXES FROM pDaten;

INSERT INTO geschlecht (bezeichnung) VALUES ('weiblich'),('maennlich');
-- INSERT INTO geschlecht (bezeichnung) VALUES ('maennlich');
CHARSET CP850;

SELECT 'Geschlechter:' AS Liste;
SELECT * FROM geschlecht;

INSERT INTO pDaten (vorname, nachname, geschlechtid)
VALUES
('Hans-Peter', 'Bergner', (SELECT geschlechtid FROM geschlecht WHERE bezeichnung='maennlich')),
('Erika', 'Musterfrau', 1)
;
-- dieser Datensatz kann nicht angelegt werden:
-- INSERT INTO pDaten (vorname, nachname, geschlechtid) VALUES ('A.', 'Anders', 3);

-- View anlegen, 
CREATE VIEW netteliste AS SELECT vorname, nachname, geschlecht.bezeichnung FROM pDaten INNER JOIN geschlecht ON geschlecht.geschlechtid=pDaten.geschlechtid;

-- und indirekt einen Datensatz anlegen: (leider nein...)
-- INSERT INTO netteliste (vorname, nachname, bezeichnung) VALUES ('Frida', 'Kahlo', 'weiblich');

DELIMITER //
CREATE PROCEDURE insert_person(vorname VARCHAR(80), nachname VARCHAR(80), gtxt VARCHAR(30))
BEGIN
	INSERT INTO pDaten (vorname, nachname, geschlechtid)
	VALUES
	(vorname, nachname, (SELECT geschlechtid FROM geschlecht WHERE bezeichnung=gtxt));
END
//
DELIMITER ;

CALL insert_person('Frida', 'Kahlo', 'weiblich');
CALL insert_person('Fritz', 'Mann', 'maennlich');
-- das geht immer noch nicht:
-- CALL insert_person('A.', 'Anders', 'kurios');



-- SELECT 'Jetzt sollten eigentlich auch alle Männer aus pDaten verschwinden (ON DELETE CASCADE ...):' AS Delete_Maennlich;
-- DELETE FROM geschlecht WHERE bezeichnung='maennlich';
-- SELECT * FROM netteliste;

-- und jetzt: ein drittes Geschlecht:
INSERT INTO geschlecht (bezeichnung) VALUES ('anders');
CALL insert_person('Conchita', 'Wurst', 'anders');

SELECT 'Personen mit menschenlesbarem Geschlecht:' AS Liste;
SELECT * FROM netteliste;

SELECT 'Jetzt wird ein ganzes Geschlecht (anders) gelöscht:' AS Kaskadiertes_Loeschen;
DELETE FROM geschlecht WHERE bezeichnung='anders';
SELECT * FROM netteliste;

ALTER TABLE pDaten DROP FOREIGN KEY fk_geschlecht;
ALTER TABLE pDaten DROP INDEX fk_geschlecht;
SHOW INDEXES FROM pDaten;
SHOW CREATE TABLE pDaten;


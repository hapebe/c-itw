-- gedacht für die Ausführung auf debian-router (Raum 102, 192.168.20.252)

USE geodaten;

SELECT plz, COUNT(plz) FROM koordinaten GROUP BY plz ORDER BY plz ASC;

SELECT DISTINCT(ort) FROM koordinaten WHERE plz=65510;

USE temperaturverlauf;

-- Alles anzeigen:
-- der folgende Befehl macht eine "Abfrage" von vorher festgelegtem Text, also eigentlich nur eine Text-Ausgabe...
-- SELECT 'Alle Daten:' AS Liste;
-- SELECT * FROM daten;

-- Städte (mit L/B), deren Name mit "B" anfängt:
SELECT 'Orte (mit L/B), deren Name mit "B" anfaengt:' AS Liste;
SELECT ort, breite, laenge FROM daten WHERE ort LIKE 'B%' GROUP BY ort LIMIT 0,10;


SELECT 'Orte, wo die Temperatur um 9:00 Uhr schon hoeher als 25 Grad war:' AS Liste;
-- DISTINCT ergibt immer nur ein Ergebnis pro eindeutigem Wert der Spalte
SELECT DISTINCT(ort) FROM daten WHERE temperatur > 25.0 AND uhrzeit < '09:30';


SELECT 'Orte zwischen dem 50. und 52. Breitengrad:' AS Liste;
-- (lieber nur die ersten 10...)
SELECT ort FROM daten WHERE breite >= 50 AND breite <=52.0 GROUP BY ort LIMIT 0,10;

SELECT 'Wo gab es die hoechste Temperatur?' AS Maximum;
SELECT ort, temperatur FROM daten ORDER BY temperatur DESC LIMIT 0,1;
SELECT FORMAT(MAX(temperatur),1) AS max_temp FROM daten;
SELECT DISTINCT(ort) FROM daten WHERE temperatur = (SELECT MAX(temperatur) FROM daten);

SELECT 'Alle Orte, jeweils nur einmal:' AS Liste;
SELECT ort, breite, laenge FROM daten GROUP BY ort, breite;


-- Wie viele Datensätze haben wir? (mit AS kann man einer Spalte einer Abfrage einen (anderen) Namen geben)
SELECT COUNT(*) AS Anzahl_Datensaetze FROM daten;

-- Daten ausgeben: Alle Felder, aber nur 10 Datensätze beginnend beim 101. (Null-basierte Zählung...) 
SELECT * FROM daten ORDER BY id ASC LIMIT 100,10;

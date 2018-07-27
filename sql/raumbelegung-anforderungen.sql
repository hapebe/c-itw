USE raumbelegung;

SELECT 'Größe der Räume und Anzahlder Arbeitsplätze:' AS 1_Raeume;
SELECT * FROM raeume_ap;

SELECT 'Welcher Computer befindet sich an welchem Arbeitsplatz:' AS 2_Computer_Orte;
SELECT Raum, AP_ID, PC_Marke, PC_Modell, Netzwerk_Name, IP_Addr 
	FROM belegung_lesbar 
	WHERE NOT(Netzwerk_Name IS NULL);

SELECT 'Informationen zum Computer' AS 3_Computer_Details;
SELECT * FROM computer_lesbar;

SELECT 'Welcher Mitarbeiter belegt welchen Arbeitsplatz' AS 4_AP_Belegung;
SELECT * FROM belegung_lesbar;
SELECT '(... und welche Mitarbeiter brauchen noch... ?)' AS 4_kein_AP;
SELECT * FROM mitarbeiter_ohne_ap;

SELECT 'Informationen' AS 5_Alle_Mitarbeiter;
SELECT * FROM mitarbeiter;

#include <string>

using namespace std;

struct person {
    string vorname;
    string nachname;
    int alter;
};

int zahleneingabe(void) {
    string s = "55";

    // Zeichenweise auf Eingabe warten:
    // Ziffern? Anhängen
    // Backspace? Ggf. letztes Zeichen löschen
    // Return? Wenn mindestens ein Zeichen vorhanden; Eingabe abschließen

    // s als Zahl interpretieren
    return stoi(s);
}

void eingabe(person * p) {
    cout << "Vorname: ";
    getline(cin, p->vorname);
    // cin >> p->vorname;

    cout << "Nachname: ";
    getline(cin, p->nachname);
    // cin >> p->nachname;

    cout << "Alter: ";
    cin >> p->alter;
}

person eingabe(void) {
    person p;

    cout << "Vorname: ";
    getline(cin, p.vorname);
    // cin >> p.vorname;

    cout << "Nachname: ";
    getline(cin, p.nachname);
    // cin >> p.nachname;

    cout << "Alter: ";
    textEingabeAcceptEmpty = 0; // keine leere Eingabe akzeptieren
    p.alter = fliesskommaEingabe(3,0);
    // p.alter = zahleneingabe();

    return p;
}

void ausgabe(person p) {
    cout << "Person: " << p.vorname << " " << p.nachname << ", Alter: " << p.alter << endl;
}

void personen() {
    person leute[10];

    leute[0].vorname = "Maaaaaaaaax";
    leute[0].nachname = "Mustermann";
    leute[0].alter = 111;

    ausgabe(leute[0]);

    for (int i=1; i<=2; i++) {
        leute[i] = eingabe();
        // eingabe(&leute[1]);
    }

    for (int i=1; i<=2; i++) {
        ausgabe(leute[i]);
    }
}


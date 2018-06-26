// zum Abschalten des Debug-Modus bitte die folgende Zeile AUSKOMMENTIEREN:
// #define DEBUG 1
#include <iostream>
#include <regex>
#include <cmath>
#include <unistd.h> // für isatty(), fileno()

using namespace std;

// forward-Deklaration für die Klasse, weil sie in IPAdresse schon benutzt wird:
class NetMask;

class IPAdresse {
	protected:
		unsigned int value;
	public:
		IPAdresse(void) {
			this->value = (1 << 24) | (1 << 16) | (1 << 8) | 1;
			// this->value = (255 << 24) | (255 << 16) | (255 << 8) | 255;
		}
		string getDottedQuad(void);
		string getDottedBinary(void);
		bool setDottedQuad(string);
		unsigned int getUInt() { return this->value; }
		void setUInt(unsigned int value) { this->value = value; }
		int getFirstByte(void) { return (this->value & 0xff000000) >> 24; }
		int getSecondByte(void) { return (this->value & 0x00ff0000) >> 16; }
		static bool istGueltigeDottedQuad(string);
		IPAdresse getNetzAdresse(NetMask m);
		IPAdresse getBroadCast(NetMask m);
		IPAdresse getHostAdresse(NetMask m);
		string getRFC791Class(void);
};

class NetMask : public IPAdresse {
	public:
		bool istGueltig(void);
		bool istGueltigAlternativ(void);
		int getCIDRKlasse(void);
		void setCIDRKlasse(int);
		string getRFC791Class(void);
		unsigned int getNetzGroesse(void);
};

class NetAnalyzer {
	public:
		static void beschreibeNetz(IPAdresse host, NetMask mask);
		static bool istPrivat(IPAdresse host);
};

bool istGueltigerInt(string s) {
    regex regexp("0|([1-9][0-9]*)");
    return regex_match(s, regexp);
}

bool isTTY() {
#ifdef _WIN32
	if (_isatty(_fileno(stdin)))
		return true;
	else
		return false;
#endif
#ifdef __linux__
	if (isatty(fileno(stdin)))
		return true;
	else
		return false;
#endif
}

bool IPAdresse::istGueltigeDottedQuad(string s) {
	istringstream stream(s);

	// an den Punkten teilen:
	int tokenCount = 0;
	string token;
	while (getline(stream, token, '.')) {
		// ist jeder Teil ein gültiger int zwischen 0 und 255 ?
		if (!istGueltigerInt(token)) return false;

		int octet = stoi(token);
		if (octet < 0 || octet > 255) return false;

		tokenCount ++;
	}

	// hat genau 3 Punkte bzw. 4 Teile?
	if (tokenCount != 4) return false;

	return true;
}

bool IPAdresse::setDottedQuad(string s) {
	if (!IPAdresse::istGueltigeDottedQuad(s)) return false;

	this->value = 0;

	// wir wissen jetzt schon, dass wir vier gültige ints erwarten dürfen:
	istringstream stream(s);
	string token; int octet;

	// 1. Byte
	getline(stream, token, '.');
	octet = stoi(token);
	this->value += octet << 24;

	// 2. Byte
	getline(stream, token, '.');
	octet = stoi(token);
	this->value += octet << 16;

	// 3. Byte
	getline(stream, token, '.');
	octet = stoi(token);
	this->value += octet << 8;

	// 4. Byte
	getline(stream, token, '.');
	octet = stoi(token);
	this->value += octet << 0;

	return true;
}

string IPAdresse::getDottedQuad() {
	stringstream ss;
	unsigned int octet;

	// octet = (this->value & 0xff000000) >> 24;
	octet = (this->value & 0xff000000) / pow(2,24);
	ss << octet << ".";
	octet = (this->value & 0x00ff0000) >> 16;
	ss << octet << ".";
	octet = (this->value & 0x0000ff00) >> 8;
	ss << octet << ".";
	octet = (this->value & 0x000000ff) >> 0;
	ss << octet;

	return ss.str();
}

string IPAdresse::getDottedBinary() {
	stringstream ss;

	// Startpunkt: Bit #31 (das höchstwertige in einer IP-Adresse)
	int aktuellesBit = 31;

	while (aktuellesBit >= 0) {
		// ist das aktuelle Bit gesetzt?
		if (this->value & (unsigned int)pow(2,aktuellesBit)) {
			ss << "1";
		} else {
			ss << "0";
		}

		// nach 8 Bits jeweils einen Punkt einfügen:
		if (aktuellesBit == 24) ss << ".";
		if (aktuellesBit == 16) ss << ".";
		if (aktuellesBit == 8) ss << ".";

		aktuellesBit--; // nächstkleineres Bit
	}

	return ss.str();
}

IPAdresse IPAdresse::getNetzAdresse(NetMask m) {
	IPAdresse retval;
	retval.setUInt(this->value & m.getUInt());
	return retval;
}

string IPAdresse::getRFC791Class(void) {
	unsigned int prefix = (this->value & 0xf0000000) >> 28;

	if (prefix >= 0x0 && prefix <= 0x7) return "A"; // 0..127
	if (prefix >= 0x8 && prefix <= 0xB) return "B"; // 128..191
	if (prefix >= 0xC && prefix <= 0xD) return "C"; // 192..223
	if (prefix == 0xE) return "D"; // 224..239
	if (prefix == 0xF) return "E"; // 240..255
	return "";
}

IPAdresse IPAdresse::getHostAdresse(NetMask m) {
	IPAdresse retval;
	// die Adresse verknüpft mit der INVERTIERTEN Netz-Maske:
	retval.setUInt(this->value & (~ m.getUInt()));
	return retval;
}

IPAdresse IPAdresse::getBroadCast(NetMask m) {
	unsigned int basis = this->getNetzAdresse(m).getUInt();
	IPAdresse retval;
	retval.setUInt(basis + m.getNetzGroesse() - 1); // die letzte IP-Adresse vor dem nächsten Sub-Netz...
	return retval;
}

bool NetMask::istGueltig(void) {
	if (this->getCIDRKlasse() == -1) return false;
	return true;
}

int NetMask::getCIDRKlasse(void) {
	unsigned int alleBits = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	for (int i=0; i<=32; i++) {
		unsigned int hostmask = (1 << i) - 1;
		unsigned int netmask = alleBits - hostmask;

		if (i==32) netmask = 0; // brauche ich, weil sonst wegen Overflows ein falscher Wert errechnet wird

		// NetMask temp;
		// temp.setUInt(netmask);
		// cout << "CIDR #" << i << ": " << temp.getDottedQuad() << endl;

		if (netmask == this->value) return 32-i;
	}

	return -1;
}

bool NetMask::istGueltigAlternativ() {
	long temp = this->value; // value ist die IP-Adresse als 32-bit-unsigned int
	unsigned int check = pow(2,31);

	while (check > 0) {
		temp -= check;

		if (temp == 0) return true; // wenn alle folgenden Bits 0 sind: gültig!

		// der folgende Fall tritt auch ein, wenn GAR KEIN Bit gesetzt war:

		// das aktuelle Bit ist nicht gesetzt, aber irgendwo "weiter hinten"
		// gibt es noch gesetzte Bits:
		if (temp < 0) return false;

		check /= 2; // nächstkleineres Bit
	}
	return true;
}

void NetMask::setCIDRKlasse(int l) {
	unsigned int mask = (255 << 24) + (255 << 16) + (255 << 8) + 255;

	int shift = 32-l;
	for (int i=shift-1; i>=0; i--) {
		mask -= (1 << i);
	}

	this->value = mask;
}

string NetMask::getRFC791Class(void) {
	if (this->value == 0xff000000) return "A";
	if (this->value == 0xffff0000) return "B";
	if (this->value == 0xffffff00) return "C";
	// stellt sich heraus: Klasse D hat gar keine definierte Subnetz-Maske!
	// if (this->value == 0xffffffff) return "D";
	return "";
}

unsigned int NetMask::getNetzGroesse(void) {
	return (~ this->value)+1; // der binäre Kehrwehrt der Netzmaske!
}


void NetAnalyzer::beschreibeNetz(IPAdresse host, NetMask mask) {
	if ((host.getRFC791Class() == "A") && (mask.getRFC791Class() == "A")) {
		cout << "Das ist ein Netzwerk der RFC-791-Klasse A.";
		if (host.getFirstByte() == 0) {
			cout << " Es handelt sich um das \"Here\"-Netzwerk 0.0.0.0/8.";
		}
		if (host.getFirstByte() == 10) {
			cout << " Es handelt sich um das private Netzwerk 10.0.0.0/8.";
		}
		if (host.getFirstByte() == 127) {
			cout << " Es handelt sich um das Loopback-Netzwerk 127.0.0.0/8.";
		}
	} else if ((host.getRFC791Class() == "B") && (mask.getRFC791Class() == "B")) {
		cout << "Das ist ein Netzwerk der RFC-791-Klasse B.";
		if (host.getFirstByte() == 169 && host.getSecondByte() == 254) {
			cout << " Es handelt sich um das private (APIPA-)Netzwerk 169.254.0.0/16.";
		}
		if (host.getFirstByte() == 172 && host.getSecondByte() >= 16 && host.getSecondByte() <= 31) {
			cout << " Es handelt sich um ein privates Netzwerk aus dem Bereich 172.16.0.0/12.";
		}
	} else if ((host.getRFC791Class() == "C") && (mask.getRFC791Class() == "C")) {
		cout << "Das ist ein Netzwerk der RFC-791-Klasse C.";
		if (host.getFirstByte() == 192 && host.getSecondByte() == 168) {
			cout << " Es handelt sich um ein privates Netzwerk aus dem Bereich 192.168.0.0/16.";
		}
	} else if (host.getRFC791Class() == "D") {
		cout << "Das ist ein Netzwerk der RFC-791-Klasse D (die Subnetz-Maske für diese Klasse ist nicht definiert).";
	} else if (host.getRFC791Class() == "E") {
		cout << "Das ist ein Netzwerk der RFC-791-Klasse E (die Subnetz-Maske für diese Klasse ist nicht definiert).";
	} else if (host.getUInt() == 0 && mask.getCIDRKlasse() == 32) {
		cout << "Es handelt sich um die Meta-Adresse 0.0.0.0/32.";
	} else if (host.getUInt() == 0xffffffff && mask.getCIDRKlasse() == 32) {
		cout << "Es handelt sich um die \"Limited Broadcast\"-Adresse 255.255.255.255/32.";
	} else {
		cout << "Das Netzwerk entspricht keiner Klasse nach RFC 791.";
	}
	cout << " Die Host-Adresse ist " << (NetAnalyzer::istPrivat(host)?"privat":"öffentlich") << ".";
	cout << endl;
}

bool NetAnalyzer::istPrivat(IPAdresse host) {
	unsigned int a = host.getUInt();
	if (a >= 0x0a000000 && a <= 0x0affffff) return true; // 10.0.0.0/8
	if (a >= 0xa9fe0000 && a <= 0xa9feffff) return true; // 169.254.0.0/16
	if (a >= 0xac100000 && a <= 0xac1fffff) return true; // 172.16.0.0/12
	if (a >= 0xc0a80000 && a <= 0xc0a8ffff) return true; // 192.168.0.0/16
	return false;
}

/**
 * überladener == Operator für IPAdresse ...
 */
bool operator==(IPAdresse lhs, IPAdresse rhs) {
	if (lhs.getUInt() == rhs.getUInt()) return true;
	return false;
}


IPAdresse allesEins;
IPAdresse host;
NetMask mask;
IPAdresse gateway;

void eingabe(void) {
	if (isTTY()) {
		cout << "Bitte geben Sie die Netzmaske (in Dotted-Quad-Notation) ein: ";
	}

	string s;
	do {
		cin >> s;
		if (!IPAdresse::istGueltigeDottedQuad(s)) {
			if (isTTY()) {
				cout << "\"" << s << "\" ist keine gültige IP-Adresse. Bitte Eingabe wiederholen: ";
			} else {
				cout << "\"" << s << "\" ist keine gültige IP-Adresse!" << endl;
				exit(1);
			}
			continue;
		}

		// okay, s ist formal ein gültige IP-Adresse:
		mask.setDottedQuad(s);
		if (!mask.istGueltig()) {
			if (isTTY()) {
				cout << "\"" << s << "\" ist keine gültige Netzmaske. Bitte Eingabe wiederholen: ";
			} else {
				cout << "\"" << s << "\" ist keine gültige Netzmaske!" << endl;
				exit(1);
			}
			continue;
		}

		break;
	} while(true);



	if (isTTY()) cout << "Bitte geben Sie die Host-Adresse ein: ";
	do {
		cin >> s;
		if (!IPAdresse::istGueltigeDottedQuad(s)) {
			if (isTTY()) {
				cout << "\"" << s << "\" ist keine gültige IP-Adresse. Bitte Eingabe wiederholen: ";
			} else {
				cout << "\"" << s << "\" ist keine gültige IP-Adresse!";
				exit(1);
			}
			continue;
		}

		// okay, s ist formal ein gültige IP-Adresse:
		host.setDottedQuad(s);

		if (host.getNetzAdresse(mask) == host) {
			if (mask.getCIDRKlasse() < 31) {
				cout << "Problem: Die Host-Adresse ist identisch zur Netzwerk-Adresse." << endl;
				if (isTTY()) {
					cout << "Bitte geben Sie eine andere Host-Adresse an: ";
				} else {
					exit(1);
				}
				continue;
			} else if (mask.getCIDRKlasse() == 31) {
				// 31 hat zwei Adressen - Netz- und Broadcast. Es gibt keine Host-Adressen.
				cout
					<< "Die Host-Adresse entspricht der Netzwerk-Adresse, das ist "
					<< "bei der CIDR-Netzklasse 31 aber vielleicht akzeptabel." << endl;
			} else if (mask.getCIDRKlasse() == 32) {
				// 32 hat nur eine Adresse - hier sind also sogar Netz- und Broadcast-Adresse identisch. Es gibt keine Host-Adressen!
				cout
					<< "Die Host-Adresse entspricht der Netzwerk- und Broadcast-Adresse, "
					<< "das ist bei der CIDR-Netzklasse 32 aber unvermeidlich." << endl;
			}
		}

		if (host.getHostAdresse(mask) == allesEins.getHostAdresse(mask)) {
			if (mask.getCIDRKlasse() < 31) {
				cout << "Problem: Die Host-Adresse ist identisch zur Broadcast-Adresse." << endl;
				if (isTTY()) {
					cout << "Bitte geben Sie eine andere Host-Adresse an: ";
				} else {
					exit(1);
				}
				continue;
			} else if (mask.getCIDRKlasse() == 31) {
				cout
					<< "Die Host-Adresse entspricht der Broadcast-Adresse, das ist "
					<< "bei der CIDR-Netzklasse 31 aber vielleicht akzeptabel." << endl;
			} else if (mask.getCIDRKlasse() == 32) {
				// Meldung hatten wir dann schon oben...
			}
		}

		// Eingabe okay, weitermachen:
		break;
	} while(true);
	
	
	if (mask.getCIDRKlasse() == 32) {
		// Bei Klasse 32 muss das Gateway gleich dem Host sein:
		gateway.setUInt(host.getUInt());
	} else {
		if (isTTY()) cout << "Bitte geben Sie die Gateway-Adresse ein: ";
		do {
			cin >> s;
			if (!IPAdresse::istGueltigeDottedQuad(s)) {
				cout << "\"" << s << "\" ist keine gültige IP-Adresse.";
				if (isTTY()) {
					cout << " Bitte Eingabe wiederholen: ";
				} else {
					exit(1);
				}
				continue;
			}

			// okay, s ist formal ein gültige IP-Adresse:
			gateway.setDottedQuad(s);

			if (!(host.getNetzAdresse(mask) == gateway.getNetzAdresse(mask))) {
				cout << "Problem: Der Gateway liegt nicht im gleichen Netzwerk wie der Hosts." << endl;
				if (isTTY()) {
					cout << " Bitte Eingabe wiederholen: ";
				} else {
					exit(1);
				}
				continue;
			}

			if (host == gateway) {
				cout << "Problem: Host- und Gateway-Adresse sind identisch." << endl;
				if (isTTY()) {
					cout << " Bitte Eingabe wiederholen: ";
				} else {
					exit(1);
				}
				continue;
			}

			if (gateway.getNetzAdresse(mask) == gateway) {
				if (mask.getCIDRKlasse() < 31) {
					cout << "Problem: Die Gateway-Adresse ist identisch zur Netzwerk-Adresse." << endl;
					if (isTTY()) {
						cout << "Bitte geben Sie eine andere Gateway-Adresse an: ";
					} else {
						exit(1);
					}
					continue;
				} else if (mask.getCIDRKlasse() == 31) {
					// 31 hat zwei Adressen - Netz- und Broadcast. Es gibt keine Host-Adressen.
					cout
						<< "Die Gateway-Adresse entspricht der Netzwerk-Adresse, das ist "
						<< "bei der CIDR-Netzklasse 31 aber vielleicht akzeptabel." << endl;
				}
			}

			if (gateway.getHostAdresse(mask) == allesEins.getHostAdresse(mask)) {
				if (mask.getCIDRKlasse() < 31) {
					cout << "Problem: Die Gateway-Adresse ist identisch zur Broadcast-Adresse." << endl;
					if (isTTY()) {
						cout << "Bitte geben Sie eine andere Gateway-Adresse an: ";
					} else {
						exit(1);
					}
					continue;
				} else if (mask.getCIDRKlasse() == 31) {
					cout
						<< "Die Gateway-Adresse entspricht der Broadcast-Adresse, das ist "
						<< "bei der CIDR-Netzklasse 31 aber vielleicht akzeptabel." << endl;
				}
			}

			// Eingabe okay, weitermachen:
			break;
		} while(true);
	}
}

int main() {
	allesEins.setDottedQuad("255.255.255.255");

#ifdef DEBUG
//	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.168.0.255") << endl;
//	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.168.0.256") << endl;
//	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.168.0.") << endl;
//	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.-1.0.1") << endl;
//	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("a.b.c.d") << endl;

	IPAdresse adresse;
	// cout << adresse.getDottedQuad() << endl;
	adresse.setDottedQuad("192.168.20.57");
	cout << "Adresse: " << adresse.getDottedQuad() << endl;

	NetMask maske;
	maske.setDottedQuad("255.255.255.240");
	cout << "Subnetz-Adresse: " << maske.getDottedQuad() << endl;
	cout << "Subnetz (binär): " << maske.getDottedBinary() << endl;
	cout << "Netzgröße: " << maske.getNetzGroesse() << endl;
	cout << "Adresse mit CIDR-Klasse: " << maske.getDottedQuad() << "/" << maske.getCIDRKlasse() << endl;
	cout << "Netz-Adresse: " << adresse.getNetzAdresse(maske).getDottedQuad() << endl;
	cout << "Broadcast-Adresse: " << adresse.getBroadCast(maske).getDottedQuad() << endl;

	IPAdresse gw;
	gw.setDottedQuad("192.168.40.252");
	cout << "Gateway: " << gw.getDottedQuad() << endl;

	cout << "Netz des Hosts: " << adresse.getNetzAdresse(maske).getDottedQuad() << endl;
	cout << "Netz des Gateways: " << gw.getNetzAdresse(maske).getDottedQuad() << endl;
	if (adresse.getNetzAdresse(maske) == gw.getNetzAdresse(maske)) {
		cout << "Der Gateway liegt im gleichen Netzwerk wie der Hosts." << endl;
	} else {
		cout << "Problem: Der Gateway liegt nicht im gleichen Netzwerk wie der Hosts." << endl;
	}

//	for(int i=0; i<=32; i++) {
//		maske.setCIDRKlasse(i);
//		cout << "Netzmaske der CIDR-Klasse " << i << ": " << maske.getDottedQuad() << endl;
//		cout << "    (binär: " << maske.getDottedBinary() << ")" << endl;
//	}
//
//	while (true) {
//		cout << "Bitte geben Sie eine Netzmaske ein: ";
//		string st;
//		cin >> st;
//		maske.setDottedQuad(st);
//		cout << "entspricht binär: " << maske.getDottedBinary() << endl;
//		cout << boolalpha << "istGueltigAlternativ sagt: " << maske.istGueltigAlternativ() << endl;
//	}

	exit(0);
#endif

	if (isTTY()) {
		cout << "Dieses Programm erfragt und prüft die Konfiguration einer IPv4-Netzwerkschnittstelle mit Gateway." << endl;
		cout << endl;
	}
	
	while (true) {
		// das setzt die globalen Variablen:
		eingabe();
		
		if (host.getFirstByte() == 127 && isTTY()) {
			cout << "Adressen aus dem Loopback-Netzwerk werden nicht akzeptiert - bitte etwas anderes eingeben!" << endl;
			continue;
		}
		// Eingabe okay:
		break;
	}

	if (isTTY()) {
		cout << endl << "Danke! Ihre gewünschte Netzwerk-Konfiguration:" << endl;
	} else {
		cout << "Ihre Netzwerk-Konfiguration:" << endl;
	}
	cout << "Adresse: " << host.getDottedQuad() << "/" << (unsigned int)mask.getCIDRKlasse() << endl;
	cout << "Gateway: " << gateway.getDottedQuad() << endl;

	// das gibt u.a. die Klasse nach RFC 791 aus:
	NetAnalyzer::beschreibeNetz(host, mask);

    return 0;
}

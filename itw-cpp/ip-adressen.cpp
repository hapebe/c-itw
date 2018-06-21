// zum Abschalten des Debug-Modus bitte die folgende Zeile AUSKOMMENTIEREN:
// #define DEBUG 1
#include <iostream>
#include <regex>
#include <cmath>

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
		bool setDottedQuad(string);
		unsigned int getUInt() { return this->value; }
		void setUInt(unsigned int value) { this->value = value; }
		static bool istGueltigeDottedQuad(string);
		IPAdresse getNetzAdresse(NetMask m);
};

class NetMask : public IPAdresse {
	public:
		bool istGueltig(void);
		int getCIDRKlasse(void);
};

bool istGueltigerInt(string s) {
    regex regexp("0|([1-9][0-9]*)");
    return regex_match(s, regexp);
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

IPAdresse IPAdresse::getNetzAdresse(NetMask m) {
	IPAdresse retval;
	retval.setUInt(this->value & m.getUInt());
	return retval;
}

bool NetMask::istGueltig(void) {
	if (this->getCIDRKlasse() == -1) return false;
	return true;
}

int NetMask::getCIDRKlasse(void) {
	unsigned int alleBits = (255 << 24) + (255 << 16) + (255 << 8) + 255;
	
	for (int i=0; i<33; i++) {
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

/**
 * überladener == Operator für IPAdresse ...
 */
bool operator==(IPAdresse lhs, IPAdresse rhs) {
	if (lhs.getUInt() == rhs.getUInt()) return true;
	return false;
}


int main() {
#ifdef DEBUG
	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.168.0.255") << endl;
	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.168.0.256") << endl;
	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.168.0.") << endl;
	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("192.-1.0.1") << endl;
	cout << boolalpha << IPAdresse::istGueltigeDottedQuad("a.b.c.d") << endl;
	
	IPAdresse adresse;
	cout << adresse.getDottedQuad() << endl;
	adresse.setDottedQuad("192.168.20.57");
	cout << "Adresse: " << adresse.getDottedQuad() << endl;
	
	NetMask subnetz;
	subnetz.setDottedQuad("255.255.128.0");
	cout << "Subnetz-Adresse: " << subnetz.getDottedQuad() << endl;
	cout << "Adresse mit CIDR-Klasse: " << adresse.getDottedQuad() << "/" << subnetz.getCIDRKlasse() << endl;
	
	IPAdresse gateway;
	gateway.setDottedQuad("192.168.40.252");
	cout << "Gateway: " << gateway.getDottedQuad() << endl;
	
	cout << "Netz des Hosts: " << adresse.getNetzAdresse(subnetz).getDottedQuad() << endl;
	cout << "Netz des Gateways: " << gateway.getNetzAdresse(subnetz).getDottedQuad() << endl;
	if (adresse.getNetzAdresse(subnetz) == gateway.getNetzAdresse(subnetz)) {
		cout << "Der Gateway liegt im gleichen Netzwerk wie der Hosts." << endl;
	} else {
		cout << "Problem: Der Gateway liegt nicht im gleichen Netzwerk wie der Hosts." << endl;
	}
	
#endif
	
	cout << "Dieses Programm erfragt und prüft die Konfiguration einer IPv4-Netzwerkschnittstelle mit Gateway." << endl;
	cout << endl;
	
	cout << "Bitte geben Sie die Host-Adresse ein: ";
	string s;
	IPAdresse host;
	do {
		cin >> s;
		if (!IPAdresse::istGueltigeDottedQuad(s)) {
			cout << "\"" << s << "\" ist keine gültige IP-Adresse. Bitte Eingabe wiederholen: ";
			continue;
		} 
		// Eingabe okay, weitermachen:
		break;
	} while(true);
	host.setDottedQuad(s);

	cout << "Bitte geben Sie die Netzmaske (in Dotted-Quad-Notation) ein: ";
	NetMask mask;
	do {
		cin >> s;
		if (!IPAdresse::istGueltigeDottedQuad(s)) {
			cout << "\"" << s << "\" ist keine gültige IP-Adresse. Bitte Eingabe wiederholen: ";
			continue;
		}

		// okay, s ist formal ein gültige IP-Adresse:
		mask.setDottedQuad(s);
		if (!mask.istGueltig()) {
			cout << "\"" << s << "\" ist keine gültige Netzmaske. Bitte Eingabe wiederholen: ";
			continue;
		}
		
		if (host.getNetzAdresse(mask) == host) {
			cout 
				<< "Problem: Die Host-Adresse wäre so identisch zur Netzwerk-Adresse." 
				<< endl 
				<< "Bitte geben Sie eine kürzere Netzmaske ein: ";
			continue;
		}
		
		break;
	} while(true);
	
	
	cout << "Bitte geben Sie die Gateway-Adresse ein: ";
	IPAdresse gateway;
	do {
		cin >> s;
		if (!IPAdresse::istGueltigeDottedQuad(s)) {
			cout << "\"" << s << "\" ist keine gültige IP-Adresse. Bitte Eingabe wiederholen: ";
			continue;
		}
		
		// okay, s ist formal ein gültige IP-Adresse:
		gateway.setDottedQuad(s);
		if (host.getNetzAdresse(mask) == gateway.getNetzAdresse(mask)) {
			// Eingabe okay, weitermachen:
			break;
		} else {
			cout 
				<< "Problem: Der Gateway liegt nicht im gleichen Netzwerk wie der Hosts." 
				<< endl 
				<< "Bitte Eingabe wiederholen: ";
			continue;
		}
	} while(true);
	
	cout << endl << "Danke! Ihre gewünschte Netzwerk-Konfiguration:" << endl;
	cout << "Adresse: " << host.getDottedQuad() << "/" << mask.getCIDRKlasse() << endl;
	cout << "Gateway: " << gateway.getDottedQuad() << endl;
	
    return 0;
}

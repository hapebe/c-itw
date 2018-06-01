# C programmieren

Ich arbeite parallel auf Windows (mit Dev-C++, wie vom Dozenten vorbereitet) und auf Ubuntu. Hier habe ich zunächst `apt install build-essential` aufgeführt, und dann über die grafischen Software-Tools "Geany" als einfache IDE installiert.

Neben den ersten Schritten in einer Programmiersprache habe ich erstmal folgende interessante "Entdeckungen" gemacht:
* `gcc -S <c-program.c>` erstellt eine Datei, die das Programm in Assembler enthält.
* `objdump -S --disassemble <object-code.o>` erfüllt den gleichen Zweck, geht aber von der fertig kompilierten Objekt-Datei aus.
* Plattform-spezifische Pre-Compiler-Konstanten: Um für Windows und Linux ggf. alternativen Code einzubinden, kann man sowas hier machen:
```
#ifdef _WIN32
#include <conio.h>
#endif

#ifdef __linux__
#include "./getch.c"
#endif
```

Ansonsten bin ich vor allem überrascht, wie die Übergabe von Array-Parameter an Funktionien funktioniert (oder eben nicht funktioniert), und erst recht: Arrays als "Return-Werte"...

## int-Zahlen sortieren

Jetzt fertig: Programm, dass Zahlenfolgen mittels QuickSort oder BubbleSort sortiert, und dabei einige Zähler erhebt. Habe ich genutzt, um auch mittels `time ...` die tatsächliche Performance auf der Maschine hier zu erheben.
Syntax für einen solchen Aufruf:

*Code siehe:* [random-1000000.sh](extra/random-1000000.sh), [viele-zahlen](viele-zahlen.c)

```
cd <repository dir>
time extra/random-1000000.sh | ./viele-zahlen
```
Dieser Aufruf generiert 1 Million Zufallszahlen und sortiert sie dann mit Bubblesort - das ist schon ein sehr ehrgeiziges Unterfangen. Meine Schätzung vorher: Es wird ca. 4400s dauern (also etwa 1 1/4 Stunden); und es werden ca. 250 Milliarden Zahlenpaare vertauscht...
Tatsächliche Zahlen:
4320,9s; 250.320.138.598 Vertauschungen

Das gleich mit Quicksort:
```
time extra/random-1000000.sh | ./viele-zahlen qs
```
Tatsächliche Zahlen:
13,6s; 5.361.728 Vertauschungen

Quicksort ist bei diesen Bedingungen also bereits mehr als 300mal schneller.

## Zahlen-Notations-Systeme (binär, oktal, dezimal, hex, Base-36, Exoten)

Es war spannend - spannender, als ich ursprünglich dachte. Das Handling von symbolischen Zahlen (also Strings, also Null-terminierte char-Arrays) in Verbindung mit Funktionen war ein Erlebnis. Im Endeffekt ist hier ein "Standard-Programm" entstanden, dass ich vielleicht ja wirklich mal nutzen kann: [baseconv.c](baseconv.c).

### Exkursion dazu: git-Branching
_Siehe auch: [git-basics.md](git-basics.md)_

Anlass bzw. Vorhaben dazu: In das Programm [baseconv](baseconv.c) eine Kommandozeilen-Option einbauen, mit dem sich das "menschenlesbare" Gruppieren von Ziffern einschalten lässt. Weil ich das mit dem/n include(s) für "getopt()" umsetzen will, möchte ich nebenher die "saubere" Programmversion erhalten. Also: Branch!

## struct, Strings und allerlei Eingabe-Magie
Besonders das Hantieren mit Strings in der 
"Wild-West"-Speicher-Verwaltungs-Philosophie von C kommt mir aufwändig und 
gefährlich vor - letzteres stimmt ja wohl auch, wenn ich an 
"Buffer Overflow"-Sicherheits-Probleme denke, die wohl oft mit C verbunden 
sind. Ersteres stimmt wahrscheinlich auch ganz allgemein, allerdings eben 
nur zur Entwurfs-Zeit - bei der Ausführung spart das Wegfallen sämtlicher 
automatischer Tests im Hintergrund anderer (Sprach-)Systeme vermutlich für
schnellere Ausführung. ABER - es ist wirklich anstrengend, über diese 
"niederen" Aufgaben nachzudenken...

Neueste Entdeckung ansonsten: Die Funktion isatty() aus unistd.h, mit deren
Hilfe ich unterscheiden kann, ob die Standard-Eingabe "interaktiv" von der
Konsole stammt oder aus einer umgelenkten Datei bzw. einer "Pipe". Beispiel 
siehe: [struct1.c](struct1.c)

## Ideen, ToDos, Projekte
* erledigt: QuickSort implementieren (http://www.zentut.com/c-tutorial/c-quicksort-algorithm/)
* gute alte Zeiten: mal den Quellcode von German Atlantis 6.2 (6.6?) kompilieren und schauen, dass ich den Spiel-"Host" zum laufen bekomme.
  * nachdem es mit German Atlantis 62 geklappt hat: Ich möchte erstmal eine Quellenrecherche machen: Wer bietet wo welchen Quellcode zum Download an, bzw. verwaltet Code in Versionierungssystemen?
  * ACheck Quellen von german-atlantis.de: [http://www.german-atlantis.de/data/achk_src.zip]
  * German Atlantis 6.2 von german-atlantis.de: [http://www.german-atlantis.de/data/version62.zip]
  * "aktueller" Source-Code des German Atlantis-Servers: [http://www.german-atlantis.de/data/version62.zip] _(existiert vermutlich nicht mehr...)_
  * englisch-sprachiger Atlantis Source-Code (die Wikipedia nennt das den Quellcode von Atlantis 5.0): [https://github.com/Atlantis-PBEM/Atlantis] (anscheinend C++)
  * englisch-sprachiger Atlantis Source-Code der Version(en) 4.0.x: [http://www.prankster.com/project/download/download.htm]
  * Eressea Server auf GitHub: [https://github.com/eressea/server]
  * Fantasya Server auf GitHub: [https://github.com/wavepacket/Fantasya] (ist in Java implementiert...)
  * TODO: [http://www.arno-saxena.de/atlantis/atl_home.php]
* in den Quellcode der GNU core-utils schauen (dort gibt es ja u.a. auch den sort-Befehl...)
* mal über GUI-Programmierung mit GTK / QT (oder wie sie alle heißen...) nachlesen und vielleicht ein paar Fingerübungen machen
* über make / Makefile etc. lesen und damit experimentieren (sowas gibt es u.a. ja auch bei den klassischen German-Atlantis-Quellen...)
* irgendwie ähnlich zur make-Erkundung: bestehendes Projekt mit Code::Blocks "importieren" und versuchen zu kompilieren (Spoiler: mit den klimageraet.c-Dateien funktioniert es nicht auf Anhieb...)
* Doxygen anschauen: JavaDoc-ähnliche Dokumentation aus Kommentaren im Quelltext generieren?
  * "Moritz" ist ein PlugIn für Doxygen, dass Nassi-Shneiderman-Diagramme erstellt (aka "Struktogramme")
* in Richtung "Schiffe versenken" als Projekt im itw-Unterricht: den Source-Code von "gnome-mines" studieren, dort etwas über die Oberflächen-Programmierung
  * hmmm, stellt sich heraus, dass gnome-mines in Vala geschrieben ist - das ist wohl eine Sprache, die ihren Code wiederum nach C kompiliert, aber für meine Zwecke kommt mir das erstmal zu kompliziert vor. :-(
  * also anderweitig: [https://www.quora.com/How-do-I-create-a-beautiful-GUI-in-C-Linux]
  * Lese-Stoff: [https://developer.gnome.org/gtk-tutorial/stable/]

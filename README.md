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

### Exkursion dazu: (git-Branching)[git-basics.md]
Anlass bzw. Vorhaben dazu: In das Programm [baseconv](baseconv.c) eine Kommandozeilen-Option einbauen, mit dem sich das "menschenlesbare" Gruppieren von Ziffern einschalten lässt. Weil ich das mit dem/n include(s) für "getopt()" umsetzen will, möchte ich nebenher die "saubere" Programmversion erhalten. Also: Branch!

## Ideen, ToDos, Projekte
* erledigt: QuickSort implementieren (http://www.zentut.com/c-tutorial/c-quicksort-algorithm/)
* gute alte Zeiten: mal den Quellcode von German Atlantis 6.2 (6.6?) kompilieren und schauen, dass ich den Spiel-"Host" zum laufen bekomme.
* in den Quellcode der GNU core-utils schauen (dort gibt es ja u.a. auch den sort-Befehl...)

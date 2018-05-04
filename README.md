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

## Ideen, ToDos, Projekte
* Aktuelles Projekt: QuickSort implementieren (http://www.zentut.com/c-tutorial/c-quicksort-algorithm/)

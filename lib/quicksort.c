#include <stdio.h>

// globale Variablen zur Performance-Beurteilung:
long qsCallCount = 0, qsSwapCount = 0, qsMaxRecurseDepth = 0;

/**
 * die Performance-"Counter" zurücksetzen, falls mehrere
 * Sortier-Durchläufe stattfinden.
 */
void quicksortResetStats() {
	qsCallCount = 0;
	qsSwapCount = 0;
	qsMaxRecurseDepth = 0;
}

/**
 * Quelle: http://www.zentut.com/c-tutorial/c-quicksort-algorithm/
 */

/**
 * vertauscht die Inhalte zweiter int-Variablen
 */
void swap(int *x,int *y) {
    static int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * wählt ein Element zwischen i und j (inklusive) als Pivot aus
 */
int choosePivot(int i, int j) { return((i+j) /2); }

/**
 * sortiert list garantiert aufsteigend im Abschnitt von startIdx bis endIdx.
 */
void quicksort(int list[], int startIdx, int endIdx, int recurseDepth) {
	#ifdef DEBUG
	printf("quicksort(..., %d, %d, Tiefe: %d)...\n", startIdx, endIdx, recurseDepth);
	#endif

	if (recurseDepth > qsMaxRecurseDepth) qsMaxRecurseDepth = recurseDepth;
	qsCallCount ++;

    if(startIdx < endIdx) {
		int i, j, pivotIdx, pivotValue;

        pivotIdx = choosePivot(startIdx, endIdx);
        pivotValue = list[pivotIdx];
		#ifdef DEBUG
		printf("Verwende #%d (%d) als Pivot-Element.\n", pivotIdx, pivotValue);
		#endif


        // den Pivot-Wert am Anfang der Liste platzieren:
        swap(&list[startIdx], &list[pivotIdx]);
        qsSwapCount ++;

        i = startIdx + 1; // hinter dem Pivot-Element anfangen...
        j = endIdx;
        while (i <= j) {
            while((i <= endIdx) && (list[i] <= pivotValue))
                i++; // solange kleiner/gleich als Pivot-Wert: okay
            while((j >= startIdx) && (list[j] > pivotValue))
                j--; // solange größer als Pivot-Wert: okay
            if (i < j) {
				// wir haben "links" eine Wert <= Pivot-Wert und
				// rechts einen Wert > Pivot-Wert: tauschen!
				#ifdef DEBUG
				printf("Tausche #%d und #%d (%d <-> %d).\n", i, j, list[i], list[j]);
				#endif
                swap(&list[i], &list[j]);
				qsSwapCount ++;
			}
        }
        /* Pivot-Element an Position j verschieben: */
		#ifdef DEBUG
		printf("Pivot-Element (%d) kommt jetzt an Position #%d.\n", pivotValue, j);
		#endif
        swap(&list[startIdx], &list[j]);
        qsSwapCount ++;

        /* Zwei Teil-Listen rekursiv sortieren: */
        if (startIdx < j-1) {
			#ifdef DEBUG
			printf("Aufruf links: ");
			#endif
	        quicksort(list, startIdx, j-1, recurseDepth+1);
		}
		if (j+1 < endIdx) {
			#ifdef DEBUG
			printf("Aufruf rechts: ");
			#endif
			quicksort(list, j+1, endIdx, recurseDepth+1);
		}

    } else {
		printf("Problem: quicksort() mit startIdx > endIdx aufgerufen...\n");
	}
}

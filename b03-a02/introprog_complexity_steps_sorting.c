#include <stdio.h>
#include <stdlib.h>
#include "introprog_complexity_steps_input.h"

const int MAX_VALUE = 5000000;

void count_sort_calculate_counts(int input_array[], int len, int count_array[], unsigned int* befehle) {
    // Muss implementiert werden
    for(int j = 0; j<len; j++){
        count_array[input_array[j]] = count_array[input_array[j]] + 1;
        *befehle += 1; // Vergleich der for-Schleife ergibt einen Befehl
        *befehle += 1; // Zuweisung der for-Schleife ergibt einen Befehl
        *befehle += 1; // Körper der for-Schleife ergibt einen Befehl
    }
    *befehle += 1; // Initialisierung der for-Schleife ergibt einen Befehl
    *befehle += 1; // Abbruch der for-Schleife bzw. letzter Vergleich ergibt einen zusätzlichen Befehl
}

void count_sort_write_output_array(int output_array[], int len, int count_array[], unsigned int* befehle) {
    // Muss implementiert werden
    int k = 0;
    *befehle += 1; // int k = 0, Initialisierung als Befehl

    for(int j = 0;  j < MAX_VALUE ; j++){

        for(int i = 0;  i < count_array[j]  ; i++){
            
            output_array[k] = j;
            k = k + 1;
            *befehle += 1; // Vergleich der zweiten for-Schleife ergibt einen Befehl
            *befehle += 1; // Zuweisung der zweiten for-Schleife ergibt einen Befehl
            *befehle += 1; // output_array[k] = j, Zuweisung ergibt einen Befehl (Körper)
            *befehle += 1; // k = k + 1, Zuweisung ergibt einen Befehl (Körper)
        }
        *befehle += 1; // Vergleich der ertsten for-Schleife ergibt einen Befehl
        *befehle += 1; // Zuweisung der ersten for-Schleife ergibt einen Befehl
        *befehle += 1; // Körper der ersten for-Schleife ergibt einen Befehl
    } 
    *befehle += 1; // Initialisierung der zweiten for-Schleife ergibt einen Befehl
    *befehle += 1; // Initialisierung der ersten for-Schleife ergibt einen Befehl
    *befehle += 1; // Abbruch der zweiten for-Schleife bzw. letzter Vergleich ergibt einen zusätzlichen Befehl
    *befehle += 1; // Abbruch der ersten for-Schleife bzw. letzter Vergleich ergibt einen zusätzlichen Befehl
}

void count_sort(int array[], int len, unsigned int* befehle) {
    
    int *count_array = calloc(MAX_VALUE, sizeof(int));
    *befehle += 1; // Initialisierung ergibt einen Befehl
   
    count_sort_calculate_counts(array,len,count_array, befehle);
    count_sort_write_output_array(array,len,count_array, befehle);

    free(count_array);
}


void insertion_sort(int array[], int len, unsigned int* befehle) {
    // Muss implementiert werden
    for(int j=1; j<len; j++){

        
        int key = array[j];
        *befehle += 1; // int key = array[j], Initialisierung ergibt einen Befehl
        int i = j-1;
        *befehle += 1; // int i = j-1, Initialisierung ergibt einen Befehl

        while(i>-1 && array[i]>key){


            array[i+1] = array[i];

            i = i-1;

            *befehle += 1; // Erster Vergleich der while-Schleife ergibt einen Befehl
            *befehle += 1; // Zweiter Vergleich der while-Schleife ergibt auch einen Befehl
            *befehle += 1; // array[i+1] = array[i], Zuweisung ergibt einen Befehl (Körper)
            *befehle += 1; // i = i-1, Zuweisung ergibt einen Befehl (Körper)

        }

        if(i<=-1){
            *befehle += 1; // Einen zusätzlichen Befehl wenn der erste Vergleich der while-Schleife nicht zutrifft
        }
        else if(array[i]<=key){
            *befehle += 1; // Einen zusätzlichen Befehl wenn der erste Vergleich der while-Schleife zutrifft
            *befehle += 1; // Einen zusätzlichen Befehl wenn der zweite Vergleich der while-Schleife nicht zutrifft
        }

        array[i+1] = key;
        *befehle += 1; // array[i+1] = key, Zuweisung ergibt einen Befehl


    }
    *befehle += 1; //Initialisierung der for-Schleife ergibt einen Befehl
    *befehle += 1; // Abbruch der for-Schleife bzw. letzter Vergleich ergibt auch einen zusätzlichen Befehl
}


int main(int argc, char *argv[]) {
    const int WERTE[] = {10000,20000,30000,40000,50000};
    const int LEN_WERTE = 5;
    const int LEN_ALGORITHMEN = 2;

    int rc = 0;
    unsigned int befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];


    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];


        // Reserviere Speicher für  Arrays der Länge n
        int* array_countsort = malloc(sizeof(int) * n);
        int* array_insertionsort = malloc(sizeof(int) * n);

        // Fülle array_countsort mit Zufallswerten ..
        fill_array_randomly(array_countsort, n, MAX_VALUE);
        // ... und kopiere die erzeugten Werte in das Array
        // array_insertionsort
        copy_array_elements(array_insertionsort, array_countsort, n);

        // Teste ob beide Arrays auch wirklich die gleichen Werte
        // enthalten
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Eingaben für beide Algorithmen müssen für die Vergleichbarkeit gleich sein!\n");
            return -1;
        }

        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            unsigned int anzahl_befehle = 0;

            start_timer();

            // Aufruf der entsprechenden Sortieralgorithmen
            if(i==0) {
                    count_sort(array_countsort, n, &anzahl_befehle);
            } else if(i==1) {
                    insertion_sort(array_insertionsort, n, &anzahl_befehle);
            }

            // Speichere die Laufzeit sowie die Anzahl benötigter
            // Befehle
            laufzeit_array[i][j] = end_timer();
            befehle_array[i][j] = anzahl_befehle;
        }

        // Teste, ob die Ausgabe beider Algorithmen gleich sind
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Arrays sind nicht gleich. Eines muss (falsch) sortiert worden sein!\n");
            rc = -1;
        }

        // Gib den Speicherplatz wieder frei
        free(array_countsort);
        free(array_insertionsort);
    }

    // Ausgabe der Anzahl ausgeführter Befehle sowie der gemessenen
    // Laufzeiten (in Millisekunden)
    printf("Parameter MAX_VALUE hat den Wert %d\n", MAX_VALUE);
    printf("\t %32s           %32s \n", "Countsort","Insertionsort");
    printf("%8s \t %16s %16s \t %16s %16s \n", "n","Befehle", "Laufzeit","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%8d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%16u %16.4f \t ",  befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return rc;
}

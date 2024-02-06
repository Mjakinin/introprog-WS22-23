#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"
/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elemements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des Letzten Elements (Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last)
{
    // HIER Funktion merge() implementieren
    int leftSize = middle - first + 1;
    int rightSize =  last - middle;
  
    int leftArray[leftSize], rightArray[rightSize];
  
    for (int i = 0; i < leftSize; i++){
        leftArray[i] = array[first + i];
    }

    for (int j = 0; j < rightSize; j++){
        rightArray[j] = array[middle + 1+ j];
    }

    int l = 0 , r = 0;
    int k = first;

    while (l < leftSize && r < rightSize)
    {
        if (leftArray[l] <= rightArray[r])
        {
            array[k] = leftArray[l];
            l++;
        }
        else
        {
            array[k] = rightArray[r];
            r++;
        }
        k++;
    }
  
    while (l < leftSize)
    {
        array[k] = leftArray[l];
        l++;
        k++;
    }

    while (r < rightSize)
    {
        array[k] = rightArray[r];
        r++;
        k++;
    }
}
/*
 * Diese Funktion implementiert den iterativen Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array:  Pointer auf das Array
 * last :  Index des letzten Elements
 */
void merge_sort(int* array, int last)
{
    // HIER Funktion merge_sort() implementieren
    int step = 1;

    while (step <= last) {

        int left = 0;

        while (left <= last) {

            int middle = left + step - 1;

            /*if (middle > last){
                middle = last;
            }*/

            middle = (middle < last)? middle :last;

            int right = left + 2 * step - 1;

            /*if(right > last){
                last = right;
            }*/

            right = (right < last)? right :last;

            merge(array, left, middle, right);
            
            left = left + 2 * step;
        }

        step = step * 2;
    }
}
/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_iterativ <maximale anzahl> \
 * 	   <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    // Hier array initialisieren
    int* array = malloc(atoi(argv[1]) * sizeof(int));
    
    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    merge_sort(array, len-1);

    printf("Sortiert:\n");
    print_array(array, len);

    free(array);

    return 0;
}

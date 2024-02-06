#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des letzten Elements(Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last)
{
  // HIER Funktion merge() implementieren

  int B[last - first + 1];
  int k = first;
  int m = middle + 1;
  int i = 1;

  // Solange Einträge in beiden Seiten vorhanden sind
  while ((k <= middle) && (m <= last)) {
    if (array[k] <= array[m]) { // Eintrag auf linker Seite kleiner oder gleich
      B[i] = array[k];
      k++;
    } else { // Eintrag auf rechter Seite kleiner
      B[i] = array[m];
      m++;
    }
    i++; // Erhöhen der Laufvariable des gemergten Arrays
  }

  // Kopiere den "Rest" der linken Seite
  while (k <= middle) {
    B[i] = array[k];
    k++;
    i++;
  }

  // Kopiere den "Rest" der rechten Seite
  while (m <= last) {
    B[i] = array[m];
    m++;
    i++;
  }

  // Rückkopieren der gemergten Einträge
  int j = 1;
  while (j < i) {
    array[first + j - 1] = B[j]; // Hinweis: j ist mit 1 initialisiert
    j++;
  }

}

/*
 * Diese Funktion implementiert den rekursiven Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array: Pointer auf das Array
 * first: Index des ersten Elements des (Teil-)Array
 * last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last)
{
  // HIER Funktion merge_sort() implementieren
  if (first < last) {
    // Mitte mit Abrunden finden
    int middle = ((first + last) / 2);
    // Linke Seite sortieren
    merge_sort(array, first, middle);
    // Rechte Seite sortieren
    merge_sort(array, middle + 1, last);
    // Seiten zusammenführen
    merge(array, first, middle, last);
  }
}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl> \
 *         <dateipfad>
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

  merge_sort(array, 0, len-1);

  printf("Sortiert:\n");
  print_array(array, len);

  free(array);
  return 0;
}

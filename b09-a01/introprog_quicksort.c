#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

/*****************************************************
 * Die benoetigten structs findet Ihr in quicksort.h *
 *****************************************************/

void init_list(list* mylist)
{
    mylist->first = NULL;
    mylist->last = NULL;
}

// Diese Funktion fügt Listenelemente an die Liste an
void insert_list(list_element* le, list* mylist)
{
    if(mylist->first == NULL){
		mylist->first = le;
		mylist->last = le;
		mylist->last->next = NULL;
	}
	else{
		mylist->last->next = le;
		mylist->last = le;
		mylist->last->next = NULL;
	}
}

// Speicher für Listenelemente wieder freigeben
void free_list(list* mylist)
{
	list_element* current = mylist->first;
	list_element* temp = NULL;

	while(current != NULL){
		temp = current;
		current = current->next;
		free(temp->password);
		free(temp);
	}
}

// Namen, Zahlen Paare in Liste einlesen
void read_data(char* filename, list* mylist)
{
	FILE* fp = fopen(filename, "r");

	if (fp == NULL){
		perror("Fehler!");
		return;
	}

	char buffer[100];

	while (fgets(buffer,sizeof(buffer), fp) != NULL){
		char* password = strtok(buffer, " ");
		int count = atoi(strtok(NULL, " "));

		list_element* le = (list_element*)malloc(sizeof(list_element));
		le->password = strdup(password);
		le->count = count;
		le->next = NULL;
		insert_list(le, mylist);
	}
	fclose(fp);

	// HIER Code einfügen:
	// * Speicher allozieren
	// * Daten in list_element einlesen
	// * insert_list benutzen, um list_element in Liste einzufügen
}

// Liste teilen. Teillisten werden in left und right zurück gegeben
list_element* partition( list* input, list* left, list* right )
{
    list_element *pivot;

	if(input->first == NULL){
		pivot = NULL;
		input->last = NULL;
	}
	else{
		pivot = input->first;
		input->first = pivot->next;
		pivot->next = NULL;

		list_element *temp = input->first;

		while(temp != NULL){
			input->first = temp->next;

			if(input->first == NULL){
				input->last = NULL;
			}

			if(temp->count < pivot->count){
				insert_list(temp, left);
			}
			else{
				insert_list(temp, right);
			}

			temp = input->first;
		}
		
	}
	return pivot;
}

// Hauptfunktion des quicksort Algorithmus
void qsort_list(list* mylist)
{
    if(mylist->first == mylist->last){
		return;
	}
	else{
		list left;
		list right;
		init_list(&left);
		init_list(&right);

		list_element *pivot = partition(mylist, &left, &right);

		qsort_list(&left);
		qsort_list(&right);

		if(left.first == NULL){
			mylist->first = pivot;
		}
		else{
			mylist->first = left.first;
			left.last->next = pivot;
		}

		if(right.first == NULL){
			pivot->next = NULL;
			mylist->last = pivot;
		}
		else{
			pivot->next = right.first;
			mylist->last = right.last;
		}
	}
}

// Liste ausgeben
void print_list(list* mylist)
{
    if(mylist->first == NULL){
		printf("Leere Liste!\n");
		return;
	}
	
	list_element *current = mylist->first;

	while(current != NULL){
		printf("%s %d\n", current->password, current->count);
		current = current->next;
	}
    // * Laufe über die list_element in mylist und gebe sie aus.
}


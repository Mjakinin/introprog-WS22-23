#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

/*
 * Fügt einen Knoten mit der Telefonnummer phone und dem Namen name
 * in den Binären Suchbaum bst ein.  Für den Suchbaum soll die
 * Eigenschaft gelten, dass alle linken Kinder einen Wert kleiner
 * gleich (<=) und alle rechten Kinder einen Wert größer (>) haben.
 */
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
  bst_node* new_node = malloc(sizeof(bst_node));
  new_node->phone = phone;

  size_t name_len = strlen(name);
  new_node->name = malloc(name_len + 1);  // +1 für das abschließende Nullzeichen
  strncpy(new_node->name, name, name_len + 1);

  new_node->left = NULL;
  new_node->right = NULL;

  if (bst->root == NULL) {
    bst->root = new_node;
    return;
  }
  else{
    bst_node* current = bst->root;
    while (current != NULL) {

      if(phone < current->phone) {
        
        if (current->left == NULL) {

          current->left = new_node;
          return;

        } 
        else {
          current = current->left;
        }
      }
      else if (phone > current->phone) {

        if (current->right == NULL) {

          current->right = new_node;
          return;

        } 
        else {
          current = current->right;
        }
      } 
      else {
        printf("FEHLER: Die Telefonnummer %lu existiert bereits!\n", phone);
        free(new_node->name);
        free(new_node);
        return;
      }
    }
  }
}

/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
  if (bst->root == NULL) {
    return NULL;
  }

  bst_node* current = bst->root;
  while (current != NULL) {
    if (phone == current->phone) {
      return current;
    } 
    else if (phone < current->phone) {
      current = current->left;
    } 
    else {
      current = current->right;
    }
  }
  return NULL;
}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {
  if (node == NULL) {
    return;
  }

  bst_in_order_walk_node(node->left);

  print_node(node);

  bst_in_order_walk_node(node->right);
}

/* 
 * Gibt den gesamten Baum bst in "in-order" Reihenfolge aus.  Die
 * Ausgabe dieser Funktion muss aufsteigend soriert sein.
 */
void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

/*
 * Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
 * "post-order" Traversierung, d.h. zurerst wird der linke und dann
 * der rechte Teilbaum gelöscht.  Anschließend wird der übergebene
 * Knoten gelöscht.
 */
void bst_free_subtree(bst_node* node) {
  if (node == NULL) {
    return;
  }

  bst_free_subtree(node->left);

  bst_free_subtree(node->right);


  free(node->name);
  free(node);
}

/* 
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}

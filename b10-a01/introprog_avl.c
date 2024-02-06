#include <math.h>  // Für die Berechnungen der Ausgabe
#include <stdio.h> // Ein- / Ausgabe
#include <stdlib.h>

#include "avl.h"

int max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int height_recursive(AVLNode *node) {
  if (node == NULL) {
    return -1;
  } else {
    int left_height = height_recursive(node->left);
    int right_height = height_recursive(node->right);
    return 1 + max(left_height, right_height);
  }
}

int height(AVLNode *node) {
  if (node == NULL) {
    return -1;
  } else if (node->left == NULL && node->right == NULL) {
    return 0;
  } else if (node->left == NULL) {
    return node->right->height + 1;
  } else if (node->right == NULL) {
    return node->left->height + 1;
  } else {
    int left_height = node->left->height;
    int right_height = node->right->height;
    return 1 + max(left_height, right_height);
  }
}

int AVL_calculate_balance(AVLNode *node) {
  if (node == NULL) {
    return 0;
  }
  int balance = height(node->left) - height(node->right);
  return balance;
}

void AVL_in_order_walk_node(AVLNode *node) {
  if (node == NULL)
    return;
  AVL_in_order_walk_node(node->left);
  printf(" %d", node->value);
  AVL_in_order_walk_node(node->right);
}

/* Gibt den gesamten AVL Baum in "in-order" Reihenfolge aus. */
void AVL_in_order_walk(AVLTree *avlt) {
  // Hier Code implementieren!
  AVLNode *current = avlt->root;
  AVL_in_order_walk_node(current);
  printf("\n");
}

/* Diese Funktion führt eine Linksrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_left(AVLTree *avlt, AVLNode *x) {
  // Hier Code implementieren!
  AVLNode *y = x->right;
  x->right = y->left;
  // Adjust parent of y->left if it is Not NULL
  if (y->left != NULL) {
    y->left->parent = x;
  }

  // Setze y an die Stelle unter Parent an der x wäre
  y->parent = x->parent;
  if (x->parent == NULL) {
    avlt->root = y;
  } else if (x == x->parent->left) {
    // Falls x links sitzt, bewege y nach links
    x->parent->left = y;
  } else {
    // Falls x rechts sitzt, bewege y nach rechts
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
  (x->height)--;
  (y->height)++;
}

/* Diese Funktion führt eine Rechtsrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_right(AVLTree *avlt, AVLNode *y) {
  // Hier Code implementieren!
  AVLNode *x = y->left;
  y->left = x->right;
  if (x->right != NULL) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == NULL) {
    avlt->root = x;
  } else if (y == y->parent->right) {
    y->parent->right = x;
  } else {
    y->parent->left = x;
  }
  x->right = y;
  y->parent = x;
  (x->height)++;
  (y->height)--;
}

/* Balanciere den Teilbaum unterhalb von node.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen _nicht_
 * angepasst werden, da dieses schon in den Rotationen geschieht.
 * Falls dies nicht eingehalten wird funktionieren die Unit-Tests
 * ggf. nicht.
 */
void AVL_balance(AVLTree *avlt, AVLNode *node) {
  // Hier Code implementieren!
  int balance = AVL_calculate_balance(node);
  if (abs(balance) < 2) {
    return;
  }
  if (balance > 1) {
    if (height(node->left->left) < height(node->left->right)) {
      AVL_rotate_left(avlt, node->left);
    }
    AVL_rotate_right(avlt, node);
  } else if (balance < 1) {
    if (height(node->right->right) < height(node->right->left)) {
      AVL_rotate_right(avlt, node->right);
    }
    AVL_rotate_left(avlt, node);
  }
}

/* Fügt der Wert value in den Baum ein.
 *
 * Die Implementierung muss sicherstellen, dass der Baum nach dem
 * Einfügen immer noch balanciert ist!
 */
void AVL_insert_value(AVLTree *avlt, int value) {
  // Hier Code implementieren!
  AVLNode *new_node = malloc(sizeof(AVLNode));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;
  new_node->value = value;
  new_node->height = 0;

  if (avlt->root == NULL) {
    avlt->root = new_node;
    avlt->numberOfNodes++;
    return;
  }

  AVLNode *node = avlt->root;
  AVLNode *parent = NULL;
  while (node != NULL) {
    if (value < node->value) {
      parent = node;
      node = node->left;
    } else if (value > node->value) {
      parent = node;
      node = node->right;
    } else {
      free(new_node);
      return;
    }
  }
  if (value < parent->value) {
    parent->left = new_node;
    parent->left->parent = parent;
  } else if (value > parent->value) {
    parent->right = new_node;
    parent->right->parent = parent;
  } else {
    free(new_node);
    return;
  }
  AVLNode *current = parent;
  while (current != NULL) {
    current->height = height_recursive(current);
    current = current->parent;
    AVL_balance(avlt, current);
  }
  avlt->numberOfNodes++;
}

void AVL_remove_element(AVLNode *node) {
  if (node == NULL) {
    return;
  }
  AVL_remove_element(node->left);
  AVL_remove_element(node->right);
  free(node);
}

/* Löscht den gesamten AVL-Baum und gibt den Speicher aller Knoten
 * frei.
 */
void AVL_remove_all_elements(AVLTree *avlt) {
  // Hier Code implementieren!
  AVL_remove_element(avlt->root);
  avlt->root = NULL;
}

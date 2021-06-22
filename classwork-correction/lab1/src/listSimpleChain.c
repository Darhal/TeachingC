#include "listSimpleChain.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Liste list_creer()
{
  Liste l;
  l.head = NULL;
  return l;
}

int list_estVide(Liste l)
{
  return !l.head;
}


Liste list_ajoutTete(Liste l, ELEMENT e)
{
    cellule* old_head = l.head;
    l.head = malloc(sizeof(cellule));
    l.head->val = e;
    l.head->suiv = old_head;
    return l;
}

void list_ajoutFin(Liste l, ELEMENT e)
{
    cellule* prev = l.head;

    while (prev->suiv) {
      prev = prev->suiv;
    }

    prev->suiv = malloc(sizeof(cellule));
    prev->suiv->val = e;
    prev->suiv->suiv = NULL;
}

void list_ajoutN(Liste l, ELEMENT e, int n)
{
  if (n < 0)
    return;

  cellule* prev = l.head;
  n--;

  while (prev->suiv && n) {
    prev = prev->suiv;
    n--;
  }

  if (!n){
    cellule* next = prev->suiv;
    prev->suiv = malloc(sizeof(cellule));
    prev->suiv->val = e;
    prev->suiv->suiv = next;
  }
}

ELEMENT list_rechN(Liste l, const char* s, int n)
{
  if (n < 0)
    return NULL;

  cellule* curr = l.head;

  while (curr && n) {
    if (!strcmp(s, curr->val)){
      return curr->val;
    }

    curr = curr->suiv;
    n--;
  }

  return NULL;
}

ELEMENT list_rech(Liste l, const ELEMENT s)
{
  if (!s)
    return NULL;

  cellule* curr = l.head;

  while (curr) {
    if (!strcmp(s, curr->val)){
      return curr->val;
    }

    curr = curr->suiv;
  }

  return NULL;
}

Liste list_remove(Liste l, ELEMENT e)
{
  if (!e)
    return l;

  cellule* curr = l.head;
  cellule* prev = NULL;

  while (curr) {
    if (!strcmp(e, curr->val)) {
      cellule* to_free = curr;

      if (prev){ // we are not in head
        prev->suiv = curr->suiv;
      }else{
        l.head = curr->suiv;
      }

      free(to_free->val); // free val
      free(to_free); // free node
      return l; // first occur
    }

    prev = curr;
    curr = curr->suiv;
  }

  return l;
}

Liste list_removeN(Liste l, int n)
{
  if (n < 0)
    return l;

  cellule* curr = l.head;
  cellule* prev = NULL;

  while (curr) {
    if (!n) {
      cellule* to_free = curr;

      if (prev){ // we are not in head
        prev->suiv = curr->suiv;
      }else{
        l.head = curr->suiv;
      }

      free(to_free->val); // free val
      free(to_free); // free node
      return l;
    }

    prev = curr;
    curr = curr->suiv;
    n--;
  }

  return l;
}

void list_affiche(ELEMENT e)
{
  printf("%s", e);
}

void list_visualiser(Liste l)
{
  cellule* curr = l.head;

  while (curr) {
    list_affiche(curr->val);
    printf(" -> ");
    curr = curr->suiv;
  }

  printf("NULL\n");
}

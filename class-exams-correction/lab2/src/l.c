#include "l.h"
#include <stdlib.h>

Liste list_creer(void)
{
  return NULL;
}

void list_detruire(Liste l)
{
  Liste curr = l;

  while (curr) {
    Liste c = curr;
    curr = curr->suiv;
    free(c->val);
    free(c);
  }
}

int list_estVide(Liste l)
{
  return l == NULL;
}

Liste list_ajoutTete(Liste l, ELEMENT e)
{
  Liste liste = malloc(sizeof(struct cellule));
  liste->val = strdup(e);
  liste->suiv = l;
  return liste;
}

int list_rechN(Liste l, ELEMENT e, int n)
{
  if (n < 0 || !e)
    return 0;

  Liste curr = l;

  while (curr && n) {
    if (!strcmp(e, curr->val)){
      return 1;
    }

    curr = curr->suiv;
    n--;
  }

  return 0;
}

int list_rech(Liste l, ELEMENT e)
{
  if (!e)
    return 0;

  Liste curr = l;

  while (curr) {
    if (!strcmp(e, curr->val)){
      return 1;
    }

    curr = curr->suiv;
  }

  return 0;
}

void list_affiche(char* e)
{
  printf("%s", e);
}

void list_visualiser(Liste l)
{
  Liste curr = l;

  while (curr) {
    list_affiche(curr->val);
    printf(" -> ");
    curr = curr->suiv;
  }

  printf("NULL\n");
}
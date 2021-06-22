#include <stdio.h>
#include <string.h>

typedef char* ELEMENT;
struct cellule {
   ELEMENT val;
   struct cellule * suiv;
} ;

typedef struct cellule* Liste;

Liste list_creer(void); //

void list_detruire(Liste l);

int list_estVide(Liste l);

Liste list_ajoutTete(Liste l, ELEMENT e);

int list_rechN(Liste l, ELEMENT e, int n);

void list_affiche(ELEMENT e);

void list_visualiser(Liste l);

int list_rech(Liste l, ELEMENT e);




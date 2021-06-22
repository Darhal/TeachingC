
typedef char* ELEMENT ;

typedef struct cellule_t
{
  ELEMENT val;
  struct cellule_t* suiv;
} cellule;

typedef struct Liste_t
{
  cellule* head;
} Liste;

Liste list_creer();
int list_estVide(Liste l);
Liste list_ajoutTete(Liste l, ELEMENT e);
void list_ajoutFin(Liste l, ELEMENT e);
void list_ajoutN(Liste l, ELEMENT e, int n);
ELEMENT list_rechN(Liste l, const char* s, int n);
ELEMENT list_rech(Liste l, const ELEMENT s);
Liste list_remove(Liste L, ELEMENT e);
Liste list_removeN(Liste l, int n);
void list_affiche(ELEMENT e);
void list_visualiser(Liste l);

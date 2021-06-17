#include <stdio.h>

struct table_hachage
{
  int N;
  Liste* table;
};

typedef struct table_hachage table_h;

table_h* alloue_h(int n);

int func_h(ELEMENT c, table_h *h);

Liste* charge_dico(char *f,table_h *h); // ret void

void ajout_dico(char *f,table_h *h); // ret void

int recherche_dico(ELEMENT mot,table_h *h);

void free_hachage(table_h *h); // table_detruire



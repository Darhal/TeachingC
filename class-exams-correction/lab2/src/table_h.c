#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "l.h"
#include "divers.h"
#include "table_h.h"

/**fonction d'allocation de la table de hachage: retour d'une structure de type table_hachage ****/

table_h* alloue_h(int n)
{
  table_h* tab = malloc(sizeof(table_h));
  tab->N = n;
  tab->table = malloc(sizeof(Liste) * n);

  for (int i = 0; i < n; i++)
    tab->table[i] = list_creer();
  return tab;
}




/*fonction de hachage:calcul de la cle de hachage*/

int func_h(ELEMENT c,table_h* h)
{
  int res=0;
  int cle = 0;

  ELEMENT p=c;
  //strcpy(p,c);
  int i = 0;
//printf("%s",p);

for(i=0;p[i]!='\0';i++)
{
  res = res + p[i];
}

cle = res % (h->N);
//printf("%d\n",cle);
return cle;
}



/*fonction de chargement du dico dans la table de hachage*/

Liste* charge_dico(char* f, table_h* h)
{
  int nb = nbligne(f);
  FILE* fp = fopen(f,"rt");
  
  for (int i = 0; i < nb; i++) {
    char mot[512];
    lecture(fp, mot);
    ajout_dico(mot, h);
  }

  fclose(fp);
  return h->table;
}

void ajout_dico(char* f, table_h* h)
{
  int hash = func_h(f, h);
  h->table[hash] = list_ajoutTete(h->table[hash], f);
}



/*fonction de recherche d'un mot dans la table de hachage*/

int recherche_dico(ELEMENT mot,table_h* h)
{
  int hash = func_h(mot, h);
  return list_rech(h->table[hash], mot);
}

/****fonction de desallocaton de la table****/

void free_hachage(table_h* h)
{
  for (int i = 0; i < h->N; i++)
    list_detruire(h->table[i]);
  free(h->table);
  free(h);
}

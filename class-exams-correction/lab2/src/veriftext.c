#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "l.h"
#include "divers.h"
#include "table_h.h"


int main()
{
  int n=0;
  int count_lut=0,count_absent=0,count_charge_par_liste=0,count_charge=0;
  int i,max=0,min=123456;
  char mot[256];
  clock_t debutchargement,finchargement,debutrecherche,finrecherche;

  FILE *fd,*fp;

  table_h *h;

  printf("entrer la taille de la table ");
  scanf("%d",&n);

  h=alloue_h(n);


puts("****************chargement du dico**********************");

  debutchargement=clock();

  h->table=charge_dico("1.txt",h);

  finchargement=clock();

  fp=fopen("script.txt","w");

  fprintf(fp,"taille de la table:%d\n",n);

  for(i=0;i<n;i++)
    {
        Liste p = h->table[i];
        list_visualiser(p);
        
        while (p){
          count_charge_par_liste++;
          count_charge++;
          p = p->suiv;
        }

        max=max_int(max,count_charge_par_liste);
        min=min_int(min,count_charge_par_liste);
        fprintf(fp,"cle=%d         nombre de mots:%d\n\n",i,count_charge_par_liste);
        count_charge_par_liste=0;

    }

fprintf(fp,"nombre de mots charges:%d\n",count_charge);
fprintf(fp,"nombre de mots en moyenne dans chaque liste:%d\n",(int)((max+min)/2));
fprintf(fp,"nombre max de mots charges dans une liste:%d\n",max);
fprintf(fp,"nombre min de mots charges dans une liste:%d\n",min);
fprintf(fp,"duree chargement= %f sec\n\n",( (double)(finchargement-debutchargement)/CLOCKS_PER_SEC));

    puts("dico charge");
    puts("appuyer sur une touche pour continuer");
    getchar();



puts("****************recherche dans sand.txt*****************");

  fd=fopen("2.txt","r");

  debutrecherche=clock();

  while(!feof(fd))
    {
      lecture(fd,mot);
      count_lut++;

      if(recherche_dico(mot,h)==0)
        {
            printf("mot: %s       trouve\n",mot);
            printf("");
        }
      else
        {
            fprintf(fp,"mot: %s          absent ",mot);
            printf("");

            count_absent++;
        }
    }

  finrecherche=clock();

  fclose(fd);

fprintf(fp,"duree recherche=%f sec\n",((double)(finrecherche-debutrecherche)/CLOCKS_PER_SEC));
fprintf(fp,"nombre de mots luts: %d \n",count_lut);
fprintf(fp,"nombre de mots absents du dico: %d \n\n",count_absent);

    puts("recherche terminee");
puts("consulter le fichier script.txt pour un compte rendu");
    fclose(fp);

  free_hachage(h);

  return 0;
}

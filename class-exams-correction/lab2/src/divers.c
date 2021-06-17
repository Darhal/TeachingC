#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nbligne(char *fic) { 
	FILE* fp; 
	int c=0; 
	char flag=0;
  	if ( (fp=fopen(fic,"rt"))==NULL) return 0;
  	else
    		while (!feof(fp))
      	if (fgetc(fp)=='\n') {
			if (flag) 
				c++; 
			flag=0;
		}
      	else flag=1;
  	return c;
}

void lecture(FILE* fp, char* mot) {
	char inter[512];
	int i,j;
	fscanf(fp,"%[^\n -]s",mot); 
	fscanf(fp,"%*c");
	for (i=j=0; mot[i]; i++)
    		if (!ispunct(mot[i])) 
			inter[j++]=mot[i];
    		else if (mot[i]=='-' && mot[i+1]!=0 && !ispunct(mot[i+1]) && !isspace(mot[i+1])) 
			inter[j++]=mot[i];
         	else if (mot[i]=='\'') 
			j=0;
  	inter[j]=0;
  	strcpy(mot,inter);
}


int max_int(int x,int y)
{
    int z= x>y ? x:y;

    return z;
}

int min_int(int x,int y)
{
    int z= x<y ? x:y;

    return z;
}



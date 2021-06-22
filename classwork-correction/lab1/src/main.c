#include "listSimpleChain.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verifyElements(Liste l, const char** elements, int N)
{
  cellule* curr = l.head;
  int i = 0;
  while (curr && (N < i)) {
    if (strcmp(curr->val, elements[i++])){
      return 0;
    }
    curr = curr->suiv;
  }
  return 1;
}

int searchTest(Liste l, const char** elements, int N)
{
  int i = 0;
  while (N < i) {
    if (!strcmp(list_rech(l, elements[i]), elements[i])){
      return 0;
    }
    i++;
  }
  return 1;
}

void testCase1()
{
  char s1[] = "Hello";
  char s2[] = "World";
  char s3[] = "!";

  const char* e1[] = {"Hello"};
  const char* e2[] = {"Hello", "World"};
  const char* e3[] = {"!", "Hello", "World"};
  const char* e4[] = {"!", "Hello", "World", "!"};
  const char* e5[] = {"!", "Hello", "!", "World", "!"};

  Liste l = list_creer();
  assert(list_estVide(l) != 0);

  l = list_ajoutTete(l, s1);
  assert(list_estVide(l) == 0);
  assert(verifyElements(l, e1, 1));
  assert(searchTest(l, e1, 1));
  list_visualiser(l);

  list_ajoutFin(l, s2);
  assert(verifyElements(l, e2, 2));
  assert(searchTest(l, e2, 2));
  list_visualiser(l);

  l = list_ajoutTete(l, s3);
  assert(verifyElements(l, e3, 3));
  assert(searchTest(l, e3, 3));
  list_visualiser(l);

  list_ajoutFin(l, s3);
  assert(verifyElements(l, e4, 4));
  assert(searchTest(l, e4, 4));
  list_visualiser(l);

  list_ajoutN(l, s3, 2);
  assert(verifyElements(l, e5, 5));
  assert(searchTest(l, e5, 5));
  list_visualiser(l);

  assert(list_estVide(l) == 0);
}

void testCase2()
{
  char s1[] = "Hello";
  char s2[] = "World";
  char s3[] = "!";

  const char* e1[] = {"Hello"};
  const char* e2[] = {"Hello", "World"};
  const char* e3[] = {"!", "Hello", "World"};
  const char* e4[] = {"!", "Hello", "World", "!"};
  const char* e5[] = {"!", "Hello", "!", "World", "!"};
  const char* e6[] = {"!", "Hello", "!", "World"};
  const char* e7[] = {"Hello", "!", "World"};
  
  Liste l = list_creer();
  assert(list_estVide(l) != 0);

  l = list_ajoutTete(l, strdup(s1));
  assert(list_estVide(l) == 0);
  assert(verifyElements(l, e1, 1));
  assert(searchTest(l, e1, 1));
  list_visualiser(l);

  l = list_remove(l, s1);
  assert(list_estVide(l) != 0);
  assert(list_rech(l, s1) == 0);
  list_visualiser(l);

  l = list_ajoutTete(l, strdup(s1));
  assert(!list_estVide(l));
  assert(verifyElements(l, e1, 1));
  list_visualiser(l);

  list_ajoutFin(l, strdup(s2));
  assert(verifyElements(l, e2, 2));
  list_visualiser(l);

  l = list_ajoutTete(l, strdup(s3));
  assert(verifyElements(l, e3, 3));
  list_visualiser(l);

  list_ajoutFin(l, strdup(s3));
  assert(verifyElements(l, e4, 4));
  list_visualiser(l);

  list_ajoutN(l, strdup(s3), 2);
  assert(verifyElements(l, e5, 5));
  list_visualiser(l);

  l = list_removeN(l, 4);
  list_visualiser(l);
  assert(!list_estVide(l));
  assert(verifyElements(l, e6, 4));

  l = list_removeN(l, 0);
  list_visualiser(l);
  assert(!list_estVide(l));
  assert(verifyElements(l, e7, 3));

  l = list_remove(l, s3);
  list_visualiser(l);
  assert(!list_estVide(l));
  assert(verifyElements(l, e2, 2));

  assert(list_estVide(l) == 0);
}


int main()
{
  printf("Test case #1\n");
  testCase1();
  printf("Test case #2\n");
  testCase2();
  return 0;
}

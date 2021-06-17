# C/SD - Examen Machine

**Date:** 01/06/2021
**Durée:** 2h

### Documents et ressources autorisés

Seuls les outils et document suivants sont autorisés : 

- votre environnement de développement C
- un terminal pour compiler/exécuter votre code
- un onglet de navigateur ouvert sur la plateforme GitLab de l'école : 
  
    http://gitlab.telecomnancy.univ-lorraine.fr/
- un onglet de navigateur ouvert sur la section 3 des *man-pages* : 
  
    https://man7.org/linux/man-pages/dir_section_3.html

**Tout autre consultation entraînera l'invalidation immédiate de l'examen et du module.**

En particulier vous **n'êtes pas autorisé à accéder** au code que vous aviez réalisé pour les TPs/TDs.

### Propos liminaires

L'examen sur machine se déroule comme suit :

- récupérez sur votre machine le dépôt git de l'examen (ce dépôt nommé `c2k21/lab-exam2-<votre_login>` devrait être visible dans votre liste de projet sur la plateforme gitlab de l'école).
- Il est **très fortement** conseillé de committer/pousser régulièrement (a minima **après chaque question**) le code que vous avez produit et **de ne pas attendre la fin de la séance !**
- Ne touchez plus votre code ni aucun de vos fichiers après la fin de l'épreuve. Toute modification de fichier ou du dépôt git hors délai sera considéré comme une fraude et entrainera l'invalidation de l'examen ;
- Le dépôt sur git vaut rendu de copie. Si vous n'arrivez pas à réaliser cette étape, envoyer impérativement avant la fin de l'épreuve vos fichiers par courriel à Christophe.Bouthier@telecomnancy.eu et Gerald.Oster@telecomnancy.eu.

## Rendu

Ce travail est à rendre au plus tard **à 10:00** sur la plateforme GitLab de l'école.

### Tests unitaires

Dans votre dépôt, vous disposez d'une branche `tests` contenant un certain nombre de scripts `bash` et de programmes `.c` permettant de tester votre code.

Nous exécuterons de manière automatisée (en utilisant le serveur d'intégration continue de la plateforme GitLab) ces tests sur votre code afin de connaître l'état de votre rendu. Vous pouvez consulter ces tests (sans y être obligé) de différentes manières :
- en consultant le contenu de la branche `tests` par l'interface web de la plateforme GitLab
- en consultant le contenu de la branche `tests` par l'intermédiaire de la commande `git checkout`
- en fusionnant la branche `tests` dans votre branche `master` par l'intermédiaire de la commande `git merge`

- À la racine de votre dépôt (si vous avez fusionner la branche `tests`), vous trouverez un script `./check.sh` qui vérifie la présence des fichiers attendus, compile le code et exécute les différents tests. Pensez à regarder au début de ce script pour fournir le bon chemin vers votre compilateur et modifier si nécessaire les options de compilation.

## Exercice 0 : Votre nom

1. Créer un fichier `name.txt` dans lequel vous indiquez votre nom/prénom.

2. Ajouter ce fichier, committer et pousser sur le serveur gitlab cette première contribution.


## Exercice 1 : Hello world

1. Dans un fichier `helloworld.c`, écrivez un programme permettant d'afficher le message `Ph'nglui mglw'nafh Cthulhu.` sur la sortie standard.

   Si vous avez besoin d'aide concernant une fonction de la librairie C, nous vous invitons à consulter la page `man` dédiée à cette fonction (i.e. pour obtenir la documentation de la fonction `printf` vous pouvez utiliser la commande `man 3 printf`).

2. Compilez et exécutez ce programme.

3. Ajouter le fichier `helloworld.c`, committer et pousser sur le serveur gitlab cette première contribution.


## Exercice 2 : Entrées/sorties et fonctions

1. Dans un fichier `max3.c` (et un fichier d'entête `max3.h`), écrivez une fonction `int max (int a, int b, int c)` qui calcule le maximum de 3 valeurs entières. 
    
2. Dans un fichier `max3_stdin.c`, écrivez un programme qui calcule le maximum de 3 valeurs entières. Cette fois-ci, le programme demandera à l'utilisateur de saisir les 3 valeurs entières sur l'entrée standard (une valeur par ligne).
 
3. Dans un fichier `max3_args.c`, écrivez un programme qui calcule le maximum de 3 valeurs entières Cette fois-ci, le programme demandera à l'utilisateur de passer les 3 valeurs entières en paramètre sur la ligne de commande. Par exemple, la commande attendues pourrait être `./max3_args 1 -42 666`.

   **Remarque :** Vous serez amené à utiliser la fonction `atoi` de la librairie standard pour convertir une chaîne de caractères en une valeur entière.

4. Si ce n'est pas déjà fait, ajouter les fichiers `max3.c`, `max3.h`, `max3_stdin.c` et  `max3_args.c`, committer et pousser sur le serveur gitlab cette première contribution.


## Exercice 3 : Entrées/sorties et tableaux

Il est possible d'identifier le signe astrologique d'une personne en fonction de sa date de naissance. Pour cela, il suffit de consulter le tableau ci-dessous :

| Signe | Dates | | Signe | Dates |
|:------|:------|-|:------|:------|
| Bélier     | 21/3 au 19/4 | | Balance    | 23/9 au 22/10 |
| Taureau    | 20/4 au 20/5 | | Scorpion   | 23/10 au 21/11 |
| Gémeaux    | 21/5 au 20/6 | | Sagittaire  | 22/11 au 21/12 |
| Cancer     | 21/6 au 21/7 | | Capricorne | 22/12 au 19/1 |
| Lion       | 22/7 au 22/8 | | Verseau    | 20/1 au 18/2 |
| Vierge     | 23/8 au 22/9 | | Poisson    | 19/2 au 20/3 |


1. Écrivez un programme prenant en paramètre (en argument de la ligne de commande) la date de naissance d'un utilisateur (au format jour/mois/année) et qui affiche en retour son signe astrologique. On imposera que l'année de la date saisie soit positive et non nulle. Si la date saisie n'est pas valide, affichez un message d'erreur et quitter le programme avec un code de retour non nul.

   Vous découperez votre programme en plusieurs fonctions (validation de la date, calcul du signe astrologique, etc.)

   Vous proposerez un algorithme reposant sur des tableaux qui mémorisent les signes astrologiques et leur dates d'effet pour réaliser ce programme. (Il ne s'agit pas ici de faire un énorme `if... else... else if...` ni d'utiliser une construction du type `switch... case...` mais plutôt une variante d'une boucle de recherche).

   Les fichiers attendus sont :
   - `zodiac.h`, un fichier d'entêtes contenant les prototypes des fonctions de calcul (validation date, calcul signe astrologique, etc.).
   - `zodiac.c`, un fichier de code source contenant le code des fonctions de calcul.
   - `zodiac_main.c`, un fichier de code source principal faisant appel aux fonctions définies dans le fichier `zodiac.c`. Ce programme lit ses entrées sur la ligne de commande et affiche le résultat (l'intitulé du signe du zodiac) sur la sortie standard. Par exemple, la commande attendues pourrait être `./zodiac_main 20/8/1890`.
 
   **Remarque :** Vous pourrez être amené à utiliser la fonction `sscanf` de la librairie standard.

2. Si ce n'est pas déjà fait, ajouter les fichiers `zodiac.h`, `zodiac.c` et `zodiac_main.c`, committer et pousser sur le serveur gitlab cette première contribution.


## Exercice 4 : Petit livre noir

Vous devez écrire un programme en C permettant de gérer un carnet d'adresses simplifié qui conserve le nom de personnes et leur numéro de téléphone.

Vous répartirez votre code uniquement dans les 3 fichiers suivants : `directory.h` et `directory.c`. Il est *fortement recommandé de committer/pousser votre code* au moins une fois après chacune des questions suivantes. Nous vous fournissons un fichier `directory_main.c` qui peut vous servir de tests.

**Question 1.** Créer une structure `person_t` pouvant contenir les informations de contact d'une personne (nom et numéro de téléphone sous forme de chaînes de caractères).  

**Question 2.** Ecrire une fonction `person_create` qui crée et retourne un pointeur sur une structure `person_t` à partir d'un nom et d'un numéro de téléphone passés tout deux en paramètre (nous vous recommandons fortement de dupliquer les chaînes de caractères passées en paramètre). Ecrire une fonction `person_destroy` permettant de libérer la mémoire allouée lors de la création d'une personne.

**Question 3.** Ecrire une fonction `person_display` qui affiche (sur la sortie standard) les informations contenues dans la structure `person_t` dont un pointeur est passé en argument. L'affichage ce fera sur une seule ligne, le nom et le numéro de téléphone étant séparés par un point virgule. Par exemple, `Libby Kate ; 555-4202`.

**Question 4.** Créer une nouvelle structure `directory_t` qui va représenter le carnet d'adresses. Cette structure contiendra un tableau associatif -- implémenté en utilisant une **table de hachage** -- et un compteur indiquant le nombre de personnes enregistrées dans l'annuaire. Ajouter les fonctions `directory_create` et `directory_destroy`. La fonction `directory_create` prendra en paramètre une valeur entière permettant d'indiquer la taille de la table d'index (et *non pas* la taille maximale du nombre d'entrée dans le carnet d'adresses).

**Remarque :** Vous trouverez ci-dessous l'implémentation d'une fonction de hachage qui pourrait vous être utile (la fonction retourne un entier naturel entre 0 et *n-1*).
```c
int hash(char *str, int n) {
    int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    hash = ((hash % n) + n) % n;
    return hash;
}
```

**Question 5.** Ecrire une fonction `directory_add_person` qui ajoute une personne dans un carnet, tous deux passés en paramètre (par pointeurs).


**Question 6.** Ecrire une fonction `directory_stats` qui affiche sur la sortie standard les informations suivantes (une information par ligne) : la taille de la table d'index, le nombre total d'entrées (de personnes) dans la table, pour chaque index de la table le nombre d'entrées stockées (le nombre de personnes). Par exemple :
```
3
42
13
15
14
```

**Question 7.** Ecrire une fonction `directory_display` qui affiche un carnet d'adresses sous le format suivant : une entrée par ligne, nom suivi du numéro de téléphone, tous deux séparés par un point virgule. Par exemple :
```
Waelchi Athena ; 0699186690
Pagac Eliezer ; 0033724577910
Abshire Chester ; 555-2368
Gleason Gabrielle ; 634-5789
Libby Kate ; 555-4202
...
```


/*
#include "directory.h"

int main()
{
    person_t* p1 = person_create("Waelchi Athena", "0699186690");
    person_t* p2 = person_create("Pagac Eliezer", "0033724577910");
    person_t* p3 = person_create("Abshire Chester", "555-2368");
    person_t* p4 = person_create("Gleason Gabrielle", "634-5789");
    person_t* p5 = person_create("Libby Kate", "555-4202");

    directory_t* d = directory_create(3);
    directory_add_person(d, p1);
    directory_add_person(d, p2);
    directory_add_person(d, p3);
    directory_add_person(d, p4);
    directory_add_person(d, p5);

    directory_stats(d);
    directory_display(d);

    person_destroy(p1);
    person_destroy(p2);
    person_destroy(p3);
    person_destroy(p4);
    person_destroy(p5);
    directory_destroy(d);
}

*/

#include "directory.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int main() {
    directory_t* d = directory_create(3);

    printf("#1 - Empty directory\n");
    directory_stats(d);
    directory_display(d);
    printf("\n");

    printf("#2 - Adding a single person\n");
    person_t* p1 = person_create("Harry Potter", "907-225-4010");
    directory_add_person(d, p1);
    directory_stats(d);
    directory_display(d);
    printf("\n");

    printf("#3 - Adding multiple persons (more than capacity of index)\n");
    person_t* p2 = person_create("Severus Snape", "393.221.9765");
    directory_add_person(d, p2);

    person_t* p3 = person_create("Albus Dumbledore", "884.790.7049");
    directory_add_person(d, p3);

    person_t* p4 = person_create("Hermione Granger", "(242) 865-6859 x095");
    directory_add_person(d, p4);

    directory_stats(d);
    directory_display(d);
    printf("\n");


    printf("#4 - Adding a lot of random persons\n");
    person_t* crowd[255];
    for (int i=0; i<255; i++) {
        char* name = strdup("John Doe");
        name[5] = '\0';
        sprintf(name + 5,"%d", i);
        crowd[i] = person_create(name, "555");
        free(name);
        directory_add_person(d, crowd[i]);
    } 
    directory_stats(d);
    //directory_display(d);
    printf("\n");

    printf("#5 - Freeing up memory\n");

    directory_destroy(d);
    person_destroy(p1);
    person_destroy(p2);
    person_destroy(p3);
    person_destroy(p4);

    for (int i=0; i<255; i++) {
        person_destroy(crowd[i]);
    } 
}
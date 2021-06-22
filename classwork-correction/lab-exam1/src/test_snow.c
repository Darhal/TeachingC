#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "library.h"

#include "snow.h"

#define assert_false(a) asserteq(a, 0)
#define assert_true(a) assertneq(a, 0)

#if defined(Q1)
book *le_silmarillion = NULL;
book *l_appel_de_cthulhu = NULL;
book *le_hobbit = NULL;

describe(Q1_book) {

    it("creating book (Le Silmarillion) and check title and author are set properly") {
        le_silmarillion = book_init("Le Silmarillion", "J. R. R. Tolkien");
        assertneq(le_silmarillion, NULL);
        char *copy = strdup("Le Silmarillion");
        asserteq_str(book_get_title(le_silmarillion), copy);
        free(copy);

        copy = strdup("J. R. R. Tolkien");
        asserteq_str(book_get_author(le_silmarillion), copy);
        free(copy);
    }
    it("creating a second book (L'Appel de Cthulhu) and check title and author are set properly") {
        l_appel_de_cthulhu = book_init("L'Appel de Cthulhu", "H. P. Lovecraft");
        assertneq(l_appel_de_cthulhu, NULL);
        char *copy = strdup("L'Appel de Cthulhu");
        asserteq_str(book_get_title(l_appel_de_cthulhu), copy);
        free(copy);

        copy = strdup("H. P. Lovecraft");
        asserteq_str(book_get_author(l_appel_de_cthulhu), copy);
        free(copy);
    }
    it("creating a third book (Le Hobbit) and check unicity of ids") {
        le_hobbit = book_init("Le Hobbit", "J. R. R. Tolkien");

        int le_silmarillion_id = book_get_id(le_silmarillion);
        int l_appel_de_cthulhu_id = book_get_id(l_appel_de_cthulhu);
        int le_hobbit_id = book_get_id(le_hobbit);

        assertneq(le_silmarillion_id, l_appel_de_cthulhu_id);
        assertneq(le_silmarillion_id, le_hobbit_id);
        assertneq(l_appel_de_cthulhu_id, le_hobbit_id);
    }
}

#endif

#if defined(Q2)

describe(Q2_book) {
    it("freeing") {
        book_destroy(le_silmarillion);
        book_destroy(l_appel_de_cthulhu);
        book_destroy(le_hobbit);
        assert_true(1);
    }
}

#endif

#if defined(Q5)
library * bibliotheque = NULL;

describe(Q5_library) {

    library * bibliotheque = NULL;
    it("creating a library and check it is empty") {
        bibliotheque = library_init(10);
        asserteq(library_books_count(bibliotheque), 0);    
        //assert_false(library_is_book_available(bibliotheque, "Le Silmarillion"));    
        library_destroy(bibliotheque);
    }

}

#endif

#if defined(Q6)
//book *le_silmarillion = NULL;

describe(Q6_library) {

    le_silmarillion = book_init("Le Silmarillion", "J. R. R. Tolkien");
    it("registering a book to library") {
        bibliotheque = library_init(10);
//        assert_false(library_is_book_available(bibliotheque, "Le Silmarillion"));    
        library_register_book(bibliotheque, le_silmarillion);
        asserteq(library_books_count(bibliotheque), 1);    
//        assert_true(library_is_book_available(bibliotheque, "Le Silmarillion"));  
    }

    it("registering the same book again to the library") {
        library_register_book(bibliotheque, le_silmarillion);
        asserteq(library_books_count(bibliotheque), 1);  
        // now there should be two copies available in the library  
    }
//    library_destroy(bibliotheque);

}

#endif

#if defined(Q7)
//book *l_appel_de_cthulhu = NULL;
//book *le_hobbit = NULL;

describe(Q7_library) {
    l_appel_de_cthulhu = book_init("L'Appel de Cthulhu", "H. P. Lovecraft");
    le_hobbit = book_init("Le Hobbit", "J. R. R. Tolkien");

    it("registering a second and a third books to the library") {
        library_register_book(bibliotheque, l_appel_de_cthulhu);
        asserteq(library_books_count(bibliotheque), 2);    
        assert_true(library_is_book_available(bibliotheque, "L'Appel de Cthulhu"));    
        assert_false(library_is_book_available(bibliotheque, "Le Hobbit"));    

        library_register_book(bibliotheque, le_hobbit);
        asserteq(library_books_count(bibliotheque), 3);    
        assert_true(library_is_book_available(bibliotheque, "L'Appel de Cthulhu"));    
        assert_true(library_is_book_available(bibliotheque, "Le Hobbit"));    
    }

}
#endif

#if defined(Q7B)

describe(Q7B_library) {

    it("looking for a non-existant book with a dummy id") {
        book *res = library_find_by_id(bibliotheque, 420666042L);
        asserteq(res, NULL); // we expect that random id is not bound to any book

        res = library_find_by_id(bibliotheque, 170676049L);
        asserteq(res, NULL); // we expect that random id is not bound to any book
    }

    int le_silmarillion_id = book_get_id(le_silmarillion);
    int l_appel_de_cthulhu_id = book_get_id(l_appel_de_cthulhu);
    int le_hobbit_id = book_get_id(le_hobbit);
    it("looking for registered books with their ids") {
        book *res = library_find_by_id(bibliotheque, le_silmarillion_id);
        asserteq(res, le_silmarillion);

        res = library_find_by_id(bibliotheque, l_appel_de_cthulhu_id);
        asserteq(res, l_appel_de_cthulhu);
        asserteq_str(book_get_title(res), "L'Appel de Cthulhu");
        asserteq_str(book_get_author(res), "H. P. Lovecraft");

        res = library_find_by_id(bibliotheque, le_hobbit_id);
        asserteq(res, le_hobbit);
    }

}
#endif

#if defined(Q7C)

describe(Q7C_library) {

    it("looking for a registered book using its title") {
        // we first build the title string (to be sure that strcmp is used and not ==)
        char *buffer = (char *) calloc(10, sizeof(char));
        strcat(buffer, "Le ");
        strcat(buffer, "Hobbit");
        book* res = library_find_by_title(bibliotheque, buffer);
        asserteq(res, le_hobbit);
        free(buffer);

    }

    it("looking for a non-existing book using its title") {
        book* res = library_find_by_title(bibliotheque, "The Tales of Beedle the Bard");
        asserteq(res, NULL);
    }

}

#endif

#if defined(Q8)

book* les_contes_de_beedle_le_bard = NULL;

describe(Q8_library) {

    it("borrowing a registered book") {
        assert_true(library_is_book_available(bibliotheque, "L'Appel de Cthulhu"));    
        book* lookedfor_book = library_borrow_book(bibliotheque, "L'Appel de Cthulhu");
        asserteq(lookedfor_book, l_appel_de_cthulhu); 
        assert_false(library_is_book_available(bibliotheque, "L'Appel de Cthulhu"));    
    }

    it("borrowing a registered book (no more available copy") {
        book* lookedfor_book = library_borrow_book(bibliotheque, "L'Appel de Cthulhu");
        asserteq(lookedfor_book, NULL); // since there is no available copy 
    }

    it("borrowing a registered book (two copies are available") {
        assert_true(library_is_book_available(bibliotheque, "Le Silmarillion"));    
        book* lookedfor_book = library_borrow_book(bibliotheque, "Le Silmarillion");
        asserteq(lookedfor_book, le_silmarillion); 

        assert_true(library_is_book_available(bibliotheque, "Le Silmarillion"));    
        book* lookedfor_book_second_copy = library_borrow_book(bibliotheque, "Le Silmarillion");
        asserteq(lookedfor_book_second_copy, le_silmarillion); 

        assert_false(library_is_book_available(bibliotheque, "Le Silmarillion"));    
        book* lookedfor_book_no_third_copy = library_borrow_book(bibliotheque, "Le Silmarillion");
        asserteq(lookedfor_book_no_third_copy, NULL); 
    }

    it("returning an borrowed book") {
        int status = library_return_book(bibliotheque, le_silmarillion);
        asserteq(status, 1);
        assert(library_is_book_available(bibliotheque, "Le Silmarillion"));    
        status = library_return_book(bibliotheque, le_silmarillion);
        asserteq(status, 2);
    }

    it("returning a non-existing book") {
        les_contes_de_beedle_le_bard = book_init("The Tales of Beedle the Bard", "Beedle the Bard");
        int status = library_return_book(bibliotheque, les_contes_de_beedle_le_bard);
        asserteq(status, 0); // since we can return a non register book
    }

}

#endif

#if defined(Q9)

describe(Q9_library) {

    it("find all books (single result) from an existing author") {
        book** found_books = library_find_by_author(bibliotheque, "H. P. Lovecraft");
        assertneq(book_get_title(found_books[0]), NULL);
        asserteq_str(book_get_title(found_books[0]), "L'Appel de Cthulhu");
        free(found_books);
    }

    it("find all books (multiple results) from an existing author") {
        book** found_books = library_find_by_author(bibliotheque, "J. R. R. Tolkien");
        assertneq(book_get_title(found_books[0]), NULL);
        assertneq(book_get_title(found_books[1]), NULL);
        assertneq_str(book_get_title(found_books[0]), book_get_title(found_books[1])); // booktitles should differ
        // printf("%s\n", found_books[0]->title); // should return one of the booktitle from JRR Tolkien
        // printf("%s\n", found_books[1]->title); // should return another booktitle from JRR Tolkien
        free(found_books);
    }

    it("find all books from a non existing author") {
        book** found_books = library_find_by_author(bibliotheque, "Beedle the Bard");
        asserteq(found_books, NULL);
    }

}


    // cleaning up
#if defined(Q5)
describe(freeing_up_memory) {
    it("freeing up memory of library") {
        library_destroy(bibliotheque);
    }
#if defined(Q2)
    it("freeing up memory of books") {
        book_destroy(le_silmarillion);
        book_destroy(l_appel_de_cthulhu);
        book_destroy(le_hobbit);
        book_destroy(les_contes_de_beedle_le_bard);
    }
//    assert_true(1);
#endif
}
#endif

describe(stress_test) {
    // greetings to Clement Bailly-Grandvaux  
    it("Stress tests") {
        library * bibliotheque = library_init(255);
        book **testbook = malloc(sizeof(book*) * 255);
        char *title = calloc(3, sizeof(char));

        // Doit être vide
        asserteq(library_books_count(bibliotheque), 0);
        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            asserteq(library_find_by_title(bibliotheque, title), NULL);
        }

        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            testbook[i] =  book_init(title, "J. R. R. Tolkien");
            library_register_book(bibliotheque, testbook[i]);
        }

        // Test d'unicité des id
        for (int i = 0; i < 255; i++) {
            for (int j = 0; j < 255; j++) {
                if (i != j)
                    assertneq(book_get_id(testbook[i]), book_get_id(testbook[j]));
            }
        }

        // Test du nombre de livres enregistrés qui ne doit psa être le nombre d'exemplaires
        asserteq(library_books_count(bibliotheque), 255);
        for (int i = 0; i < 255; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                library_register_book(bibliotheque, testbook[i]);
            }
        }
        asserteq(library_books_count(bibliotheque), 255);

        // Vérification de la présence des livres et leur compte, et la non présence d'autres livres
        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            assertneq(library_find_by_title(bibliotheque, title), NULL);
            assertneq(library_is_book_available(bibliotheque, title), 0); //i + 1);
        }
        title[1] = 'a';
        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            asserteq(library_find_by_title(bibliotheque, title), NULL);
            asserteq(library_is_book_available(bibliotheque, title), 0);
        }
        title[1] = 0;

        
        library_destroy(bibliotheque);
        for (int i = 0; i < 255; i++) {
            book_destroy(testbook[i]);
        }

        bibliotheque = library_init(510);
        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            testbook[i] =  book_init(title, "J. R. R. Tolkien");
            library_register_book(bibliotheque, testbook[i]);
        }
        
        // Test d'unicité des id après destructions d'un ensemble de livres
        for (int i = 0; i < 255; i++) {
            for (int j = 0; j < 255; j++) {
                if (i != j)
                    assertneq(book_get_id(testbook[i]), book_get_id(testbook[j]));
            }
        }

        for (int i = 0; i < 255; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                library_return_book(bibliotheque, testbook[i]);
            }
        }
        // Vérification de la présence des livres et leur compte, et la non présences d'autres livres
        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            assertneq(library_find_by_title(bibliotheque, title), NULL);
            assertneq(library_is_book_available(bibliotheque, title), 0); // i + 1);
        }
        title[1] = 'a';
        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            asserteq(library_find_by_title(bibliotheque, title), NULL);
            asserteq(library_is_book_available(bibliotheque, title), 0);
        }
        title[1] = 0;

        // On peut les emprunter jusqu'au nombre d'exemplaire        
        for (int i = 0; i < 255; i++) {
            title[0] = (char)(i + 1);
            for (int j = 1; j <= i + 1; j++) {
                asserteq_ptr(library_borrow_book(bibliotheque, title), testbook[i]);
            }
            asserteq_ptr(library_borrow_book(bibliotheque, title), NULL);
        }

        book **testbook2 = malloc(sizeof(book*) * 255);
        title[1] = 'a';
        for (int i = 0; i < 255; i++)
        {
            title[0] = (char)(i + 1);
            testbook2[i] =  book_init(title, "J. R. R. Tolkien2");
            library_register_book(bibliotheque, testbook2[i]);
        }

        book ** found_books = library_find_by_author(bibliotheque, "J. R. R. Tolkien");
        for (int i = 0; i < 255; i++) {
            asserteq(found_books[i], testbook[i]);
        }
        free(found_books);

        library_destroy(bibliotheque);
        for (int i = 0; i < 255; i++) {
            book_destroy(testbook[i]);
        }
        for (int i = 0; i < 255; i++) {
            book_destroy(testbook2[i]);
        }


        free(testbook2);
        free(testbook);
        free(title);
    }
}

#endif

snow_main();

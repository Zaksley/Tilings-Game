#include <stdio.h>
#include <string.h>
#include "outils.h"

void text_green() {
    printf("\e[38;5;10m");
}

void text_red() {
    printf("\e[38;5;9m");
}

void text_white() {
    printf("\e[38;5;15m");
}

void display_error(int nb_error, char * name) {
    if (nb_error == 0) {
        printf("\e[38;5;10m"); 
        printf("Il n'y a pas d'erreur dans les tests %s\n", name);
    } else {
        printf("\e[38;5;9m");
        printf("Il y a %d erreurs dans les tests %s\n", nb_error, name);
    }
}
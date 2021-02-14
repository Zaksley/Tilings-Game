#include <stdio.h>
#include <string.h>
#include "../src/tile.h"
#include "test_tile.h"

void test_empty_tile()
{
    printf("  Debut test empty_tile\n");
    const struct tile * empty = empty_tile();

    enum direction directions[4] = {NORTH, SOUTH, WEST, EAST};
    int valide = 1;
    int i = 0;
    while ( i < 4 && valide == 1) {
        if (strcmp(color_name(tile_edge(empty, directions[i])), color_name(color_from_name("EMPTY")))) {
            valide = 0;
        }
        ++ i;
    }

    if (valide == 1) {
        printf("    La tuile est bien vide\n");
    } else {
        printf("    ERROR : la tuile n'est pas vide\n");
    }
    printf("  Fin test empty_tile\n");
}

void test_tile_is_empty()
{
    printf("  Debut test tile_is_empty\n");
    
    struct deck d;
    deck_init(&d);

    if (tile_is_empty(empty_tile())) {
        printf("    La tuile vide est bien considere comme vide\n");
    } else {
        printf("    ERROR : La tuile vide n'est pas considere comme vide\n");
    }


    if (tile_is_empty(d.cards[0].t)) {
        printf("    ERROR : Une tuile non vide est considere comme vide\n");
    } else {
        printf("    La tuile non vide n'est pas considere comme vide\n");
    }

    printf("  Fin test tile_is_empty\n");
}

void test_tile_equals()
{
    printf("  Debut test tile_equals\n");

    struct deck d;
    deck_init(&d);

    if (tile_equals(d.cards[0].t, d.cards[0].t)) {
        printf("    Le cote au nord a ete correctement reconu \n");
    } else {
        printf("    ERROR : le cote au nord a reconnu %s au lieu de %s\n", 
            color_name(tile_edge(d.cards[0].t, NORTH)), color_name(color_from_name("ROUGE")));
    }

    printf("  Fin test tile_equals\n");
}

void test_tile_edge()
{
    printf("  Debut test tile_edge.c\n");

    struct deck d;
    deck_init(&d);

    if (! strcmp(color_name(tile_edge(d.cards[0].t, NORTH)),color_name(color_from_name("ROUGE")))) {
        printf("    Le cote au nord a ete correctement reconu \n");
    } else {
        printf("    ERROR : le cote au nord a reconu %s au lieu de %s\n", 
            color_name(tile_edge(d.cards[0].t, NORTH)), color_name(color_from_name("ROUGE")));
    }

    printf("  Fin test tile_edge.c\n");
}

void test_deck_init()
{
    printf("  Debut test deck_init\n");

    struct deck d;
    deck_init(&d);
    
    if (d.size != 5) {
        printf("    ERROR : mauvais size %d\n", d.size);
    } else {
        printf("    Le deck a le bon size\n");
        for (unsigned int i = 0; i < d.size; ++ i) {
            int error = 0;
            if (d.cards[i].n != 20) {
                ++ error;
                printf("    ERROR : mauvais nombre de carte %d\n", d.cards[i].n);
            }
            if (error == 0) {
                printf("    Le deck_pair numero %u est valide\n", i);
            }
        }
    }

    printf("  Fin test deck_init\n");
}

void execute_test_tile()
{
    printf("Debut test tile.c\n");
    test_empty_tile();
    test_tile_is_empty();
    test_tile_equals();
    test_tile_edge();
    test_deck_init();
    printf("Fin test tile.c\n");
}


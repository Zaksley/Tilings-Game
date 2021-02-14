#include <stdio.h>
#include <string.h>
#include "../src/tile.h"
#include "test_tile.h"
#include "outils.h"

 int test_empty_tile()
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
    
    int error = 0;
    if (valide == 1) {
        text_green();
        printf("    La tuile est bien vide\n");
    } else {
        error = 1;
        text_red();
        printf("    ERROR : la tuile n'est pas vide\n");
    }
    text_white();
    printf("  Fin test empty_tile\n");
    return error;
}

 int test_tile_is_empty()
{
    printf("  Debut test tile_is_empty\n");
    int error = 0;

    struct deck d;
    deck_init(&d);

    if (tile_is_empty(empty_tile())) {
        text_green();
        printf("    La tuile vide est bien considere comme vide\n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : La tuile vide n'est pas considere comme vide\n");
    }


    if (tile_is_empty(d.cards[0].t)) {
        error ++;
        text_red();
        printf("    ERROR : Une tuile non vide est considere comme vide\n");
    } else {
        text_green();
        printf("    La tuile non vide n'est pas considere comme vide\n");
    }

    text_white();
    printf("  Fin test tile_is_empty\n");
    return error;
}

 int test_tile_equals()
{
    printf("  Debut test tile_equals\n");
    int error = 0;
    struct deck d;
    deck_init(&d);

    if (tile_equals(d.cards[0].t, d.cards[0].t)) {
        text_green();
        printf("    Le cote au nord a ete correctement reconu \n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : le cote au nord a reconnu %s au lieu de %s\n", 
            color_name(tile_edge(d.cards[0].t, NORTH)), color_name(color_from_name("ROUGE")));
    }

    text_white();
    printf("  Fin test tile_equals\n");
    return error;
}

 int test_tile_edge()
{
    printf("  Debut test tile_edge.c\n");
    int error = 0;

    struct deck d;
    deck_init(&d);

    if (! strcmp(color_name(tile_edge(d.cards[0].t, NORTH)),color_name(color_from_name("ROUGE")))) {
        text_green();
        printf("    Le cote au nord a ete correctement reconu \n");
    } else {
        error ++;
        text_red();
        printf("    ERROR : le cote au nord a reconu %s au lieu de %s\n", 
            color_name(tile_edge(d.cards[0].t, NORTH)), color_name(color_from_name("ROUGE")));
    }

    text_white();
    printf("  Fin test tile_edge.c\n");
    return error;
}

 int test_deck_init()
{
    printf("  Debut test deck_init\n");
    int error = 0;
    struct deck d;
    deck_init(&d);
    
    if (d.size != 5)
    { 
        error ++;
        text_red();
        printf("    ERROR : mauvais size %d\n", d.size);
    } else {
        text_green();
        printf("    Le deck a le bon size\n");
        for (unsigned int i = 0; i < d.size; ++ i) {
            int e = 0;
            if (d.cards[i].n != 20) {
                ++ e;
                error ++;
                text_red();
                printf("    ERROR : mauvais nombre de carte %d\n", d.cards[i].n);
            }
            if (e == 0) {
                text_green();
                printf("    Le deck_pair numero %u est valide\n", i);
            }
        }
    }

    text_white();
    printf("  Fin test deck_init\n");
    return error;
}

 int execute_test_tile()
{
    printf("Debut test tile.c\n");
    int error_empty = test_empty_tile();
    int error_is_empty = test_tile_is_empty();
    int error_equals = test_tile_equals();
    int error_edge = test_tile_edge();
    int error_deck_init = test_deck_init();
    int error_tot = error_deck_init + error_edge + error_equals + error_is_empty + error_empty;

    display_error(error_empty, "de empty_tile");
    display_error(error_is_empty, "de tile_is_empty");
    display_error(error_equals, "de tile_equals");
    display_error(error_edge, "de tile_edge");
    display_error(error_deck_init, "de deck_init");
    display_error(error_tot, "de tile");

    text_white();
    printf("Fin test tile.c\n");
    printf("-----------------------------------------\n");
    printf("\n");
    return(error_tot);
}


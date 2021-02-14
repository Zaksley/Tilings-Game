#include <stdio.h>
#include "../src/rule.h"
#include "test_rule.h"

void test_board_init()
{
    printf("  Debut test board_init\n");

    int taille = 5;
    struct board b = board_init(taille);

    if (b.taille == taille) {
        printf("    Taille du board valide\n");

        int erreur = 0;
        int le = -1;
        int lc = -1;
        for (int l = 0; l < b.taille; ++ l) {
            for (int c = 0; c < b.taille; ++ c) {
                if (! tile_equals(empty_tile(), b.plateau[l][c])) {
                    erreur ++;
                    le = l;
                    lc = c;
                }                
            }    
        }
        if(erreur == 0) {
            printf("    Le board est bien compose de tuile vide\n");
        } else {
            printf("    ERROR : il y a %d tuiles non vides ex ligne %d, colonne %d\n", erreur, le, lc);
        }
    } else {
        printf("    Error : Taille du board invalide %d au lieu de %d\n",b.taille,taille);
    }


    printf("  Fin test board_init\n");
}

void test_authorized_places()
{
    printf("  Debut test authorized_places\n");

    int taille = 3;
    struct board b = board_init(taille);

    struct deck d;
    deck_init(&d);

    const struct tile * t1 = d.cards[4].t;

    const struct tile * t2 = d.cards[1].t;

    struct position p1 = {.X=1, .Y=1};
    struct position p2 = {.X=0, .Y=2};
    struct position p3 = {.X=2, .Y=0};

    place_tile(&b, t1, p1, 0);
    place_tile(&b, t1, p2, 0);
    place_tile(&b, t1, p3, 0);

    /*

            tuile a place 

                V
              V   V
                V 

            plateau           
            |     |   V  
        NV  | Val | V   R 
            |     |   R 
       ----------------
            |  V  |     
        Val |V   R| NV  
            |  R  |     
       ---------------- 
         V  |     |     
        V R | NV  | NV   
         R  |     |     


    */

    int valides_x[9] = {0};
    int valides_y[9] = {0};

    int x_valides[2] = {0, 1};
    int y_valides[2] = {1, 0};
    int nb_valides = authorized_places(&b, t2, valides_x, valides_y);
    if (nb_valides == 2) {
        printf("    Il y a bien 2 places valides\n");

        int erreur = 0;
        int ie = -1;
        for (int i = 0; i < nb_valides; ++ i) {
            if (! (x_valides[i] == valides_x[i] && y_valides[i] == valides_y[i])) {
                erreur ++;
                ie = i;
            }        
        }
        if(erreur == 0) {
            printf("    Les cases valides sont bien aux bonnes positions\n");
        } else {
            printf("    ERROR : il y a %d cases valides aux mauvaises positions ex ligne %d, colonne %d\n", erreur, valides_x[ie], valides_y[ie]);
        }  

    } else {    
        printf("    ERROR : Il y a %d places valides au lieu de 2\n", nb_valides);
    }
   
    printf("  Fin test authorized_places\n");
}

void test_position_valide()
{
    printf("  Debut test position_valide\n");

    int taille = 5;
    struct board b = board_init(taille);

    struct deck d;
    deck_init(&d);

    const struct tile * t1 = d.cards[4].t;

    const struct tile * t2 = d.cards[1].t;

    if (! position_valide(&b, t1, 2, 2)) {
        printf("    Une place entouree de case vide est bien invalide\n");    
    } else  {    
        printf("    ERROR : Une place entouree de case vide est considere comme valide\n");    
    }
    struct position p = {.X = 0, .Y = 1};

    place_tile(&b, t2, p, 1);

    if (position_valide(&b, t2, 0, 0)) {
        printf("    une case sur les bords est biens valide\n");    
    } else  {    
        printf("    ERROR : une case sur les bords est considere comme invalide\n");    
    }

    p.X = 2;
    p.Y = 2;

    place_tile(&b, t1, p, 1);

    if (position_valide(&b, t1, 3, 2)) {
        printf("    ERROR : Deux couleurs differentes au sud et au nord mais la place est considere valide\n");    
    } else  {    
        printf("    Deux couleurs differents donnent bien une place invalide\n");    
    }

    if (position_valide(&b, t2, 1, 2)) {
        printf("    Deux couleurs egales donnent bien une place valide\n");    
    } else  {    
        printf("    ERROR : Deux couleurs egales au sud et au nord mais la place est considere invalide\n");    
    }
    
    printf("  Fin test position_valide\n");
}


void test_place_tile()
{
    printf("  Debut test place_tile\n");

    int taille = 5;
    struct board b = board_init(taille);

    struct deck d;
    deck_init(&d);

    const struct tile * t = d.cards[4].t;

    int x = 2;
    int y = 3;
    struct position pos = {.X = x, .Y = y};    
    place_tile(&b, t, pos, -1);

    if (tile_equals(t, b.plateau[x][y])) {
        printf("    La tuile a ete bien place\n");
    } else {
        printf("    ERROR : la tuile n'a pas été place a la postition %d %d\n", x, y);
    }
    printf("  Fin test place_tile\n");
}


void test_select_position()
{
    printf("  Debut test select_position\n");

    int nb = 3;
    int Xs[3] = {10, 5, 4};
    int Ys[3] = {8, 2, 1};

    struct position p = select_position(nb, Xs, Ys);

    int posValide = 0;
    int i = 0;

    while (posValide == 0 && i < nb) {
        posValide = (p.X == Xs[i] && p.Y == Ys[i])? 1 : 0;
        ++ i;
    }
    
    if (posValide) {
        printf("    La position %d %d est une position valide\n", p.X, p.Y);
    } else {
        printf("    ERROR : La position %d %d n'est pas une position valide\n", p.X, p.Y);
    }

    printf("  Fin test select_position\n");
}

void test_color_equals() {
    printf("  Debut test color_equals\n");

    struct color * cR1 = color_from_name("ROUGE");
    struct color * cR2 = color_from_name("ROUGE");
    struct color * cM = color_from_name("MAGENTA");

    if (color_equals(cR1, cR2)) {
        printf("    Deux couleurs rouges sont biens consideres comme egale\n");
    } else {
        printf("    ERROR : Deux couleurs rouges ne sont pas consideres comme egales les couleurs : %s %s\n",
         color_name(cR1), color_name(cR2));
    }

    if (! color_equals(cR1, cM)) {
        printf("    Deux couleurs rouge et magenta sont biens consideres comme non egale\n");
    } else {
        printf("    ERROR : Deux couleurs rouge et magenta ne sont pas consideres comme non egales les couleurs : %s %s\n",
         color_name(cR1), color_name(cM));
    }
    printf("  Fin test color_equals\n");
}

void test_init_players() {
    printf("  Debut test init_players\n");

    int nb_players = 3;
    struct player players[MAX_PLAYERS];
    init_players(nb_players, players);
    
    for (int i = 0; i < nb_players; i ++) {
        if (players[i].score == 0) {
            printf("    Le joueur %d a bien un score de 0\n", i);
        } else {
            printf("    ERROR : Le joueur %d a un score de %d au lieu de 0\n", i, players[i].score);
        }
    }

    printf("  Fin test init_players\n");
}


void execute_test_rule()
{
    printf("Debut test rule.c\n");
    test_board_init();
    test_authorized_places();
    test_position_valide();
    test_place_tile();
    test_select_position();
    test_color_equals();
    test_init_players();
    printf("Fin test rule.c\n");
}
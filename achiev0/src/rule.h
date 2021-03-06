#ifndef _RULE_H_
#define _RULE_H_

#include "tile.h"
#include "file.h"

#define MAX_PLAYERS 20
#define MAX_BOARD_LONG 50
#define DEFAULT_BOARD_LONG 10

struct board {
    int taille;
    const struct tile * plateau[50][50];
    int from_player[50][50];
};

struct position {
    int X;
    int Y;
};

struct player {
    struct file cards;
    int score;
};

void init_players(int nbPlayer, struct player players[]);

/**
 * Check all the board b for valide position for the tile t and put them in positions_validesX and positions_validesY
 * return the numbre of valide positions
 *  
**/ 
int authorized_places(struct board * b, const struct tile * t, int positions_validesX[], int positions_validesY [] );

/**
 * initialise a bord with the given taille
**/ 
struct board board_init(int taille);

/**
 * Place the tile p in the board b at the position p.X and p.Y from the player numero num_player
**/ 
void place_tile(struct board * b, const struct tile * t, struct position p, int num_player);

/**
 * Select a valid position
**/ 
struct position select_position(int nb_pos_valide, int positionsX[],int positionsY[]);

/**
 * test if a position is valid to place the tile
**/ 
int position_valide(struct board *b, const struct tile * t, int ligne, int colonne);


/**
 * Show score for every player and display the winner
**/ 
void display_result(int nb_players, struct player players[]);

/**
 * Display all the tiles - Usefull for visual comphrehension 
 **/
void afficher_board(struct board * b);

/**
 * compare two color
 **/ 
int color_equals(struct color * c1, struct color * c2);

#endif // _RULE_H_

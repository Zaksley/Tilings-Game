#ifndef _RULE_H_
#define _RULE_H_

#include "file.h"
#include "motif.h"

#define MAX_PLAYERS 20
#define MAX_BOARD_LONG 50
#define DEFAULT_BOARD_LONG 10

struct board {
    int taille;
    const struct tile * plateau[MAX_BOARD_LONG][MAX_BOARD_LONG];
    int from_player[MAX_BOARD_LONG][MAX_BOARD_LONG][MAX_PLAYERS];
    int nb_tuiles_placed_after[MAX_BOARD_LONG][MAX_BOARD_LONG];
};

struct position {
    int X;
    int Y;
};

struct player {
    struct file cards;
    int score;
};

struct zone_connexe {
    int nb_tuile;
    int cases_players [MAX_PLAYERS];
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
struct board board_init(int taille, int nb_players);

/**
 * Place the tile p in the board b at the position p.X and p.Y from the player numero num_player
**/ 
void place_tile(struct board * b, const struct tile * t, struct position p, int num_player, int nb_players);

/**
 * Select a valid position
**/ 
struct position select_position(int nb_pos_valide, int positionsX[],int positionsY[]);

/**
 * test if a position is valid to place the tile
**/ 
int position_valide(struct board *b, const struct tile * t, int ligne, int colonne);



/**
 * Check if a tile is bicolor
 **/
int is_monocolor(const struct tile* t);

/**
 * Motif full color with full color
 **/
int motif_monocolor_with_monocolor(struct board *b, int l, int c);

/**
 * Motif full color with 2 bicolor
 **/
int motif_monocolor_with_two_bicolor(struct board *b, int l, int c);


/**
 * Motif full color surrounded
 **/
int motif_full_surrond(struct board *b, int l, int c);


/**
 * Add score with the motif system
 **/
void checking_motif(struct player players[], struct board *b, int nb_motifs, struct motif motifs[], int nb_players);

/**
 * Test connections on the board 
 **/
void connexe(int nb_player, struct player players[], struct board* b);

/**
 * Recursive parcours to get all connections from a direction tile
 **/
void parcours_en_profondeur(struct board* b, int l, int c, int i, int connexe_used[][MAX_BOARD_LONG][5], struct zone_connexe* z, int nb_players);

/**
 * Every round give -1 propriétés for all tiles and all players
 **/ 
void update_propriete(struct board *b, int nb_players);

/**
 * Add The King to the game, he fall un the chosed_l chosed_c
 **/
void king(struct board *b, int nb_players, int chosed_l, int chosed_c);

/**
 * Give the numbers of players with the maximum from_player of the case l c and give their num in the tab proprios
 **/
int proprietaires(struct board * b, int l, int c, int nb_players, int proprios[]);

/**
 * Show score for every player and display the winner
**/ 
void display_result(int nb_players, struct player players[]);

/**
 * Display all the tiles - Usefull for visual comphrehension 
 **/
void afficher_board(struct board * b, int nb_players);

/**
 * Display all the influences - Usefull for visual comphrehension 
 **/
void afficher_influence(struct board * b, int nb_players);

/**
 * compare two color
 **/ 
int color_equals(struct color * c1, struct color * c2);

#endif // _RULE_H_

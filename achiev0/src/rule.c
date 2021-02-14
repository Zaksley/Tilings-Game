#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rule.h"

void init_players(int nbPlayers, struct player players []) {
    for (int i = 0; i < nbPlayers; i ++) {
        struct player p = {.score = 0};
        p.cards = create_file();
        players[i] = p;
    } 
}

int authorized_places(struct board * b, const struct tile * t, int positions_validesX[], int positions_validesY[] ) {
    int nb_pos = 0;
    int tail =  b->taille;
    for (int ligne = 0; ligne < tail; ++ ligne) {
        for (int colonne = 0; colonne < tail; ++ colonne) {
            if (position_valide(b, t, ligne, colonne)) {
                positions_validesX[nb_pos] = ligne;
                positions_validesY[nb_pos] = colonne;
                ++ nb_pos;                
            }
        }    
    }
    return nb_pos;
}

int position_valide(struct board *b, const struct tile * t, int ligne, int colonne) {
    if ((b->from_player)[ligne][colonne] != -1) {
        return 0;
    }

    int exist_neighbour = -1;
    
    if (ligne > 0) {
        if ((b->from_player)[ligne - 1][colonne] != -1) {
            exist_neighbour += 1;
            if (!color_equals(tile_edge((b->plateau)[ligne - 1][colonne], SOUTH), tile_edge(t, NORTH))) {
                return 0;
            }
        }       
    }
    
    
    if (ligne < b->taille - 1) {
        if ((b->from_player)[ligne + 1][colonne] != -1) {
            exist_neighbour += 1;
            if (!color_equals(tile_edge((b->plateau)[ligne + 1][colonne], NORTH), tile_edge(t, SOUTH))) {
                return 0;
            }
        }
    }
    
    if (colonne > 0) {
        if ((b->from_player)[ligne][colonne - 1] != -1) {
            exist_neighbour += 1;
            if (!color_equals(tile_edge((b->plateau)[ligne][colonne - 1], EAST), tile_edge(t, WEST))) {
                return 0;
            }
        }
    }

    if (colonne <  b->taille - 1) {
        if ((b->from_player)[ligne][colonne + 1] != -1) {
            exist_neighbour += 1;
            if (!color_equals(tile_edge((b->plateau)[ligne][colonne + 1], WEST), tile_edge(t, EAST))) {
                return 0;
            }
        }
    }

    if (exist_neighbour != -1)     return 1;
    else return 0;
}

int color_equals(struct color * c1, struct color * c2) {
    if (c1 == NULL || c2 == NULL) {
      if (c1 == NULL && c2 == NULL) {
        return 1;
      } else {
        return 0;
      }
    }

    return !strcmp(color_name(c1), color_name(c2));
}

struct board board_init(int taille) {
    struct board b = {.taille = taille};
    for (int l = 0; l < taille; ++ l) {
        for (int c = 0; c < taille; ++ c) {
            b.plateau[l][c] = empty_tile();
            b.from_player[l][c] = -1;
        }    
    }
    return b;
}

void place_tile(struct board * b, const struct tile * t, struct position p, int num_joueur) {
  (b->plateau)[p.X][p.Y] = t;
  (b->from_player)[p.X][p.Y] = num_joueur;
}

struct position select_position(int nb_pos_valide, int positionsX[],int positionsY[]) {
    int r = rand() % nb_pos_valide; 
    struct position p = {.X = positionsX[r], .Y=positionsY[r]};
    return p; 
}

void display_result(int nb_players, struct player players [])
{
  int max = players[0].score;
  int indice = 0;
  printf("Joueur %d a %d points\n", 0, players[0].score);
  for (int i=1; i<nb_players; i++)
    {
      printf("Joueur %d a %d points\n", i, players[i].score);
      if (max< players[i].score)
	{
	  max = players[i].score;
	  indice = i;
	}
    }
   printf("Le gagnant est le joueur %d\n", indice);
}

void print_entre_ligne(int taille) {
    printf("%s", color_cstring(color_from_name("BLANC")));
    for (int i = 0; i < taille; i ++) {
        printf("-");
    }
    printf("\n");
}

void afficher_board(struct board * b) {
    print_entre_ligne(5 * b->taille - 1);
    for(int ligne = 0; ligne < b->taille; ++ ligne) {
        int colonne = 0;
        while(colonne < b->taille) {
            if (tile_is_empty((b->plateau)[ligne][colonne])) {
                printf("    ");
            } else {
                printf("%s", color_cstring(tile_edge((b->plateau)[ligne][colonne], NORTH)));
                printf(" /\\ ");
            }
            ++ colonne;
            if (colonne != b->taille) {
                printf("%s", color_cstring(color_from_name("BLANC")));
                printf("|");
            }
        }
        printf("\n");

        colonne = 0;
        while(colonne < b->taille) {
            if (tile_is_empty((b->plateau)[ligne][colonne])) {
                printf("    ");
            } else {
                printf("%s", color_cstring(tile_edge((b->plateau)[ligne][colonne], WEST)));
                int num = b->from_player[ligne][colonne];
                if (num < 10) {
                    printf("/%d ", num);
                } else {
                    printf("/%d", num);
                }
               
                printf("%s", color_cstring(tile_edge((b->plateau)[ligne][colonne], EAST)));
                printf("\\");
            }
            
            ++ colonne;
            if (colonne != b->taille) {
                printf("%s", color_cstring(color_from_name("BLANC")));
                printf("|");
            }
        }
        printf("\n");

        colonne = 0; 
        while(colonne < b->taille) {
            if (tile_is_empty((b->plateau)[ligne][colonne])) {
                printf("    ");
            } else {
               printf("%s", color_cstring(tile_edge((b->plateau)[ligne][colonne], WEST)));
                printf("\\ ");
                printf("%s", color_cstring(tile_edge((b->plateau)[ligne][colonne], EAST)));
                printf(" /");
            }
            
            ++ colonne;
            if (colonne != b->taille) {
                printf("%s", color_cstring(color_from_name("BLANC")));
                printf("|");
            }
        }
        printf("\n");

        colonne = 0;
        while(colonne < b->taille) {
            if (tile_is_empty((b->plateau)[ligne][colonne])) {
                printf("    ");
            } else {
               printf("%s", color_cstring(tile_edge((b->plateau)[ligne][colonne], SOUTH)));
               printf(" \\/ ");
            }

            
            ++ colonne;
            if (colonne != b->taille) {
                printf("%s", color_cstring(color_from_name("BLANC")));
                printf("|");
            }
        }
        printf("\n");
        print_entre_ligne(5 * b->taille - 1);    
    }
}

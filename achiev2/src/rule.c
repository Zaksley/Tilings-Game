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
    
    
    if (exist_neighbour != -1)  return 1;
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

// -------------------------------  Motifs 

int is_monocolor(const struct tile * t) {
    struct color * c = tile_edge(t, NORTH);
    enum direction other_directions[3] = {SOUTH, EAST, WEST};
    for (int i = 0; i < 3; i ++) {
        if (! color_equals(c, tile_edge(t,other_directions[i]))) {
            return 0;
        }
    }
    return 1;
}


//Motif 1
int motif_monocolor_with_monocolor(struct board *b, int l, int c)
{

  if (!is_monocolor(b->plateau[l][c])) return 0;
  
  int nb_needed = 1;
  int count = 0;

  if (l>0)
    {
      if ((b->from_player)[l-1][c] != -1)
	{
	  if (is_monocolor(b->plateau[l-1][c])) count += 1;
	}
    }

  if (l<(b->taille) - 1)
    {
      if ((b->from_player)[l+1][c] != -1)
	{
	  if (is_monocolor(b->plateau[l+1][c])) count += 1;
	}
    }

    if (c>0)
    {
      if ((b->from_player)[l][c-1] != -1)
	{
	  if (is_monocolor(b->plateau[l][c-1])) count += 1;
	}
    }

  if (c<(b->taille) - 1)
    {
      if ((b->from_player)[l][c+1] != -1)
	{
	  if (is_monocolor(b->plateau[l][c+1])) count += 1;
	}
    }
  
  return (count >= nb_needed);
}

//Motif 2
int motif_monocolor_with_two_bicolor(struct board *b, int l, int c) {
    if (!is_monocolor((b->plateau[l][c]))) {
        return 0;
    }
    int nb_bic = 0;

    if (l > 0) {
        if ((b->from_player)[l - 1][c] != -1) {
            nb_bic = (!is_monocolor((b->plateau)[l - 1][c])) ? nb_bic + 1 : nb_bic;
        }
    }

    if (l < b->taille-1) {
        if ((b->from_player)[l + 1][c] != -1) {
            nb_bic = (!is_monocolor((b->plateau)[l + 1][c])) ? nb_bic + 1 : nb_bic;
        }
    }

    if (c > 0) {
        if ((b->from_player)[l][c - 1] != -1) {
            nb_bic = (!is_monocolor((b->plateau)[l][c - 1])) ? nb_bic + 1 : nb_bic;
        }
    }

    if (c < b->taille-1) {
        if ((b->from_player)[l][c + 1] != -1) {
            nb_bic = (!is_monocolor((b->plateau)[l][c + 1])) ? nb_bic + 1 : nb_bic;
        }
    }

    return nb_bic >= 2;
}

//Motif 3
int motif_full_surrond(struct board *b, int l, int c) {
  if ( l == 0 || l == (b->taille)-1 || c == 0 || c == (b->taille)-1 ) {
        return 0;
    }

    if ((b->from_player)[l - 1][c] == -1) {
        return 0;
    }

    if ((b->from_player)[l + 1][c] == -1) {
        return 0;
    }

    if ((b->from_player)[l][c - 1] == -1) {
        return 0;
    }

    if ((b->from_player)[l][c + 1] == -1) {
        return 0;
    }

    return 1;
}


void checking_motif(struct player players[], struct board *b, int nb_motifs, struct motif motifs[])
{
  for(int i=0; i<(b->taille); i++)
    {
      for(int j=0; j<(b->taille); j++)
	{
	  int num = (b->from_player)[i][j];
	  if (num != -1)
	    {
	      for (int m = 0; m < nb_motifs; m ++) {
              if (motifs[m].actif) {
                if ( (*motifs[m].test)(b,i,j)) {
                    players[num].score += motifs[m].score; 
                }
              }
          }
	      
	    }
	}
    }
}


// ---------------------------------- End Motifs

// ---------------------------------- Connexe

void connexe(int nb_player, struct player players[], struct board *b)
{
  int connexe_used[MAX_BOARD_LONG][MAX_BOARD_LONG][5] = {{{0}}};
  for(int l=0; l< b->taille; l++)
    {
      for(int c=0; c< b->taille; c++)
	{
	  for(int i=0; i<4; i++)
	    {
        if (connexe_used[l][c][i] == 0 && b->from_player[l][c] != -1) {
          struct zone_connexe z = {.nb_tuile = 0, .cases_players = {0}};       

          for(int li=0; li< b->taille; li++) {
            for(int ci=0; ci< b->taille; ci++) {
              connexe_used[li][ci][4] = 0;
            }
          }
          parcours_en_profondeur(b, l, c, i, connexe_used, &z);

          int max = 0;
          int nb_players_max = 0;
          int players_max[MAX_PLAYERS];
          for (int k = 0; k < nb_player; k ++) {
            if (max < z.cases_players[k]) {
              nb_players_max = 1;
              players_max[nb_players_max - 1] = k;
              max = z.cases_players[k];
            } else if ( max == z.cases_players[k]) {
              nb_players_max ++;
              players_max[nb_players_max - 1] = k;
            }
          }

          for (int v = 0; v < nb_players_max; v ++) {
            players[players_max[v]].score += (z.nb_tuile * z.nb_tuile) / nb_players_max; 
          }
        }
	      
	    }
	}
    }

}

void parcours_en_profondeur(struct board* b, int l, int c, int i, int connexe_used[][MAX_BOARD_LONG][5], struct zone_connexe* z)
{
  if (connexe_used[l][c][i] == 0)
    {
      connexe_used[l][c][i] = 1;

      if (connexe_used[l][c][4] == 0)
	{
	  connexe_used[l][c][4] = 1;
	  z->cases_players[b->from_player[l][c]] += 1;
	  z->nb_tuile += 1;
	}
      
      for(int k=1; k<4; k++)
	{
	  if (color_equals(tile_edge(b->plateau[l][c], i), tile_edge(b->plateau[l][c], (i+k)%4)))
	    {
	      parcours_en_profondeur(b, l, c, (i+k)%4, connexe_used, z);
	    }
	}

      switch(i)
	{
	case 0:
	 
	  if ( (l > 0) && (b->from_player[l-1][c] != -1) )
	    {
        if (color_equals(tile_edge(b->plateau[l][c], i), tile_edge(b->plateau[l-1][c], 1))) {
          parcours_en_profondeur(b, l-1, c, 1, connexe_used, z);
        }   
	    }
	  
	  break;
	  
	case 1:
	  if  ( (l<(b->taille-1)) && (b->from_player[l+1][c] != -1))
	    {
        if (color_equals(tile_edge(b->plateau[l][c], i), tile_edge(b->plateau[l+1][c], 0))) {
          parcours_en_profondeur(b, l+1, c, 0, connexe_used, z);
        }
	      
	    }
	  break;
	  
	case 2:
	  if ( (c<(b->taille-1)) && (b->from_player[l][c+1] != -1))
	    {
        if ((color_equals(tile_edge(b->plateau[l][c], i), tile_edge(b->plateau[l][c+1], 3)))) {
          parcours_en_profondeur(b, l, c+1, 3, connexe_used, z);
        }
	    }
	  break;
	      
	case 3:
	  if ( (c>0) && (b->from_player[l][c-1]))
	    {
        if ((color_equals(tile_edge(b->plateau[l][c], i), tile_edge(b->plateau[l][c-1], 2))) ) {
          parcours_en_profondeur(b, l, c-1, 2, connexe_used, z);  
        }
 	      
	    }
	  break;
	}
	      
    }
	
      else
	{
	  //Do nothing 
	}
}





// ---------------------------------- End Connexe



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

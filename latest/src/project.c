#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "rule.h"


// Global parameters for the game
static int seed = 0;
static int nb_players = MAX_PLAYERS;
static int board_long = DEFAULT_BOARD_LONG;
static int print_result = 0;
static int print_influence = 0;
static int m1_active = 1;
static int m2_active = 1;
static int m3_active = 1;

////////////////////////////////////////////////////////////////
// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
// -n <nb_player> : sets the number of player
// -b <board_long> : sets the width/height of the board
// -m <m1_active> <m2_active> <m3_active> : choose which motif are used
// -r : Display board and tiles
// -i : Display influence


void parse_opts(int argc, char* argv[])
{
  int opt;
  while ((opt = getopt(argc, argv, "s:n:b:m:ri")) != -1)
    {
      switch (opt)
	{
	case 's':
	  seed = atoi(optarg);
	  break;
	case 'n':
	  if (atoi(optarg) > MAX_PLAYERS || atoi(optarg) < 2)
	    {
	      nb_players = MAX_PLAYERS;
	    }
	  else
	    {
	      nb_players = atoi(optarg);
	    }
	  break;
	case 'b':
	  if (atoi(optarg) > MAX_BOARD_LONG || atoi(optarg) <= 0)
	    {
	      board_long = DEFAULT_BOARD_LONG;
	    }
	  else
	    {
	      board_long = atoi(optarg);
	    }
	  break;

	case 'm':
	  switch (atoi(optarg))
	    {
	    case 1:
	      m1_active = 0;
	      break;
	    case 2:
	      m2_active = 0;
	      break;
	    case 3:
	      m3_active = 0;
	      break;
	    }
	  break;
	case 'r':
	  print_result = 1;
	  break;
	case 'i':
	  print_influence = 1;
	  break;
	  
	default: /* '?' */
	  fprintf(stderr, "Usage: %s [-s seed] \n", argv[0]);
	  fprintf(stderr, "Usage: %s [-n number of players] \n", argv[0]);
	  fprintf(stderr, "Usage: %s [-b width of the board] \n", argv[0]);
	  fprintf(stderr, "Usage: %s [-r] Print results \n", argv[0]);
	  fprintf(stderr, "Usage: %s [-i] Print influence \n", argv[0]);
	  fprintf(stderr, "Usage: %s [-m which motif retired] \n", argv[0]);
	  exit(EXIT_FAILURE);
    }
  }
}

////////////////////////////////////////////////////////////////


void distrib(struct deck* d, int nb_joueur, struct player players[])
{
  int nb_tiles = MAX_DECK_SIZE / nb_joueur;
  for(int i=0; i<nb_joueur; i++)
    {
      for(int j=0; j<nb_tiles; j++)
	{
	  int chosed = rand() % d->size;
	  int nb = (d->cards)[chosed].n;
	  
	  if (nb == 0)
	    {
	      (d->cards)[chosed] = (d->cards)[(d->size)];
	      d->size -= 1;	
	    }
	  push(&(players[i].cards), (d->cards)[chosed].t);
	  nb -= 1; 
	}
    }
}

int main(int argc,  char* argv[])
{

  parse_opts(argc, argv);  
  printf("Seed : %d\n", seed);
  srand(seed);
  printf("Nombre de joueurs %d\n", nb_players);
  printf("Longueur de la board %d\n", board_long);

  char * statut_motif = "actif";

  statut_motif = (m1_active) ? "actif" : "non actif"; 
  printf("Motif 1 (Monochrome avec un autre monochrome) est %s \n", statut_motif);
  statut_motif = (m2_active) ? "actif" : "non actif"; 
  printf("Motif 2 (Monochrome avec au moins deux bicolores) est %s \n", statut_motif);
  statut_motif = (m3_active) ? "actif" : "non actif"; 
  printf("Motif 3 (Tuile entourée de 4 tuiles) est %s \n", statut_motif);
  
  printf("\n LANCEMENT DE LA PARTIE \n\n");

  
  //----------- Init --------------
  struct player players[MAX_PLAYERS];
  init_players(nb_players, players);     // Initialise les joueurs
  struct deck d;
  deck_init(&d);                         // Initialise les decks
  struct board b = board_init(board_long, nb_players);
  distrib(&d, nb_players, players);

  // ---  On oblige manuellement le premier joueur à jouer au centre
  struct position center = {.X=board_long/2, .Y=board_long/2};
  place_tile(&b, pop(&(players[0].cards)), center, 0, nb_players);
  // ---
  
  int skipped_turn = 0;             // Initialise la boucle de jeu
  int active_player = (nb_players > 1)? 1 : 0;
  

  // --- Initialisation motifs
  struct motif m1 = { .score = 3, .actif = m1_active, .test = &motif_monocolor_with_monocolor };
  struct motif m2 = { .score = 5, .actif = m2_active, .test = &motif_monocolor_with_two_bicolor };
  struct motif m3 = { .score = 10, .actif = m3_active, .test = &motif_full_surrond };

  struct motif motifs[3] = {m1, m2, m3};
  // ---

  int position_validesX[MAX_BOARD_LONG * MAX_BOARD_LONG];
  int position_validesY[MAX_BOARD_LONG * MAX_BOARD_LONG];
    
  //----------- Game --------------
  
  while (skipped_turn < nb_players)
  {
    if (! file_is_empty(&(players[active_player].cards))) {
      const struct tile* new_tile = get_top(&(players[active_player].cards));
      int nb_place = authorized_places(&b, new_tile, position_validesX, position_validesY);
      if (nb_place == 0 ) //Pas de case disponible pour placer la tuile
	{
	  skipped_turn++;
	  push(&(players[active_player].cards), new_tile);
	  pop(&(players[active_player].cards));
	}
      else
	{
	  skipped_turn = 0;
	  place_tile(&b, new_tile, select_position(nb_place, position_validesX, position_validesY), active_player, nb_players);
	  pop(&(players[active_player].cards));
	} 
    }
    else
      {
	break;
      }

    
    //Fin d'un tour
    if (active_player == (nb_players-1))
      {
	update_propriete(&b, nb_players);
	
	int chosed_l = rand() % b.taille;
	int chosed_c = rand() % b.taille;
	king(&b, nb_players, chosed_l, chosed_c);
	active_player = 0;
      }
    else
      {
	active_player++;
      }
  }
  checking_motif(players, &b, 3, motifs, nb_players);
  connexe(nb_players, players, &b);
  display_result(nb_players, players);

  
  if (print_result)  {
    afficher_board(&b, nb_players);
  }

   if (print_influence) {
     printf("\n -- Affichage de l'influence -- \n\n");
     afficher_influence(&b, nb_players);
     printf("\n -- Fin de l'affichage de l'influence -- \n\n");
   }
		       
  printf("\n FIN DE LA PARTIE \n");
  
  return EXIT_SUCCESS;
}


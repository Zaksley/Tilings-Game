#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "tile.h"
#include "file.h"
#include "rule.h"

#define MAX_PLAYERS 20
#define MAX_BOARD_LONG 50
#define DEFAULT_BOARD_LONG 10

// Global parameters for the game
static int seed = 0;
static int nb_players = MAX_PLAYERS;
static int board_long = DEFAULT_BOARD_LONG;
static int print_result = 0;

////////////////////////////////////////////////////////////////
// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
// -n <nb_player> : sets the number of player
// -b <board_long> : sets the width/height of the board

void parse_opts(int argc, char* argv[])
{
  int opt;
  while ((opt = getopt(argc, argv, "s:n:b:r")) != -1)
    {
      switch (opt)
	{
	case 's':
	  seed = atoi(optarg);
	  break;
	case 'n':
	  if (atoi(optarg) <= MAX_PLAYERS)
	    {
	      nb_players = atoi(optarg);
	    }
	  break;
	case 'b':
	  if (atoi(optarg) <= MAX_BOARD_LONG)
	    {
	      board_long = atoi(optarg);
	    }
	  break;
	case 'r':
	  print_result = 1;
	  break;
	  
	default: /* '?' */
	  fprintf(stderr, "Usage: %s [-s seed] \n", argv[0]);
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
  printf("Nombre de joueurs %d\n", nb_players);
  printf("Longueur de la board %d\n", board_long);
  printf("\n LANCEMENT DE LA PARTIE \n\n");

  
  //----------- Init --------------
  struct player players[MAX_PLAYERS];
  init_players(nb_players, players);
  struct deck d;
  deck_init(&d);
  struct board b = board_init(board_long);
  distrib(&d, nb_players, players);
  struct position center = {.X=board_long/2, .Y=board_long/2};
  place_tile(&b, pop(&(players[0].cards)), center, 0);
  int skipped_turn = 0;
  int active_player = 1;

  int position_validesX[MAX_BOARD_LONG * MAX_BOARD_LONG];
  int position_validesY[MAX_BOARD_LONG * MAX_BOARD_LONG];
    
  //----------- Game --------------
  
  while (skipped_turn < nb_players)
  {
    if (! file_is_empty(&(players[active_player].cards))) {
      const struct tile* new_tile = get_top(&(players[active_player].cards));
      int nb_place = authorized_places(&b, new_tile, position_validesX, position_validesY);
      if (nb_place == 0 )
	{
	  skipped_turn++;
	  push(&(players[active_player].cards), new_tile);
	  pop(&(players[active_player].cards));
	}
      else
	{
	  skipped_turn = 0;
	  place_tile(&b, new_tile, select_position(nb_place, position_validesX, position_validesY), active_player);
	  pop(&(players[active_player].cards));
	  players[active_player].score += 1;
	} 
    }
    else
      {
	skipped_turn++;
      }
    
    if (active_player == (nb_players-1))
      {
	active_player = 0;
      }
    else
      {
	active_player++;
      }
  }
  display_result(nb_players, players);

  if (print_result)  afficher_board(&b);
		       
  printf("\n FIN DE LA PARTIE \n");
  
  return EXIT_SUCCESS;
}


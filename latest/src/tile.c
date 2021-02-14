#include <stdio.h>
#include <stdlib.h>
#include "tile.h"

#define NB_COUL 15

void random_tuile(struct tile* t);

struct tile {
  struct color* colors[4];
};

static struct tile empty_t;


const struct tile* empty_tile() 
{
  enum direction directions[4] = {NORTH, SOUTH, WEST, EAST};
  for (int i = 0; i < 4; ++ i) {
    empty_t.colors[directions[i]] = color_from_name("EMPTY");
  }
  return &empty_t;
}

int tile_is_empty(const struct tile* t) {
  return tile_equals(empty_tile(), t);
}

int tile_equals(const struct tile* t1, const struct tile* t2) 
{
  enum direction directions[4] = {NORTH, SOUTH, WEST, EAST};
  for (int i = 0; i < 4; ++ i){
    if ((t1->colors)[directions[i]] != (t2->colors)[directions[i]])
      return 0;
      }
  return 1;
}

struct color* tile_edge(const struct tile* t, enum direction d) 
{
  return (t->colors)[d];
}

static struct tile tuiles[100];

void deck_init(struct deck* d)
{
  d->size = 5;
  for (unsigned int i = 0; i < d-> size; ++ i) {
    (d->cards)[i].n = 20;
    (d->cards)[i].t = &tuiles[i];
  }

  //Tuiles utilisées

  (tuiles[0].colors)[NORTH] = color_from_name("ROUGE");
  (tuiles[0].colors)[SOUTH] = color_from_name("ROUGE");
  (tuiles[0].colors)[EAST] = color_from_name("ROUGE");
  (tuiles[0].colors)[WEST] = color_from_name("ROUGE");

  (tuiles[1].colors)[NORTH] = color_from_name("VIOLET");
  (tuiles[1].colors)[SOUTH] = color_from_name("VIOLET");
  (tuiles[1].colors)[EAST] = color_from_name("VIOLET");
  (tuiles[1].colors)[WEST] = color_from_name("VIOLET");

  (tuiles[2].colors)[NORTH] = color_from_name("ROUGE");
  (tuiles[2].colors)[SOUTH] = color_from_name("VIOLET");
  (tuiles[2].colors)[EAST] = color_from_name("ROUGE");
  (tuiles[2].colors)[WEST] = color_from_name("VIOLET");

  (tuiles[3].colors)[NORTH] = color_from_name("VIOLET");
  (tuiles[3].colors)[SOUTH] = color_from_name("ROUGE");
  (tuiles[3].colors)[EAST] = color_from_name("VIOLET");
  (tuiles[3].colors)[WEST] = color_from_name("ROUGE");

  (tuiles[4].colors)[NORTH] = color_from_name("VIOLET");
  (tuiles[4].colors)[SOUTH] = color_from_name("ROUGE");
  (tuiles[4].colors)[EAST] = color_from_name("ROUGE");
  (tuiles[4].colors)[WEST] = color_from_name("VIOLET");
}
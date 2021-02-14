#include <stdio.h>
#include "tile.h"
#include "file.h"


void push(struct file* f, const struct tile* new_tile)
{
  f->tiles[f->fin] = new_tile;
  f->fin++;
}

const struct tile* get_top(struct file* f)
{
  return (f->tiles[f->debut]);
}

int file_is_empty(struct file* f)
{
  return (f->debut == f->fin);
}

const struct tile* pop(struct file* f)
{
  f->debut++;
  return (f->tiles[(f->debut)-1]);
}

struct file create_file()
{
  struct file new_file;
  new_file.debut = 0;
  new_file.fin = 0;
  return new_file;
}

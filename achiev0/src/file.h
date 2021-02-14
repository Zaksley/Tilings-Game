#ifndef _FILE_H
#define _FILE_H

#define MAX_TILES 150

struct file
{
  int debut;
  int fin;
  const struct tile* tiles[MAX_TILES];
};

// Add a tile to the file
void push(struct file* f, const struct tile* new_tile);
// Get the first tile
const struct tile* get_top(struct file* f);
// Get the first tile and delete it from file
const struct tile* pop(struct file* f);
// A file that is empty
int file_is_empty(struct file* f);
// Create an empty file
struct file create_file();

#endif // _FILE_H

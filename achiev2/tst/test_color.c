#include <stdio.h>
#include <string.h>
#include "../src/color.h"
#include "test_color.h"



void test_color_name()
{
  printf("   Debut test color_name\n");
  printf("La couleur orange est bien %s\n", color_name(color_from_name("ORANGE")));
  printf("   Fin test color_name\n");
}


void test_color_cstring()
{
  printf("   Debut test color_cstring\n");
  printf("Valeur ANSI pour la couleur Magenta : %s'MAGENTA'\n", color_cstring(color_from_name("MAGENTA")));
  printf("\e[38;5;15m");

  printf("   Fin test color_cstring\n");
}

void test_color_from_name()
{
  printf("   Debut test color_from_name\n");
  struct color* test = color_from_name("ROUGE");
  if (!strcmp("ROUGE", color_name(test)))
    {
      printf("La couleur rouge est bien %s\n", color_name(test));
    }
  printf("   Fin test color_name\n");
}


void execute_test_color()
{
  printf("Debut test color.c\n");
  test_color_name();
  test_color_cstring();
  test_color_from_name();
  printf("Fin test tile.c\n");
}

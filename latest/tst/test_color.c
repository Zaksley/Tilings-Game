#include <stdio.h>
#include <string.h>
#include "../src/color.h"
#include "test_color.h"
#include "outils.h"



int test_color_name()
{
  printf("   Debut test color_name\n");
  int error = 0;

  if (! strcmp("ORANGE", color_name(color_from_name("ORANGE")))) {
    text_green();
    printf("    La couleur orange est bien ORANGE\n");
  } else {
    error ++;
    text_red();
    printf("    ERROR: La couleur est %s au lieu de ORANGE\n", color_name(color_from_name("ORANGE")));  
  }
  
  text_white();
  printf("   Fin test color_name\n");
  return error;
}


int test_color_cstring()
{
  printf("   Debut test color_cstring\n");
  int error = 0;

  if (! strcmp("\e[38;5;89m", color_cstring(color_from_name("MAGENTA")))) {
    text_green();
    printf("    Le cstring de MAGENTA est bien \\e[38;5;15m \n");
  } else {
    error ++;
    text_red();
    const char * res = color_cstring(color_from_name("MAGENTA"));
    if (strlen(res) > 0) {
      char erreur [15];
      int i = 1;
      erreur[0] = 'e';
      while (res[i] != 0) {
        erreur[i] = res[i];
        i ++;
      }
      erreur[i] = 0;
      printf("    ERROR: Le cstring de MAGENTA est \\%s au lieu de \\e[38;5;89m\n", erreur);  
    } else {
      printf("    ERROR: Le cstring de MAGENTA est %s au lieu de \\e[38;5;89m\n", res);  
    }
  }

  text_white();
  printf("   Fin test color_cstring\n");
  return error;
}

int test_color_from_name()
{
  printf("   Debut test color_from_name\n");
  int error = 0;
  struct color* test = color_from_name("ROUGE");
  if (!strcmp("ROUGE", color_name(test)))
  {
    text_green();
    printf("    La couleur ROUGE est bien %s\n", color_name(test));
  } else {
    error ++;
    text_red();
    printf("    ERROR: La couleur %s est au lieu de ROUGE", color_name(test));
  }

  text_white();
  printf("   Fin test color_name\n");
  return error;
}


int execute_test_color()
{
  printf("Debut test color.c\n");
  int error_color_name = test_color_name();
  int error_cstring = test_color_cstring();
  int error_from_name = test_color_from_name();
  int error_tot = error_color_name + error_cstring + error_from_name;
  display_error(error_color_name, "de color_name");
  display_error(error_cstring, "de color_cstring");
  display_error(error_from_name, "de color_from_name");
  display_error(error_tot, " de color");

  text_white();
  printf("Fin test color.c\n");
  printf("-----------------------------------------\n");
  printf("\n");
  return error_tot;
}

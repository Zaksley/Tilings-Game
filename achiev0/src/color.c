#include <stdio.h>
#include <string.h>
#include "color.h"

#define nb_color 16

enum couleur { ROUGE, BLEU, VERT, JAUNE, ORANGE, MARRON,
		 ROSE, CYAN, MAGENTA, GRIS, NOIR, BLANC,
	       VIOLET, SAUMON, VERT_FONCE,  EMPTY=15};
struct color
{
  enum couleur col;
};

static struct color couleurs[16] =
  {
    { ROUGE },
    { BLEU },
    { VERT },
    { JAUNE },
    { ORANGE },
    { MARRON },
    { ROSE },
    { CYAN },
    { MAGENTA },
    { GRIS },
    { NOIR },
    { BLANC },
    { VIOLET },
    { SAUMON },
    { VERT_FONCE },
    { EMPTY }
  };

 static char * couleurs_string[16] =
  {
    "ROUGE",
    "BLEU",
    "VERT",
    "JAUNE",
    "ORANGE",
    "MARRON",
    "ROSE",
    "CYAN",
    "MAGENTA",
    "GRIS",
    "NOIR",
    "BLANC",
    "VIOLET",
    "SAUMON",
    "VERT_FONCE",
    "EMPTY"
  };

// A string giving the color name
const char* color_name(struct color* t)
{
  switch(t->col)
    {
    case 0:
      return "ROUGE";
      break;
    case 1:
      return "BLEU";
      break;
    case 2:
      return "VERT";
      break;
    case 3:
      return "JAUNE";
      break;
    case 4:
      return "ORANGE";
      break;
    case 5:
      return "MARRON";
      break;
    case 6:
      return "ROSE";
      break;
    case 7:
      return "CYAN";
      break;
    case 8:
      return "MAGENTA";
      break;
    case 9:
      return "GRIS";
      break;
    case 10:
      return "NOIR";
      break;
    case 11:
      return "BLANC";
      break;
    case 12:
      return "VIOLET";
      break;
    case 13:
      return "SAUMON";
      break;
    case 14:
      return "VERT_FONCE";
      break;
    case 15:
      return "EMPTY";
      break;

    default:
      return "ERROR";
      break;
    }
}
// A ANSI-colored string describing the color
const char* color_cstring(struct color* t)
{
  switch(t->col)
    {
    case 0: 
      return "\e[38;5;9m";
      break;
    case 1:
      return "\e[38;5;12m";
      break;
    case 2:
      return "\e[38;5;10m";
      break;
    case 3:
      return "\e[38;5;11m";
      break;
    case 4:
      return "\e[38;5;202m";
      break;
    case 5:
      return "\e[38;5;52m";
      break;
    case 6:
      return "\e[38;5;13m";
      break;
    case 7:
      return "\e[38;5;14m";
      break;
    case 8:
      return "\e[38;5;89m";
      break;
    case 9:
      return "\e[38;5;8m";
      break;
    case 10:
      return "\e[38;5;0m";
      break;
    case 11:
      return "\e[38;5;15m";
      break;
    case 12:
      return "\e[38;5;5m";
      break;
    case 13:
      return "\e[38;5;215m";
      break;
    case 14:
      return "\e[38;5;2m";
      break;
    case 15:
      //Empty
      return "ERROR";
      break;
      
    default:
      return "ERROR";
      break;
    }
};

// Return a color from its name, or NULL
struct color* color_from_name(const char* name)
{
  for (int i = 0; i < nb_color; i ++) {
    if (!strcmp(name, couleurs_string[i])) {
      return &couleurs[i];
    }
  }
  
  return NULL;
}



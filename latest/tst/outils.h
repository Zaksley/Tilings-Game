#ifndef _OUTILS_H_
#define _OUTILS_H_

/**
 * make the text green
 **/
void text_green();

/**
 * make the text red
 **/
void text_red();

/**
 * make the text white
 **/
void text_white();

/**
 * display and complete this :
 * if (nb_error == 0) {
 *      printf("\e[38;5;10m"); 
 *      printf("Il n'y a pas d'erreur dans les tests name\n");
 *  } else {
 *      printf("\e[38;5;9m");
 *      printf("Il y a %d erreurs dans les tests name\n", nb_error);
 *  }
 * 
 **/
void display_error(int nb_error, char * name);

#endif // _OUTILS_H_

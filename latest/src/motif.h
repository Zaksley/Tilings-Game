#ifndef _MOTIF_H_
#define _MOTIF_H_

struct board;

struct motif
{
    int (* test)(struct board *, int, int); //La fonction qui test si la case en ligne et colonne donné par les deux int contient le motif dans le board
    int actif; //Si actif est faux le motif serras ignoré lors du calcul des scores pour les motifs
    int score; //Le score rapporté par la réalisation du motif 
};

#endif // _MOTIF_H_

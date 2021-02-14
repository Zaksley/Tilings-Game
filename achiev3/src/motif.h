#ifndef _MOTIF_H_
#define _MOTIF_H_



struct board;

struct motif
{
    int (* test)(struct board *, int, int);
    int actif;
    int score;  
};

#endif // _MOTIF_H_

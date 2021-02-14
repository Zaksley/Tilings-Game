#ifndef _MOTIF_H_
#define _MOTIF_H_

#include "tile.h"
#include "rule.h"

struct board;

struct motif
{
    int (* test)(struct board *, int, int);
    int actif;
    int score;  
};

#endif // _MOTIF_H_

#ifndef AI_H
#define AI_H

#include "Grille.h"
#include "Solution.h"

void PlusCourtChemin(Solution *S, int i, int j, int k, int l);

void algorithme_naif(Grille *G, Solution *S);

#endif

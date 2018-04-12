#ifndef METHODE_NAIVE_H
#define METHODE_NAIVE_H

#include "Grille.h"
#include "Solution.h"

void RechercherCaseNaif_c(Grille *G, int c, int i, int j, int *k, int *l);

void RechercherCaseNaif_nn(Grille *G, int i, int j, int *k, int *l);

void algorithme_naif(Grille *G, Solution *S);


#endif

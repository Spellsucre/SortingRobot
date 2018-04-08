#ifndef METHODE_CIRCULAIRE_H
#define METHODE_CIRCULAIRE_H

#include "Grille.h"
#include "Solution.h"

void RechercherCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l);

void RechercherCaseCirculaire_nn(Grille *G, int i, int j, int *k, int *l);

void algorithme_circulaire(Grille *G, Solution *S);

#endif

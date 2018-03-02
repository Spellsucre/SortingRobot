#ifndef FONCTIONS_BASE_H
#define FONCTIONS_BASE_H


#include "Grille.h"
#include "Solution.h"

void PlusCourtChemin(Solution *S, int i, int j, int k, int l);

int caseNoire(Grille *G, int i, int j);

int pieceNoire(Grille *G, int i, int j);

int robotPortePiece(Grille *G);

int getCouleurPieceRobot(Grille *G);

int getCouleurCase(Grille *G, int i, int j);

int estDansGrille(Grille *G, int i, int j);

int distance(int i, int j, int k, int l);

int grilleTerminee(Grille *G);

void liberer(Grille *G);

#endif

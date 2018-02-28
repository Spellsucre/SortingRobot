#ifndef EXO1_H
#define EXO1_H


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


void RechercherCaseNaif_c(Grille *G, int c, int i, int j, int *k, int *l);

void RechercherCaseNaif_nn(Grille *G, int i, int j, int *k, int *l);

void algorithme_naif(Grille *G, Solution *S);


void RechercherCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l);

void RechercherCaseCirculaire_nn(Grille *G, int i, int j, int *k, int *l);

void algorithme_circulaire(Grille *G, Solution *S);

#endif

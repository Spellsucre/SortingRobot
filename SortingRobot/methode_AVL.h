#ifndef METHODE_AVL_H
#define METHODE_AVL_H

#include "fonctions_AVL.h"
#include "Grille.h"
#include "Solution.h"

typedef struct {
	int nbcoul;
	int nblig;
	AVL ***M;
} t_AVL;


t_AVL *creer_t_AVL(int nbcoul, int nblig);

t_AVL *initialiser_t_AVL(Grille *G);

void liberer_t_AVL(t_AVL *tavl);

void AVLrechercherPlusProcheCase(t_AVL *tavl, int c, int k, int l, int *u, int *v);

void algorithme_AVL(Grille *G, Solution *S);

void AVLrechercheJ(AVL *b, int jr, int *jres, int *dtmp);

#endif

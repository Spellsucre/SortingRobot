#ifndef METHODE_AVL_H
#define METHODE_AVL_H

#include "fonctions_AVL.h"
#include "Grille.h"
#include "Solution.h"

typedef struct {
	int nbcoul;
	int nblig;
	int cptr_noire;	//nombre de cases noires
	AVL ***M;
} t_AVL;

t_AVL *creer_t_AVL(int nbcoul, int nblig);

t_AVL *initialiser_t_AVL(Grille *G);

int AVLrechercheJ(AVL *b, int l, int dMin);

void liberer_t_AVL(t_AVL *tavl);

void AVLrechercherPlusProcheCase(t_AVL *tavl, int c, int k, int l, int *u, int *v);

void algorithme_AVL(Grille *G, Solution *S);

#endif

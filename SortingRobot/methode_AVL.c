#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fonctions_base.h"
#include "methode_AVL.h"
#include "methode_circulaire.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
t_AVL *creer_t_AVL(int nbcoul, int nblig){
	int c, i;
	
	//malloc de t_AVL*
	t_AVL *tavl = malloc(sizeof(t_AVL));
	if (!tavl) { printf("Erreur lors de l'allocation"); return NULL; }
	tavl->nbcoul = nbcoul;
	tavl->nblig = nblig;
	
	//malloc de M[nbcoul][nblig]
	tavl->M = malloc( sizeof(AVL**) * nbcoul );
	if (!tavl->M) { printf("Erreur lors de l'allocation"); return NULL; }
	for (c=0; c<nbcoul; c++){
		tavl->M[c] = malloc( sizeof(AVL*) * nblig );
		if (!tavl->M[c]) { printf("Erreur lors de l'allocation"); return NULL; }
	}
	
	//init des AVL* à NULL
	for (c=0; c<nbcoul; c++){
		for (i=0; i<nblig; i++){
			tavl->M[c][i] = NULL;
		}
	}

	return tavl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
t_AVL *initialiser_t_AVL(Grille *G){
	int c, m, n;
	
	t_AVL *tavl = creer_t_AVL(G->nbcoul, G->m);
	tavl->cptr_noire = G->cptr_noire;
	
	for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){
			if ( caseNoire(G, m, n) ) continue;
			c = G->T[m][n].fond;		
			tavl->M[c][m] = insererAVL(tavl->M[c][m], n);
		}
	}
	
	return tavl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ok??
void liberer_t_AVL(t_AVL *tavl){
	int c, i;
	if (!tavl) return;
	
	for (c=0; c < tavl->nbcoul; c++){
		for (i=0; i < tavl->nblig; i++){
			libererAVL(tavl->M[c][i]);
		}
	}
	free(tavl);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int AVLrechercheJ(AVL *b, int l, int dMin){
	if (!b){
		//printf("####### ERROR #######\n");
		return -1;
	}
	if (b->fg && b->fd){
		if (distJ(b->fg->j,l) > distJ(b->fd->j,l)){
			if (dMin > distJ(b->fd->j,l)){
				dMin=distJ(b->fd->j,l);
				return AVLrechercheJ(b->fd, l, dMin);
			}
		} else {
			if (dMin > distJ(b->fg->j,l)){
				dMin=distJ(b->fg->j,l);
				return AVLrechercheJ(b->fg, l, dMin);
			} 
		}		
		   
	} else if (b->fg && dMin > distJ(b->fg->j,l)){
		dMin=distJ(b->fg->j,l);
		return AVLrechercheJ(b->fg, l, dMin);
		
	} else if (b->fd && dMin > distJ(b->fd->j,l)){
		dMin=distJ(b->fd->j,l);
		return AVLrechercheJ(b->fd, l, dMin);
	}
	return b->j;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void AVLrechercherPlusProcheCase(t_AVL *tavl, int c, int k, int l, int *u, int *v){
	if (!tavl){ printf("tavl non existant"); return; }
	
	int jtmp, dMin, dCour, cpt=0;
	AVL *cour;
	
	*u= tavl->nblig * tavl->nblig; *v = tavl->nblig * tavl->nblig;
	dMin = distance(k,l,*u,*v);
	
	printf("Robot couleur %d en (%d, %d)\n", c, k, l);
	
	while (k+cpt < tavl->nblig || k-cpt >= 0){
		
		if (k+cpt < tavl->nblig){
			
			//printf("tavl: nbcoul = %d, nblig = %d\n", tavl->nbcoul, tavl->nblig);
			//printf("c = %d, k = %d, cpt = %d, k+cpt = %d\n", c, k, cpt, k+cpt);
			
			
			//printf("dbg_k+cpt_1\n");
			cour = tavl->M[c][k+cpt];
			printf("%d\n",cour!=NULL);
			//printf("dbg_k+cpt_2\n");
			//afficherAVL(cour);
			//printf("\n");
			
			//AVLtoDot()
			if(cour){
				printf("if cour +\n");
				jtmp = AVLrechercheJ(cour, l, dMin);
				dCour = distance(k, l, k+cpt, jtmp);			
				
				if (dCour < dMin){
					printf("dMin +\n");
					dMin = dCour;
					*u = k+cpt;
					*v = jtmp;
				}
			}
		}
		
		if (k-cpt >= 0){
			//printf("\n(k, l) = (%d, %d)\n", k, l);
			//printf("tavl: nbcoul = %d, nblig = %d\n", tavl->nbcoul, tavl->nblig);
			//printf("c = %d, k = %d, cpt = %d, k-cpt = %d\n", c, k, cpt, k-cpt);
			
			
			//printf("dbg_k-cpt_1\n");
			cour = tavl->M[c][k-cpt];
			printf("%d\n",cour!=NULL);
			//printf("dbg_k-cpt_2\n");
			//afficherAVL(cour);
			//printf("\n");
			
			if(cour){
				printf("if cour -\n");
				jtmp = AVLrechercheJ(cour, l, dMin);
				dCour = distance(k, l, k-cpt, jtmp);
				
				if (dCour < dMin){
					printf("dMin -\n");
					dMin = dCour;
					*u = k-cpt;
					*v = jtmp;
				}
			}
		}
		
		printf("=dbg: (u, v) = (%d, %d), cpt=%d\n", *u, *v, cpt);
		cpt++;
	}
	
	
	printf("res: (u, v) = (%d, %d)\n", *u, *v);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ok??
void algorithme_AVL(Grille *G, Solution *S){
	if (!G){ printf("Grille NULL, fin algo AVL"); return; }
	if (!S){ printf("Solution NULL, fin algo AVL"); return; }
	
	int c, u, v;
	
	t_AVL * tavl = initialiser_t_AVL(G);
	
	int i, j;
	for (i=0; i<tavl->nbcoul; i++){
		for (j=0; j<tavl->nblig; j++){
			AVLtoDot(tavl->M[i][j], i, j);
		}
	} 
	
	//application de l'algorithme
	while ( !grilleTerminee(G) ){
		if ( !robotPortePiece(G) ){
			RechercherCaseCirculaire_nn( G, G->ir, G->jr, &u, &v );
			PlusCourtChemin( S, G->ir, G->jr, u, v);
			//printf("dbg_if\t\tu = %d   |   v = %d\n", u, v);
			changement_case(G, u, v);
		} else {
			c = getCouleurPieceRobot(G);
			
			//printf("(ir, jr) = (%d, %d), c=%d\n", G->ir, G->jr, c);
			AVLrechercherPlusProcheCase(tavl, c, G->ir, G->jr, &u, &v);
			printf("dbg_else\tu = %d   |   v = %d\n\n", u, v);
			
			PlusCourtChemin( S, G->ir, G->jr, u, v);
			changement_case(G, u, v);
			tavl->M[c][u] = supprimeAVL(tavl->M[c][u], v);
		}
		swap_case(G);
		Ajout_action( S, 'S');
		//printf("_______SWAP EN (%d, %d)_______\n\n\n", G->ir, G->jr);
	}
	
	liberer_t_AVL(tavl);
}



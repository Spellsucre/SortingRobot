#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fonctions_base.h"
#include "methode_AVL.h"
#include "methode_circulaire.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
t_AVL *creer_t_AVL(int nbcoul, int nblig){
	int c, i;
	
	// malloc de t_AVL*
	t_AVL *tavl = malloc( sizeof(t_AVL) );
	if (!tavl) { printf("Erreur lors de l'allocation"); return NULL; }
	tavl->nbcoul = nbcoul;
	tavl->nblig = nblig;
	
	// malloc de M[nbcoul][nblig]
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
	
	// malloc
	t_AVL *tavl = creer_t_AVL(G->nbcoul, G->m);
	
	// initialisation
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
void AVLrechercheJ(AVL *b, int jr, int *jres, int *dtmp){
	if (!b) return;
	
	int dCour = distJ(b->j, jr);
	
	if ( (dCour < *dtmp) || (dCour == *dtmp && b->j < *jres) ){
		*jres = b->j;
		*dtmp = dCour;
	}

	if (jr < b->j)
		AVLrechercheJ(b->fg, jr, jres, dtmp);
	else
		AVLrechercheJ(b->fd, jr, jres, dtmp);
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void AVLrechercherPlusProcheCase(t_AVL *tavl, int c, int k, int l, int *u, int *v){
	if (!tavl){ printf("tavl non existant"); return; }
	
	int cpt=0, dMin, jtmp, dCour, dtmp, dInf;
	AVL *cour;

	*u = tavl->nblig * tavl->nblig;		*v = tavl->nblig * tavl->nblig;
	
	dInf = distance(k,l,*u,*v);
	dMin = dInf;
	
	while ( k-cpt >= 0 || k+cpt < tavl->nblig ){
		
		//if ( dMin!=dInf && cpt > dMin ) break;
		
		// cas 1: k-cpt
		if (k-cpt >= 0){
			cour = tavl->M[c][k-cpt];
			if (cour){
				jtmp = tavl->nblig * tavl->nblig;
				dtmp = tavl->nblig * tavl->nblig;
				AVLrechercheJ(cour, l, &jtmp, &dtmp);
				
				dCour = distance(k, l, k-cpt, jtmp);
				if (dCour <= dMin){	// k-cpt prévaut donc test à égalité
					dMin = dCour;
					*u = k-cpt;
					*v = jtmp;
				}
			}
		}
		
		// cas 2: k+cpt
		if (k+cpt < tavl->nblig){
			cour = tavl->M[c][k+cpt];
			if (cour){
				jtmp = tavl->nblig * tavl->nblig;
				dtmp = tavl->nblig * tavl->nblig;
				AVLrechercheJ(cour, l, &jtmp, &dtmp);
				
				dCour = distance(k, l, k+cpt, jtmp);			
				if (dCour < dMin){
					dMin = dCour;
					*u = k+cpt;
					*v = jtmp;
				}
			}
		}
		
		//printf("cpt = %d,    dMin = %d,    res = (%d, %d)\n", cpt, dMin, *u, *v);
		
		cpt++;
		
		
	}
	
	//printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_AVL(Grille *G, Solution *S){
	if (!G){ printf("Grille NULL, fin algo AVL"); return; }
	if (!S){ printf("Solution NULL, fin algo AVL"); return; }
	
	int c, u, v;
	// création et initialisation de tavl
	t_AVL *tavl = initialiser_t_AVL(G);

	// application de l'algorithme
	while ( !grilleTerminee(G) ){
		if ( !robotPortePiece(G) ){
			RechercherCaseCirculaire_nn(G, G->ir, G->jr, &u, &v);
			//PlusCourtChemin(S, G->ir, G->jr, u, v);
			changement_case(G, u, v);
		} else {
			c = getCouleurPieceRobot(G);
			AVLrechercherPlusProcheCase(tavl, c, G->ir, G->jr, &u, &v);			
			//PlusCourtChemin(S, G->ir, G->jr, u, v);
			changement_case(G, u, v);
			tavl->M[c][u] = supprimeAVL(tavl->M[c][u], v);
		}
		swap_case(G);
		//Ajout_action( S, 'S');
	}
	
	liberer_t_AVL(tavl);
}



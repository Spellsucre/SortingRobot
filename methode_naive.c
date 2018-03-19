#include <stdio.h>
#include <stdlib.h>

#include "methode_naive.h"
#include "fonctions_base.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) la plus proche de la case
// (i,j) et dont la couleur est c
void RechercherCaseNaif_c(Grille *G, int c, int i, int j, int *k, int *l){
	int m, n;
	
	*k= G->m * G->n; *l = G->m * G->n;
	int dMin = distance(i, j, *k, *l);
	
	for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){	//parcours de la grille
			
			if ( !caseNoire(G,m,n) && getCouleurCase(G,m,n)==c ){
				if ( distance(i,j, m,n) < dMin){
					*k = m;
					*l = n;
					dMin = distance	(i, j, m, n);						
				}
			}
			
		}
	}
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) non vide et possédant une
// pièce la plus proche de la case (i,j)
void RechercherCaseNaif_nn(Grille *G, int i, int j, int *k, int *l){
	int m, n;
	
	*k= G->m * G->n; *l = G->m * G->n;
	int dMin = distance(i, j, *k, *l);
	
	for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){	//parcours de la grille
			
			if ( !caseNoire(G, m, n) && !pieceNoire(G, m, n) ){
				if ( distance(i,j, m,n) < dMin){
					*k = m;
					*l = n;
					dMin = distance	(i, j, m, n);						
				}
			}
			
		}
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_naif(Grille *G, Solution *S){
    int k, l;
    
    while ( !grilleTerminee(G) ){
		if( !robotPortePiece(G) ){  
		    RechercherCaseNaif_nn( G, G->ir, G->jr, &k, &l );
		}else{
			RechercherCaseNaif_c( G, getCouleurPieceRobot(G), G->ir, G->jr, &k, &l );
		}
		PlusCourtChemin( S, G->ir, G->jr, k, l);
		changement_case(G, k, l);
		swap_case(G);
		Ajout_action( S, 'S');
    }
}



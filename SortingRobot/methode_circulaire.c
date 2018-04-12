#include <stdio.h>
#include <stdlib.h>

#include "methode_circulaire.h"
#include "fonctions_base.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) la plus proche de la case
// (i,j) et dont la couleur est c
void RechercherCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l){
	int h, d, x, y;
	
	for (d=1; d<G->m*G->n; d++){
		//case du haut
		h=0;
		x = j;
		y = i-d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& getCouleurCase(G,y,x)==c ){
			*k=y; *l=x;
			return;
		}
		h++;
	
		//couple cases intermédiare haut
		while (h<d){
			y++;
			x=j-h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& getCouleurCase(G,y,x)==c ){
				*k=y; *l=x;
				return;
			}
			x=j+h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& getCouleurCase(G,y,x)==c ){
				*k=y; *l=x;
				return;
			}
			h++;
		}
	
		//couple cases milieu
		y++;
		x=j-h;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& getCouleurCase(G,y,x)==c ){
			*k=y; *l=x;
			return;
		}
		x=j+h;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& getCouleurCase(G,y,x)==c ){
			*k=y; *l=x;
			return;
		}
		h--;
	
		//couple cases intermédiare bas
		while (h>0){
			y++;
			x=j-h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& getCouleurCase(G,y,x)==c ){
				*k=y; *l=x;
				return;
			}
			x=j+h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& getCouleurCase(G,y,x)==c ){
				*k=y; *l=x;
				return;
			}
			h--;
		}
	
		//case du bas
		x = j;
		y = i+d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& getCouleurCase(G,y,x)==c ){
			*k=y; *l=x;
			return;
		}
		
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) non vide et possédant une
// pièce la plus proche de la case (i,j)
void RechercherCaseCirculaire_nn(Grille *G, int i, int j, int *k, int *l){
	int h, d, x, y;

	// d=0
	if ( estDansGrille(G,i,j) && !caseNoire(G,i,j)
			&& !pieceNoire(G,i,j) ){
		*k=i; *l=j;
		return;
	}
	
	for (d=1; d<G->m*G->n; d++){
		//case du haut
		h=0;
		x = j;
		y = i-d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& !pieceNoire(G,y,x) ){
			*k=y; *l=x;
			return;
		}
		h++;
	
		//couple cases intermédiare haut
		while (h<d){
			y++;
			x=j-h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& !pieceNoire(G,y,x) ){
				*k=y; *l=x;
				return;
			}
			x=j+h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& !pieceNoire(G,y,x) ){
				*k=y; *l=x;
				return;
			}
			h++;
		}
	
		//couple cases milieu
		y++;
		x=j-h;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& !pieceNoire(G,y,x) ){
			*k=y; *l=x;
			return;
		}
		x=j+h;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& !pieceNoire(G,y,x) ){
			*k=y; *l=x;
			return;
		}
		h--;
	
		//couple cases intermédiare bas
		while (h>0){
			y++;
			x=j-h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& !pieceNoire(G,y,x) ){
				*k=y; *l=x;
				return;
			}
			x=j+h;
			if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
					&& !pieceNoire(G,y,x) ){
				*k=y; *l=x;
				return;
			}
			h--;
		}
	
		//case du bas
		x = j;
		y = i+d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& !pieceNoire(G,y,x) ){
			*k=y; *l=x;
			return;
		}
		
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_circulaire(Grille *G, Solution *S){
    int k, l;
    
    while ( !grilleTerminee(G) ){
		if( !robotPortePiece(G) ){
		    RechercherCaseCirculaire_nn( G, G->ir, G->jr, &k, &l );
		}else{
			RechercherCaseCirculaire_c( G, getCouleurPieceRobot(G), G->ir, G->jr, &k, &l );
		}
		PlusCourtChemin( S, G->ir, G->jr, k, l);
		changement_case(G, k, l);
		swap_case(G);
		Ajout_action( S, 'S');
    }
}



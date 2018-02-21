#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "exo1.h"
#include "Solution.h"
#include "Grille.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans S la séquence de mouvements correspondant au plus court chemin entre
// le point (i,j) et le point (k,l)
void PlusCourtChemin(Solution *S, int i, int j, int k, int l){
	int q, d;
	char deplacementx, deplacementy;
	
	d = k-i;
	if (d<0) deplacementx='U';
	else if (d>0) deplacementx='D';
	for (q=0; q<abs(d); q++) Ajout_action(S, deplacementx);
	
	d = l-j;
	if (d<0) deplacementy='L';
	else if (d>0) deplacementy='R';
	for (q=0; q<abs(d); q++) Ajout_action(S, deplacementy);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si la case (i,j) est noire, 0 sinon
int caseNoire(Grille *G, int i, int j){
	return G->T[i][j].fond == G->T[i][j].piece ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si la pièce en (i,j) est noire, 0 sinon
int pieceNoire(Grille *G, int i, int j){
	//pas de pièce => absence de couleur => noir
	return G->T[i][j].piece == -1 ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si le robot porte une pièce, 0 sinon
int robotPortePiece(Grille *G){
	return G->T[G->ir][G->jr].robot >= 0 ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne la couleur de la pièce que porte le robot, -1 sinon
int getCouleurPieceRobot(Grille *G){
	return G->T[G->ir][G->jr].robot ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// reourne la couleur de la case (i,j)
int getCouleurCase(Grille *G, int i, int j){
	return G->T[i][j].fond;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si (i,j) est contenu dans la grille
int estDansGrille(Grille *G, int i, int j){
	if ( i<0 || j<0 || i>=G->m || j>=G->n ) return 0;
	return 1;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) la plus proche de la case
// (i,j) et dont la couleur est c, (-1,-1) si elle n'existe pas
void RechercherCaseNaif_c(Grille *G, int c, int i, int j, int *k, int *l){
	int h, d, x, y;// d_max;
	
	//d_max est la longeur de la diagonale de la grille
	//d_max = (int) sqrt( pow(G->m,2) + pow(G->n,2) ); 
	
	for (d=0; d<G->m*G->n; d++){
		
		//case du haut
		h=0;
		x = i;
		y = j-d;
		if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
				&& getCouleurCase(G,x,y)==c ){
			*k=x; *l=y;
			return;
		}
		h++;
	
		//couple cases intermédiare haut
		while (h<d){
			y++;
			x=i-h;
			if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
					&& getCouleurCase(G,x,y)==c ){
				*k=x; *l=y;
				return;
			}
			x=i+h;
			if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
					&& getCouleurCase(G,x,y)==c ){
				*k=x; *l=y;
				return;
			}
			h++;
		}
	
		//couple cases milieu
		y++;
		x=i-h;
		if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
				&& getCouleurCase(G,x,y)==c ){
			*k=x; *l=y;
			return;
		}
		x=i+h;
		if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
				&& getCouleurCase(G,x,y)==c ){
			*k=x; *l=y;
			return;
		}
		h--;
	
		//couple cases intermédiare bas
		while (h>0){
			y++;
			x=i-h;
			if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
					&& getCouleurCase(G,x,y)==c ){
				*k=x; *l=y;
				return;
			}
			x=i+h;
			if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
					&& getCouleurCase(G,x,y)==c ){
				*k=x; *l=y;
				return;
			}
			h--;
		}
	
		//case du bas
		x = i;
		y = d;
		if ( estDansGrille(G,x,y) && !caseNoire(G,x,y)
				&& getCouleurCase(G,x,y)==c ){
			*k=x; *l=y;
			return;
		}
		
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) non vide et possédant une
// pièce la plus proche de la case (i,j), (-1,-1) si elle n'existe pas
void RechercherCaseNaif_nn(Grille *G, int i, int j, int *k, int *l){
	int h, d, x, y;// d_max;
	
	//d_max est la longeur de la diagonale de la grille
	//d_max = (int) sqrt( pow(G->m,2) + pow(G->n,2) ); 
	
	
	for (d=0; d<G->m*G->n; d++){
		
		//case du haut
		h=0;
		x = i;
		y = j-d;
		if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
				&& !pieceNoire(G, x, y) ){
			*k=x; *l=y;
			return;
		}
		h++;
	
		//couple cases intermédiare haut
		while (h<d){
			y++;
			x=i-h;
			if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
					&& !pieceNoire(G, x, y) ){
				*k=x; *l=y;
				return;
			}
			x=i+h;
			if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
					&& !pieceNoire(G, x, y) ){
				*k=x; *l=y;
				return;
			}
			h++;
		}
	
		//couple cases milieu
		y++;
		x=i-h;
		if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
				&& !pieceNoire(G, x, y) ){
			*k=x; *l=y;
			return;
		}
		x=i+h;
		if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
				&& !pieceNoire(G, x, y) ){
			*k=x; *l=y;
			return;
		}
		h--;
	
		//couple cases intermédiare bas
		while (h>0){
			y++;
			x=i-h;
			if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
					&& !pieceNoire(G, x, y) ){
				*k=x; *l=y;
				return;
			}
			x=i+h;
			if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
					&& !pieceNoire(G, x, y) ){
				*k=x; *l=y;
				return;
			}
			h--;
		}
	
		//case du bas
		x = i;
		y = d;
		if ( estDansGrille(G, x, y) && !caseNoire(G, x, y)
				&& !pieceNoire(G, x, y) ){
			*k=x; *l=y;
			return;
		}
		
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_naif(Grille *G, Solution *S){
    int k, l;
    
    while (G->cptr_noire < G->m * G->n){
    	
    	//si le robot n'a pas de piece, il va prendre celle la plus proche
        if( !robotPortePiece(G) ){            
            RechercherCaseNaif_nn( G, G->ir, G->jr, &k, &l );
            PlusCourtChemin( S, G->ir, G->jr, k, l );
            changement_case(G, k, l);            
            
            swap_case(G);
            Ajout_action( S, 'S' );
        }
        
        //le robot a une piece et va la poser sur la case correspondante
        RechercherCaseNaif_c( G, getCouleurPieceRobot(G), G->ir, G->jr, &k, &l );
        PlusCourtChemin( S, G->ir, G->jr, k, l);
        changement_case(G, k, l);
        
        swap_case(G);
        Ajout_action( S, 'S');
    }
}



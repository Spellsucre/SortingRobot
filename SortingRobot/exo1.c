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
	if (d<0) deplacementy='U';
	else if (d>0) deplacementy='D';
	for (q=0; q<abs(d); q++) Ajout_action(S, deplacementy);
		
	
	d = l-j;
	if (d<0) deplacementx='L';
	else if (d>0) deplacementx='R';
	for (q=0; q<abs(d); q++) Ajout_action(S, deplacementx);
	
	//printf("(%d,%d) -> (%d,%d)\n", i,j,k,l);
	//Affiche(S);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si la case (i,j) est noire, 0 sinon
int caseNoire(Grille *G, int i, int j){
	//printf("dbg caseNoire (%d,%d)\n", i, j);
	return G->T[i][j].fond == G->T[i][j].piece ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si la pièce en (i,j) est noire, 0 sinon
int pieceNoire(Grille *G, int i, int j){
	//pas de pièce => absence de couleur => noir
	//printf("dbg pieceNoire (%d,%d)\n\n", i, j);
	return G->T[i][j].piece == -1 ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si le robot porte une pièce, 0 sinon
int robotPortePiece(Grille *G){
	//printf("dbg robotPortePiece (%d,%d) = %d\n", G->ir, G->jr, G->T[G->ir][G->jr].robot >= 0);
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
	//printf("dbg getCouleurCase (%d,%d)\n\n", i, j);
	return G->T[i][j].fond;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si (i,j) est contenu dans la grille
int estDansGrille(Grille *G, int i, int j){
	//printf("dbg estDansGrille (%d,%d)\n", i, j);
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
	
	//x, j, l : col
	//y, i, k : lig
	
	for (d=0; d<G->m*G->n; d++){
		//printf("c_d = %d\n", d);
		//case du haut
		h=0;
		x = j;
		y = i-d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& getCouleurCase(G,y,x)==c ){
			*k=y; *l=x;
			return;
		}
		
		if (d==0) continue;
		
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
		y = d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& getCouleurCase(G,y,x)==c ){
			*k=y; *l=x;
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
		//printf("nn_d = %d\n", d);
		//case du haut
		h=0;
		x = j;
		y = i-d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& !pieceNoire(G,y,x) ){
			*k=y; *l=x;
			return;
		}
		
		if (d==0) continue;
		
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
		y = d;
		if ( estDansGrille(G,y,x) && !caseNoire(G,y,x)
				&& !pieceNoire(G,y,x) ){
			*k=y; *l=x;
			return;
		}
		
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_naif(Grille *G, Solution *S){
    int k, l;
    
    while (G->cptr_noire < G->m * G->n){
    	
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



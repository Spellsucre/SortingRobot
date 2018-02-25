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
	int m, n;
	
	//le point (k_,l_) d'origine sort de la grille
	int k_= G->m * G->n, l_ = G->m * G->n;
	
	for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){	//parcours de la grille
			
			if ( !caseNoire(G,m,n) && G->T[m][n].fond == c ){	//si la case est de couleur c:
				if ( abs(i-m)<abs(k_-m) ){	//si la distance en lignes est inf.:
					if ( abs(j-n)<abs(l_-n) ){	//et la dist. en col. aussi:
						//printf("Couleur case: %d\nCouleur robot: %d\n", G->T[m][n].fond, c);
						k_ = m;	//cette case est de la couleur demandée et est
						l_ = n;	//plus proche au point (i,j) que la case (k_,l_)
					}	
				}
			}
			
		}
	}
	
	//si k_ ou l_ vallent m*n, cela signifie qu'il n'y a pas de case de couleur c
	if ( (k_ == G->m * G->n) || (l_ == G->m * G->n) ){
		*k = -1;
		*l = -1;
	}else{
		*k = k_;
		*l = l_;
	}
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) non vide et possédant une
// pièce la plus proche de la case (i,j), (-1,-1) si elle n'existe pas
void RechercherCaseNaif_nn(Grille *G, int i, int j, int *k, int *l){
	int m, n;
	
	//le point (k_,l_) d'origine sort de la grille
	int k_= G->m * G->n, l_ = G->m * G->n;
	
	for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){	//parcours de la grille
			
			if ( !caseNoire(G, m, n) &&
				 !pieceNoire(G, m, n) ){	//si la case est nn et a une piece:
				if ( abs(i-m)<abs(k_-m) ){	//si la distance en lignes est inf.:
					if ( abs(j-n)<abs(l_-n) ){	//et la dist. en col. aussi:
						k_ = m;	//cette case est de la couleur demandée et est
						l_ = n;	//plus proche au point (i,j) que la case (k_,l_)
					}	
				}
			}
			
		}
	}
	
	//si k_ ou l_ vallent m*n, cela signifie qu'il n'y a pas de case non vide
	if ( (k_ == G->m * G->n) || (l_ == G->m * G->n) ){
		*k = -1;
		*l = -1;
	}else{
		*k = k_;
		*l = l_;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// met dans k et l les coordonnées de la case (k,l) la plus proche de la case
// (i,j) et dont la couleur est c, (-1,-1) si elle n'existe pas
void RechercherCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l){
	int h, d, x, y;// d_max;
	
	//d_max est la longeur de la diagonale de la grille
	//d_max = (int) sqrt( pow(G->m,2) + pow(G->n,2) ); 

	
	for (d=0; d<G->m*G->n; d++){
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
void RechercherCaseCirculaire_nn(Grille *G, int i, int j, int *k, int *l){
	int h, d, x, y;// d_max;
	
	//d_max est la longeur de la diagonale de la grille
	//d_max = (int) sqrt( pow(G->m,2) + pow(G->n,2) ); 
	
	
	for (d=0; d<G->m*G->n; d++){
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_circulaire(Grille *G, Solution *S){
    int k, l;
    
    while (G->cptr_noire < G->m * G->n){
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



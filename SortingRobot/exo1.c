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
	//printf("dbg caseNoire (%d,%d)\n", i ,j);
	return G->T[i][j].fond == G->T[i][j].piece ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si la pièce en (i,j) est noire, 0 sinon
int pieceNoire(Grille *G, int i, int j){
	//pas de pièce => absence de couleur => noir
	//printf("dbg pieceNoire (%d,%d)\n", i ,j);
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
	//printf("dbg getCouleurCase : %d\n", G->T[i][j].fond);
	return G->T[i][j].fond;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si (i,j) est contenu dans la grille
int estDansGrille(Grille *G, int i, int j){
	//printf("dbg estDansGrille (%d,%d)\n", i ,j);
	if ( i<0 || j<0 || i>=G->m || j>=G->n ) return 0;
	return 1;
}

int distance(int i, int j, int k, int l){
	return abs(k-i) + abs(l-j) ;
}

int grilleTerminee(Grille *G){
	return G->cptr_noire == G->m * G->n ;
}

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
		
		//if (d==0) continue;
		
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
		
		//if (d==0) continue;
		
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



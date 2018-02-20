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

double distance(int i, int j, int k, int l){
    return sqrt((k-i)*(k-i)+(l-j)*(l-j)*1.0);
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
			
			if ( G->T[m][n].fond == c ){	//si la case est de couleur c:
				if ( distance( i, j, m, n) < distance( i, j, k_, l_) ){	//si la distance en lignes est inf.:
						//et la dist. en col. aussi:
						k_ = m;	//cette case est de la couleur demandée et est
						l_ = n;	//plus proche au point (i,j) que la case (k_,l_)	
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
				if ( distance( i, j, m, n) < distance( i, j, k_, l_) ){	//si la somme des distance en lignes et en col est inf.:
						k_ = m;	//Cette case est
						l_ = n;	//plus proche au point (i,j) que la case (k_,l_)	
				}
			}
			
		}
	}
	
	//si k_ ou l_ vallent m*n, cela signifie qu'il n'y a pas de case non noire contenant une piece
	if ( (k_ == G->m * G->n) || (l_ == G->m * G->n) ){
		*k = -1;
		*l = -1;
	}else{
		*k = k_;
		*l = l_;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_naif(Grille *G, Solution *S){
    int cpt = 0;
    int k,l;
    while (cpt<G->cptr_noire){
        if(!robotPortePiece(G)){
            RechercherCaseNaif_nn( G, G->ir, G->jr, &k, &l );
            printf("Knn : %d,\nLnn : %d.\n",k,l);
            PlusCourtChemin( S, G->ir, G->jr, k, l );
            Ajout_action( S, 'S' );
        }
        RechercherCaseNaif_c( G, G->T[G->ir][G->jr].robot, G->ir, G->jr, &k, &l );
        printf("Kc : %d,\nLc : %d.\n",k,l);
        PlusCourtChemin( S, G->ir, G->jr, k, l);
        Ajout_action( S, 'S');
        cpt++;
    }
}



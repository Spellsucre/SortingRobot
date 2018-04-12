#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fonctions_base.h"
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne le nombre de pas séparant les points (i,j) et (k,l)
int distance(int i, int j, int k, int l){
	return abs(k-i) + abs(l-j) ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// retourne 1 si la grille ne comporte que des cases noires, 0 sinon
int grilleTerminee(Grille *G){
	return G->cptr_noire == G->m * G->n ;
}



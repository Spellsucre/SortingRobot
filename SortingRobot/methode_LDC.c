#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "methode_LDC.h"
#include "fonctions_base.h"
#include "methode_circulaire.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Creer cellule avec coordonnées i, j

CelluleLDC* creerCellule(int i, int j){
    CelluleLDC *cel = malloc(sizeof(CelluleLDC));
    if (cel == NULL){
        printf("Erreur lors de l'allocation");
        return NULL;
    }
    cel->i=i;
    cel->j=j;
    cel->prec=NULL;
    cel->suiv=NULL;
    return cel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Initialise une ldc déjà allouée

void LDCInitialise(LDC *ldc){
    if( ldc != NULL){
        ldc->premier=NULL;
        ldc->dernier=NULL;
    }
    else
        printf("Liste non existante");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Retourne true si la liste est vide

int LDCVide(LDC *ldc){
    if(ldc == NULL){
        printf("Liste non existante");
        return 0;
    }
    return (ldc->premier==NULL && ldc->dernier == NULL);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Insere un élément en fin de ldc, dont les coordonnées sont passées en argument

void LDCInsererEnFin(LDC *ldc, int i, int j){
    if(ldc == NULL){
        printf("Liste à initialiser avant d'insérer!");
        return;
    }
    CelluleLDC *cel = creerCellule( i , j );
    if ( LDCVide(ldc) ){ 
        ldc->premier=cel;
        ldc->dernier=cel;
        return;
    }
    ldc->dernier->suiv=cel;
    cel->prec=ldc->dernier;
    ldc->dernier=cel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Enleve la première occurence de la cellule (à savoir celle qui a les même coordonnées, une seule dans toute la matrice)

void LDCEnleverCellule(LDC* ldc, CelluleLDC *cel){
    if(ldc == NULL){
        printf("Liste non existante");
        return;
    }
    if(LDCVide(ldc)){
        printf("Liste vide suppression impossible");
        return;
    }
    if(ldc->premier == cel)
        ldc->premier=cel->suiv;
    if(ldc->dernier == cel)
        ldc->dernier = cel->prec;
    if(cel->prec)
        cel->prec->suiv = cel->suiv;
    if(cel->suiv)
        cel->suiv->prec = cel->prec;
    free(cel);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Affiche les cases sous format "Cell à ( i , j )"

void LDCafficher(LDC *ldc){
    if(ldc == NULL){
        printf("Liste non existante");
        return;
    }
    if(LDCVide(ldc)){
        printf("Liste vide");
        return;
    }
    CelluleLDC *cour=ldc->premier;
    while(cour){
        printf("Cell ( %d , %d )\t",cour->i,cour->j);
        cour=cour->suiv;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Free toute la ldc (cases une par une + elle meme)

void LDCdesalloue(LDC *ldc){
    if(ldc == NULL){
        printf("Liste non existante");
        return;
    }
    if(LDCVide(ldc)){
        free(ldc);
        return;
    }
    CelluleLDC *cour=ldc->premier;
    CelluleLDC *tmp;
    while(cour){
        tmp=cour->suiv;
        free(cour);
        cour=tmp;
    }
    free(ldc);
}

CelluleLDC* LDCrechercherPlusProcheCase(LDC* ldc, int i, int j){
    if(ldc == NULL){
        printf("Liste non existante");
        return NULL;
    }
    if(LDCVide(ldc)){
        printf("Liste vide");
        return NULL;
    }
    
    CelluleLDC *cour=ldc->premier;
    CelluleLDC *Cproche=cour;
    int dMin = distance(i, j, Cproche->i, Cproche->j);
    
    while(cour){
        if ( distance(i,j, cour->i, cour->j) < dMin){
            Cproche = cour;
			dMin = distance(i, j, Cproche->i, Cproche->j);						
		}
        cour=cour->suiv;
    }
    
    return Cproche;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

void algorithme_parcouleur(Grille *G, Solution *S){
    //Initialisation de TC le tableau de LDC de taille nbcoul (une case par couleur)
    LDC **TC = malloc(G->nbcoul*sizeof(LDC*));
    int q, m, n, k, l;
    for (q=0; q<G->nbcoul; q++){
        TC[q]=malloc(sizeof(LDC));
        LDCInitialise(TC[q]);
    }
    int indice;
    
    for (m=0; m<G->m; m++){
		for (n=0; n<G->n; n++){
			if( caseNoire(G, m, n) ) continue;
		    indice=G->T[m][n].fond;
		    LDCInsererEnFin(TC[indice], m, n); 
        }
    }

    CelluleLDC *target= malloc(sizeof(CelluleLDC));
    while ( !grilleTerminee(G)){
		if( !robotPortePiece(G) ){  
		    RechercherCaseCirculaire_nn( G, G->ir, G->jr, &k, &l );
		    PlusCourtChemin( S, G->ir, G->jr, k, l);
		    changement_case(G, k, l);
		}else{
			target = LDCrechercherPlusProcheCase(TC[getCouleurPieceRobot(G)], G->ir, G->jr);
			PlusCourtChemin( S, G->ir, G->jr, target->i, target->j);
			changement_case(G, target->i, target->j);
			indice=getCouleurPieceRobot(G);
			LDCEnleverCellule(TC[indice],target);
		}
		swap_case(G);
		Ajout_action( S, 'S');
    }
    
    for (k=0; k<G->nbcoul; k++){
        LDCdesalloue(TC[k]);
    }
    free(TC);
}

#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

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

void LDCInitialise(LDC *ldc){
    if( ldc != NULL){
        ldc->premier=NULL;
        ldc->dernier=NULL;
    }
    else
        printf("Liste non existante");
}

int LDCVide(LDC *ldc){
    if(ldc == NULL){
        printf("Liste non existante");
        return 0;
    }
    return (ldc->premier==NULL && ldc->dernier == NULL);
}

void LDCInsererEnFin(LDC *ldc, int i, int j){
    if(ldc == NULL){
        printf("Liste à initialiser avant d'insérer!");
        return;
    }
    CelluleLDC *cel = creerCellule( i , j );
    if ( LDCvide(ldc) ){ 
        ldc->premier=cel;
        ldc->dernier=cel;
        return;
    }
    ldc->dernier->suiv=cel;
    ldc->dernier=cel;
}

void LDCEnleverCellule(LDC* ldc, CelluleLDC *cel){
    if(ldc == NULL){
        printf("Liste non existante");
        return;
    }
    if(LDCvide(ldc)){
        printf("Liste vide");
        return;
    }
    CelluleLDC *cour=ldc->premier;
    while(cour){
        if(cel->i==cour->i && cel->j==cour->j){
            cour->prec->suiv=cour->suiv;
            cour->suiv->prec=cour->prec;
            free(cour);
            return;
        }
        cour=cour->suiv;
    }
    printf("Cellule non trouvée");
}

void LDCafficher(LDC *ldc){
    if(ldc == NULL){
        printf("Liste non existante");
        return;
    }
    if(LDCvide(ldc)){
        printf("Liste vide");
        return;
    }
    CelluleLDC *cour=ldc->premier;
    while(cour){
        printf("Cell à ( %d , %d )",cour->i,cour->j);
        cour=cour->suiv;
    }
}

void LDCdesalloue(LDC *ldc){
    if(ldc == NULL){
        printf("Liste non existante");
        return;
    }
    if(LDCvide(ldc)){
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

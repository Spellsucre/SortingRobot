#include <stdio.h>
#include <stdlib.h>

#include "Ensemble.h"

ElemEnsemble* creerElem(int i, int j, int indice){
    ElemEnsemble *el = malloc(sizeof(ElemEnsemble));
    el->i=i;
    el->j=j;
    el->indice=indice;
}

void EnsembleInitialise(Ensemble *E, int taille){
    E->taille=taille;
    E->nbElem=0;
    E->tab=malloc(sizeof(ElemEnsemble)*taille);
}

/* Test si liste vide */
int EnsembleVide(Ensemble* E){
    return taille==0;
}

void EnsembleAdd(Ensemble* E, int i,int j){
    if(E->nbElem >= E->taille){
        print("Ensemble plein !");   
        return;
    }
    ElemEnsemble *el = creerElem(i, j, E->nbElem);
    E->tab[nbElem]=el;
    E->nbElem++;
}

ElemEnsemble *EnsemblePop(Ensemble* E, int indice){
    int k, decal=1;
    ElemEnsemble *el;
    for(k=0;k<E->nbElem;k++){
        if ( decal == 0 ){
            E->tab[k-1]==E->tab[k];
        }
        else if ( E->tab[k]->indice==indice){
            decal = 0;
            el=E->tab[k];
        }
    }
    return el;
}

ElemEnsemble *EnsembleTrouve(Ensemble* E, int indice){
    int k;
    ElemEnsemble *el;
    for(k=0;k<E->nbElem;k++){
        else if ( E->tab[k]->indice==indice){
            el=E->tab[k];
            break;
        }
    }
    return el;
}


void Ensembleafficher(Ensemble* E){
}

void Ensembledesalloue(Ensemble* E){
    int k;
    for(k=0;k<E->nbElem;k++)
        free(E->tab[k]);
    free(E);
}

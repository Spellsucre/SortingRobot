#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Ensemble.h"
#include "Graphe.h"

int DistanceTSP(Ensemble S, ElemEnsemble* c, int **M){
    int k, min=INT_MAX, dopt;
    if (S.nbElem<=1)
        return M[0][c->indice];
    
    for(k=0;k<S.nbElem;k++){
        EnsemblePop(S, c->indice);
        dopt=(DistanceTSP(S,EnsembleTrouve(S, k))+ M[0][c->indice]);
        if (dopt<min)
            min=dopt;
    }
}

void Algo_Held_Karp(Graphe G){
    int **M, k, l, taille= G->m*G->n;
    Ensemble *S=malloc(sizeof(Ensemble);
    EnsembleInitialise(S,taille);
    for(k=0;k<taille;k++)
        for(l=0;l<taille;l++){
            EnsembleAdd(S, G->Tsom[k][l]->i, G->Tsom[k][l]->i); 
            
        }
}

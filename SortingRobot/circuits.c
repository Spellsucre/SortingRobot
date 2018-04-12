#include <stdio.h>
#include <stdlib.h>
#include "Graphe.h"
#include "ListeDC.h"
#include "Lcircuit.h"

void recherche_circuit_sommet(Sommet *s, Sommet *init, LDC *L){

    if(!s) return;
    
    LDCInsererEnFin(L, s->i, s->j);
    
    if(s->visit==0 && s==init) {
        //printf("(%d,%d) #\n",s->i, s->j);
        return;
    }
    
    //printf("(%d,%d) ",s->i, s->j);
    s->visit=0;
        
    if(s->Lsucc){
        Arc *cour = s->Lsucc;
        while(cour && cour->succ && cour->succ->visit!=-1 && cour->succ!=init)
            cour=cour->suiv;
        if(cour && cour->succ){
            //printf(" -> ");
            recherche_circuit_sommet(cour->succ, init, L);
        }       
    }
}

Lcircuit *Graphe_Rech_Circuit(Graphe *h){
    int n, m;
    
    Lcircuit *Lcirc = malloc(sizeof(Lcircuit));
    LcircuitInitialise(Lcirc);
    
    if(!h){
        printf("Pas de graphe");
        return NULL;    
    }
    
    for( m=0; m < h->m; m++)
        for( n=0; n < h->n; n++)
            
            if(h->Tsom[m][n]){
                if(h->Tsom[m][n]->visit==-1){
                    LDC *L = malloc(sizeof(LDC));
                    LDCInitialise(L);
                    recherche_circuit_sommet(h->Tsom[m][n],h->Tsom[m][n], L);   
                    Lcirc->nb_circuit++;
                    LcircuitInsererEnFin(Lcirc, L);  
                    //printf("\n");
                }                        
            }
           
      

    //printf("\n");   
    return Lcirc;
}


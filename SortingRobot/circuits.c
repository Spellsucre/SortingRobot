#include <stdio.h>
#include <stdlib.h>

#include "circuits.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void recherche_circuit_sommet(Sommet *s, Sommet *init, LDC *L){
    if (!s || !init) return;
    
    LDCInsererEnFin(L, s->i, s->j);
    
    if (s->visit==0 && s==init) return;
    
    //LDCInsererEnFin(L, s->i, s->j);
    
    s->visit = 0;
        
    if (s->Lsucc){
        Arc *cour = s->Lsucc;
        while (cour && cour->succ && cour->succ->visit!=-1 && cour->succ!=init)
            cour = cour->suiv;
        if (cour)	//&& cour->succ
            recherche_circuit_sommet(cour->succ, init, L);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Lcircuit *Graphe_Rech_Circuit(Graphe *h){
    int m, n;
    
    Lcircuit *Lcirc = malloc( sizeof(Lcircuit) );
    if (!Lcirc){ printf("pb malloc\n"); return NULL; }
    LcircuitInitialise(Lcirc);
    
    if (!h){ printf("Pas de graphe\n"); return NULL; }
    
    for( m=0; m< h->m; m++){
        for( n=0; n< h->n; n++){
			
            if (h->Tsom[m][n] && h->Tsom[m][n]->visit==-1){
                LDC *L = malloc( sizeof(LDC) );
                if (!L){ printf("pb malloc\n"); return NULL; }
                LDCInitialise(L);
                recherche_circuit_sommet(h->Tsom[m][n], h->Tsom[m][n], L);   
                //Lcirc->nb_circuit++;	//voir le code de LcircuitInsererEnFin()
                LcircuitInsererEnFin(Lcirc, L);  
            }
                                
    	}
    }
    
    CalculJminJmax(Lcirc);
    
    return Lcirc;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CalculJminJmax(Lcircuit *LC){
	int jmax;
	Cell_circuit *cour = LC->premier;
	CelluleLDC *tmp;
	
	while (cour){	//parcourt de la liste de circuits
		tmp = cour->L.premier;	//tmp := [premiere] case appartenant au circuit
		
		//jmin
		cour->jmin = tmp->j;	//toujours la premiere case
		
		//jmax
		jmax = cour->jmin;
		while (tmp){	//parcourt du circuit
			jmax = tmp->j>jmax ? tmp->j : jmax;
			tmp = tmp->suiv;
		}
		cour->jmax = jmax;
		
		cour = cour->suiv;
	}
}



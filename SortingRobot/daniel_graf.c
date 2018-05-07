#include <stdio.h>
#include <stdlib.h>

#include "Graphe.h"
#include "circuits.h"
#include "daniel_graf.h"
#include "Solution.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Solution *daniel_graf(Grille *G){

	if (!G) { printf("Grille non initialisée\n"); return NULL; }
	if (G->m != 1) { printf("Il faut m=1\n"); return NULL; }
	if (G->m*G->n != G->nbcoul) { printf("Il faut m*n=nbcoul\n"); return NULL; }
	
	Graphe *H = malloc( sizeof(Graphe) );
	if (!H){ printf("Probleme d'allocation memoire\n"); return NULL; }
	Graphe_creation(G, H);
	
	int i, Jdroite, JdroiteSav, Drapeau;
	
	Lcircuit *LC = Graphe_Rech_Circuit(H);
	
	Solution *S = malloc( sizeof(Solution) );
	if (S==NULL){
		printf("Probleme d'allocation memoire\n");
		return NULL;
	}
	Solution_init(S);
	
	Cell_char **Tref = malloc( sizeof(Cell_char*) * G->n );
	if (!Tref){	printf("Probleme d'allocation memoire\n"); return NULL;	}
	for (i=0; i<G->n; i++){
		Tref[i] = NULL;
	}
	
	Jdroite = 0;
	
	Cell_circuit *C = LC->premier;
	while (C){
		
		if ( Tref[C->jmin] == NULL ){
			Drapeau = 1;
			JdroiteSav = Jdroite;
			plus_court_chemin_apres_c(S, Tref[Jdroite], Jdroite, C->jmin, Tref);
            ajout_action_apres_c( S, Tref[Jdroite], Jdroite, 'S', Tref);
			Jdroite = C->jmin;
		}
		
		ajout_circuit_dans_solution(&(C->L), S, Tref[C->jmin], Tref, &Jdroite);
		
		if (Drapeau){
			Drapeau = 0;
			plus_court_chemin_apres_c(S, Tref[C->jmin], C->jmin, JdroiteSav, Tref);
		}
				
		C = C->suiv;
	}
	
	return S;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Cell_char *ajout_action_apres_c(Solution *S, Cell_char *c, int j, char a, Cell_char **Tref){
	
	Cell_char *nouv = malloc( sizeof(Cell_char) );
	if (nouv==NULL){ printf("Probleme d'allocation memoire\n");	return NULL; }
	nouv->a = a;
	nouv->suiv = NULL;
	
	if ( c != NULL){
        nouv->suiv=c->suiv;
        c->suiv=nouv;
	} else {
	    nouv->suiv=S->prem;
	    S->prem=nouv;
	}
	
	if (a!='S'){
	    S->cptr_pas++;
	    Tref[j] = nouv;
	}	
	return nouv;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cell_char *plus_court_chemin_apres_c(Solution *S, Cell_char *c, int j, int l, Cell_char **Tref){
    
    Cell_char *lastAct;
    char action = 'S';
    int i, k;
    
    if ( j-l < 0 ){
        action = 'R';
    }
    else if ( j-l > 0){
        action = 'L';
    } 
    
    for ( i = 0 ; i < (j-l<0?-(j-l):j-l) ; i++ ){
        lastAct = ajout_action_apres_c( S, c, j+i, action, Tref);
    }
    
    return lastAct;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ajout_circuit_dans_solution(LDC *L, Solution *S, Cell_char *c, Cell_char **Tref, int *Jdroite){
    
    CelluleLDC *cour;
    
    if(L != NULL){
    
        cour = L->premier;
        
        while ( cour->suiv ){
            plus_court_chemin_apres_c(S, c, cour->j, cour->suiv->j, Tref);
            ajout_action_apres_c( S, c, cour->j, 'S', Tref); 
            if(cour->suiv->j > *Jdroite)
                *Jdroite = cour->suiv->j;
                
            cour = cour->suiv;
        }
        
    }
}


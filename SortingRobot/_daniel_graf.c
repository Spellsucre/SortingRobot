#include <stdio.h>
#include <stdlib.h>

#include "Graphe.h"
#include "circuits.h"
#include "daniel_graf.h"
#include "Solution.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Solution *daniel_graf(Grille *G){
	if (!G) { printf("Grille non initialisée\n"); return NULL; }

	// tests de conditions sur la grille
	if (G->m != 1) { printf("Il faut m=1\n"); return NULL; }
	if (G->m*G->n != G->nbcoul) { printf("Il faut m*n=nbcoul\n"); return NULL; }
	
	
	int i, Jdroite, JdroiteSav, Drapeau, cpt=0;
	
	
	// création du graphe H
	Graphe *H = malloc( sizeof(Graphe) );
	if (!H){ printf("Probleme d'allocation memoire\n"); return NULL; }
	Graphe_creation(G, H);
	
	// création de LC, la liste descircuits de H
	// avec calcul de jmin et jmax pour chaque circuit
	// LC rangée par jmin croissants
	Lcircuit *LC = Graphe_Rech_Circuit(H);
	
	// création d'une solution S vide
	Solution *S = malloc( sizeof(Solution) );
	if (S==NULL){
		printf("Probleme d'allocation memoire\n");
		return NULL;
	}
	Solution_init(S);
	
	// création de Tref, tab de pointeurs de n cases NULL
	Cell_char **Tref = malloc( sizeof(Cell_char*) * G->n );
	if (!Tref){	printf("Probleme d'allocation memoire\n"); return NULL;	}
	for (i=0; i<G->n; i++) Tref[i]=NULL;
	
	// indice de la case la plus à droite visitée par le robot
	Jdroite = 0;
	
	Cell_circuit *C = LC->premier;
	while (C){	//parcours de la liste de circuits de LC (jmin croissants)
		
		printf("cpt = %d\n", cpt++);
		
		if ( Tref[C->jmin] == NULL ){
			printf("\n=================== dbg_1 =================== \n");
			Drapeau = 1;
			JdroiteSav = Jdroite;
			// insertion de 'R' dans S pemettant d'aller de Jdroite à C->jmin à la suite de Tref[Jdroite]
			pluscourtchemin_apres_c(S, Tref[Jdroite], Jdroite, C->jmin, Tref);
			Jdroite = C->jmin;
		}
		
		printf("\n=================== dbg_2 =================== \n");
		// ajout seq deplacements de C dans S à la suite de Tref[jmin]
		ajout_circuit_dans_solution(C, S, Tref[C->jmin], Tref, &Jdroite);

		

		if (Drapeau){
			printf("\n=================== dbg_3 =================== \n");
			Drapeau = 0;
			// insersion de 'L' dans S pemettant d'aller de C->jmin à JdroiteSav à la suite de Tref[C->jmin], après l'action 'S'
			pluscourtchemin_apres_c(S, Tref[C->jmin], C->jmin, JdroiteSav, Tref);
		}
		
		Affiche(S);
		printf("\n");
				
		C = C->suiv;
	}
	
	return S;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/**
 *	insère l'action a dans S 
 *	si c != NULL: 
 *		après le pointeur c
 *	sinon 
 *		en tête de S
 *	retourne le pointeur sur la nouvelle cellule inserée dans S
 *	maj de Tref
*/
Cell_char *ajout_action_apres_c(Solution *S, Cell_char *c, int j, char a, Cell_char **Tref){
	printf("Solution avant insersion:\n"); Affiche(S);
	
	Cell_char *nouv = malloc( sizeof(Cell_char) );
	if (nouv==NULL){ printf("Probleme d'allocation memoire\n");	return NULL; }
	nouv->a = a;
	nouv->suiv = NULL;
	
	if ( c != NULL){
		printf("--- après le pointeur c ---\n");
		/*
		nouv->suiv = c->suiv;
		c->suiv = nouv;
		S->cptr_pas++;
		if (c == S->dern)
			S->dern = nouv;
		*/
		c->suiv = nouv;
		
		//S->dern->suiv=nouv;
		//S->dern=nouv;
	} else {
		printf("--- en tête de S ---\n");
		//c = nouv;
		//nouv->suiv = S->prem;
		//S->prem = nouv;
		
		if (S->prem==NULL){  // Si Liste vide
			S->prem=nouv;
			S->dern=nouv;
		} else {
			S->dern->suiv=nouv;
			S->dern=nouv;
		}
	}
	if (a!='S') S->cptr_pas++;

	
	
	Tref[j] = nouv;
	
	printf("Solution après insersion:\n"); Affiche(S); printf("\n");
	
	return nouv;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cell_char *pluscourtchemin_apres_c(Solution *S, Cell_char *c, int j, int l, Cell_char **Tref){
	//printf("Solution avant insersion:\n"); Affiche(S);
	
	char a;
	int i;
	Cell_char *LastAct;
	if (j-l < 0){
		a='R';
	} else if (j-l > 0){
		a='L';
	}
	
	if (a=='L') {
		LastAct = ajout_action_apres_c(S, c, j, 'S', Tref);
		printf("____ajout S (L)\n");	
	}
	
	for (i=0; i<abs(j-l); i++){
		LastAct = ajout_action_apres_c(S, c, j, a, Tref);
	}
	
	if (a=='R' || i==0) {
		LastAct = ajout_action_apres_c(S, c, j, 'S', Tref);
		printf("____ajout S (R)\n");	
	}
	
	//printf("Solution après insersion:\n"); Affiche(S); printf("\n");
	
	return LastAct;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ajout_circuit_dans_solution(Cell_circuit *C, Solution *S, Cell_char *c, Cell_char **Tref, int *Jdroite){
	
	CelluleLDC *cour = C->L.premier;	//premier elem de L
	
	while (cour->suiv){
		pluscourtchemin_apres_c(S, c, cour->j, cour->suiv->j, Tref);
		//ajout_action_apres_c(S, c, cour->suiv->j, 'S', Tref);
		
		cour = cour->suiv;
	}
	
	//maj de Jdroite
	if ( C->jmax > *Jdroite ){
		*Jdroite = C->jmax;
	}
	
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void algorithme_circuit_CasLigne1x1(Grille *G, Solution *S){
	
}


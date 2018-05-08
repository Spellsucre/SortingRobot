#include <stdio.h>
#include <stdlib.h>

#include "Graphe.h"
#include "circuits.h"
#include "daniel_graf.h"
#include "Solution.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ajoute a à la Solution S à la suite de c si non nul, en tete de S sinon
// maj de Tref selon j
Cell_char *ajout_action_apres_c(Solution *S, Cell_char *c,
			int j, char a, Cell_char **Tref){
		
	Cell_char *nouv = malloc( sizeof(Cell_char) );
	if (nouv==NULL){ printf("Probleme d'allocation memoire\n");	return NULL; }
	nouv->a = a;
	nouv->suiv = NULL;
	
	if ( c != NULL){
		if (c->suiv && c->suiv->a=='S') c=c->suiv;
		
		nouv->suiv = c->suiv;
		c->suiv = nouv;
		
		if (a=='S' && nouv->suiv) Tref[j] = nouv;
		
	} else {
		S->prem = nouv;
	} 

	if (a!='S'){
		S->cptr_pas++;
		Tref[j] = nouv;
	}
	
	return nouv;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cell_char *pluscourtchemin_apres_c(Solution *S, Cell_char *c, 
			int j, int l, Cell_char **Tref){
			
	int i;
	Cell_char *LastAct = c;

	if (j<l){
		for (i=j; i<l; i++){
			LastAct = ajout_action_apres_c(S, LastAct, i+1, 'R', Tref);
		}
		
	} else if (j>l){
		for (i=j; i>l; i--){
			LastAct = ajout_action_apres_c(S, LastAct, i-1, 'L', Tref);
		}
	} 

	return LastAct;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ajout_circuit_dans_solution(Cell_circuit *C, Solution *S, Cell_char *c,
			Cell_char **Tref, int *Jdroite){
			
	CelluleLDC *cour = C->L.premier;	//premier elem de L
	Cell_char *LastAct = c;
	
	LastAct = ajout_action_apres_c(S, LastAct, cour->j, 'S', Tref);
	
	while (cour->suiv){
		LastAct = pluscourtchemin_apres_c(S, LastAct, cour->j, cour->suiv->j, Tref);
		ajout_action_apres_c(S, LastAct, cour->suiv->j, 'S', Tref);
		cour = cour->suiv;
	}
	
	//maj de Jdroite
	if ( C->jmax > *Jdroite ){
		*Jdroite = C->jmax;
	}
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// prend en arguments une Grille vecteur (une case par couleur) et une Solution
// maj de S selon l'algo de Daniel Graf appliqué à la grille G
void algorithme_circuit_CasLigne1x1(Grille *G, Solution *S){
	if (!G) { printf("Grille non initialisée\n"); return; }
	if (!S) { printf("Solution non initialisée\n"); return; }

	// tests de conditions sur la grille
	if (G->m != 1) { printf("Il faut m=1\n"); return; }
	if (G->m*G->n != G->nbcoul) { printf("Il faut m*n=nbcoul\n"); return; }
	
	
	int i, Jdroite=0, JdroiteSav, Drapeau;
	
	// création du graphe H
	Graphe *H = malloc( sizeof(Graphe) );
	if (!H){ printf("Probleme d'allocation memoire\n"); return; }
	Graphe_creation(G, H);
	
	// création de LC, la liste des circuits de H
	// avec calcul de jmin et jmax pour chaque circuit
	// LC rangée par jmin croissants
	Lcircuit *LC = Graphe_Rech_Circuit(H);
	
	// création de Tref, tab de pointeurs de n cases NULL
	Cell_char **Tref = malloc( sizeof(Cell_char*) * G->n );
	if (!Tref){	printf("Probleme d'allocation memoire\n"); return;	}
	for (i=0; i<G->n; i++) Tref[i] = NULL;	
	
	Cell_circuit *C = LC->premier;
	while (C){	//parcours de la liste de circuits de LC (jmin croissants)
		
		if ( Tref[C->jmin] == NULL ){
			Drapeau = 1;
			JdroiteSav = Jdroite;
			// insertion de 'R' dans S pemettant d'aller de Jdroite à C->jmin
			// à la suite de Tref[Jdroite]
			pluscourtchemin_apres_c(S, Tref[Jdroite], Jdroite, C->jmin, Tref);
			Jdroite = C->jmin;
		}
		
		// ajout seq deplacements de C dans S à la suite de Tref[C->jmin]
		ajout_circuit_dans_solution(C, S, Tref[C->jmin], Tref, &Jdroite);

		if (Drapeau){
			Drapeau = 0;
			// insertion de 'L' dans S pemettant d'aller de C->jmin à JdroiteSav
			// à la suite de Tref[C->jmin], après l'action 'S'
			pluscourtchemin_apres_c(S, Tref[C->jmin], C->jmin, JdroiteSav, Tref);
		}
			
		C = C->suiv;
	}
	
	printf("Calcul de la Solution selon l'algo de Daniel Graf avec réussi!\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// affiche Tref (debug)
void afficheTref(Cell_char **Tref, int n){
	int i;
	Cell_char *cell;	
	
	printf("---- Tref ----\n");
	for (i=0; i<n; i++){
		cell = Tref[i];
		printf("%d: ", i);
		while (cell){
			printf("%c ", cell->a);
			cell = cell->suiv;	
		}
		printf("\n");
	}
	printf("\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// affiche la liste chainee d'éléments de Solution pointée par c
void afficheCellChar(Cell_char *c, char *label){
	Cell_char *tmp = c;
	printf("%s:    ", label);
	while (tmp){
		printf("%c -> ", tmp->a);
		tmp = tmp->suiv;
	}
	printf("\n");
}



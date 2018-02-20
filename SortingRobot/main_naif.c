#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "exo1.h"
#include "Grille.h"
#include "Solution.h"

int main(){
    
    Grille G;
	Solution S;
	Solution_init(&S);
	
	G.m=4;
	G.n=4;
	G.nbcoul=4;
	int graine=1;
	
	
	Grille_allocation(&G);
	Gene_Grille(&G, graine);
	
	algorithme_naif( &G, &S);
	
	if (G.cptr_noire==G.n*G.m){
      printf("\nL'algorithme a gagne en %d pas\n",S.cptr_pas);
      printf("\nEcriture de la solution sur disque\n\n");
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
    }
    Affiche(&S);
    
    int i;
    for (i=0;i<G.m;i++)
        free(G.T[i]);
    free(G.T);
    
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "exo1.h"
#include "Grille.h"
#include "Solution.h"

int main(int argc, char** argv){
    
	Grille G;
	Solution S;
	Solution_init(&S);
	int graine;

    if(argc!=5){
        printf("usage: %s <nb_lignes nb_colonnes nb_couleur graine>\n",argv[0]);
        return 1;
    }

    G.m=atoi(argv[1]);
    G.n=atoi(argv[2]);
    
    if (G.m>G.n){
        printf("Il doit y avoir plus de colonnes que de lignes.\n");
        exit(1);
    }
      
    G.nbcoul=atoi(argv[3]);  
    if (G.nbcoul>G.m*G.n){
        printf("Il ne doit pas y avoir plus de couleurs que de cases.\n");
        exit(1);
    }
  
    graine=atoi(argv[4]);

	Grille_allocation(&G);
	Gene_Grille(&G, graine);

	algorithme_naif( &G, &S);

	if (G.cptr_noire==G.n*G.m){
		printf("\nL'algorithme a gagne en %d pas\n",S.cptr_pas);
		printf("\nEcriture de la solution sur disque\n\n");
		Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
	}else{
		printf("\nAlogo NOK\n\n");
	}
	Affiche(&S);

	int i;
	for (i=0;i<G.m;i++) free(G.T[i]);
	free(G.T);

	return 0;
}

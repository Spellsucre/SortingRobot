#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "exo1.h"
#include "Grille.h"
#include "Solution.h"

int main(int argc, char** argv){
    
	Grille G;
	Solution S;
	int graine, version;
	clock_t t0, t1;
	double d1;
	
	char *ModeRecherche[] = { "tampon", "recherche_naive", "recherche_circulaire"};

	
	Solution_init(&S);
	
    if(argc!=6){
        printf("usage: %s <nb_lignes nb_colonnes nb_couleur graine num_version_recherche>\n", argv[0]);
        return 1;
    }

    G.m=atoi(argv[1]); G.n=atoi(argv[2]);
    
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
    
    version=atoi(argv[5]);	//version de fonction de recherche de case lpp


	Grille_allocation(&G);
	Gene_Grille(&G, graine);

	switch (version){
		case 1:
			t0 = clock();
			algorithme_naif(&G, &S);
			t1 = clock();
			d1 = ((double)(t1-t0))/CLOCKS_PER_SEC;
			break;
		
		case 2:
			t0 = clock();
			algorithme_circulaire(&G, &S);
			t1 = clock();
			d1 = ((double)(t1-t0))/CLOCKS_PER_SEC;
			break;
			
		default:
			printf("Versions de fonction de recherche de case lpp possibles: [1, 2]\n");
			return 1;
	}
	
	printf("\nTemps de recherche avec la méthode %s: %f\n", ModeRecherche[version], d1);
	
	if (G.cptr_noire==G.n*G.m){
		printf("\nL'algorithme a gagne en %d pas\n", S.cptr_pas);
		printf("\nEcriture de la solution sur disque\n");
		Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
	}else{
		printf("\nAlgo version %d NOK\n\n", version);
	}
	//Affiche(&S);

	int i;
	for (i=0;i<G.m;i++) free(G.T[i]);
	free(G.T);

	return 0;
}

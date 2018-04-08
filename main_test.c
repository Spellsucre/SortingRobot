#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fonctions_base.h"
#include "methode_naive.h"
#include "methode_circulaire.h"
#include "methode_LDC.h"
#include "methode_AVL.h"

int main(int argc, char** argv){
    
	Grille G;
	Solution S;
	int graine, version;
	clock_t t0, t1;
	double d1;
	char str[256];
	
	char *modeRecherche[] = { "tampon",
							"recherche_naive",
							"recherche_circulaire",
							"recherche_LDC",
							"recherche_AVL"};

	
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
	
		case 3:
			t0 = clock();
			algorithme_parcouleur(&G, &S);
			t1 = clock();
			d1 = ((double)(t1-t0))/CLOCKS_PER_SEC;
			break;
		
		case 4:
			t0 = clock();
			algorithme_AVL(&G, &S);
			t1 = clock();
			d1 = ((double)(t1-t0))/CLOCKS_PER_SEC;
			break;	
			
		default:
			printf("Versions de fonction de recherche de case lpp possibles: [1, 2, 3, 4]\n");
			return 1;
	}
	
	printf("\nTemps de recherche avec la méthode %s: %f\n", modeRecherche[version], d1);
	
	if (G.cptr_noire==G.n*G.m){
		printf("\nL'algorithme a gagne en %d pas\n", S.cptr_pas);
		printf("\nEcriture de la solution sur disque\n");
		Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
		
		sprintf(str, "mv Robot_%d_%d_%d_%d.sol Robot_%d_%d_%d_%d_%d.sol ",
								G.m, G.n, G.nbcoul, graine,
								G.m, G.n, G.nbcoul, graine, version==4?4:0);
		system(str);
		
	}else{
		printf("\nAlgo version %d NOK\n\n", version);
	}
	//Affiche(&S);
	freeGrille(&G);
	freeSol(&S);

	return 0;
}

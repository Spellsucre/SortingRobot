#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions_base.h"
#include "Grille.h"
#include "Solution.h"
#include "Graphe.h"
#include "ListeDC.h"
#include "circuits.h"
#include "Lcircuit.h"
#include "daniel_graf.h"


int main (int argc, char *argv[]){
	char commande[256];
	
	Grille G;
	Solution *S= malloc( sizeof(Solution) );
	if (S==NULL){
		printf("Probleme d'allocation memoire\n");
		return 1;
	}
	
	int graine;
	
	Solution_init(S);
	
    if(argc!=5){
        printf("usage: %s <nb_lignes nb_colonnes nb_couleur graine>\n", argv[0]);
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
    
	Grille_allocation(&G);
	Gene_Grille(&G, graine);
	
	
	S = daniel_graf( &G );
	Affiche(S);
	
	// test de validité de la solution
	Ecriture_Disque(G.m, G.n, G.nbcoul, graine, S);
	sprintf(commande, "./Checker_SortingRobot Robot_1_%d_%d_%d.sol 0 1", G.n, G.nbcoul, graine);
	system(commande);	
	sprintf(commande, "rm Robot_1_%d_%d_%d.sol", G.n, G.nbcoul, graine);
	system(commande);


	freeGrille(&G);
	freeSol(S);
	
	return 0;
}

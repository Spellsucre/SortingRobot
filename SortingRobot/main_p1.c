#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fonctions_base.h"
#include "methode_naive.h"
#include "methode_circulaire.h"
#include "methode_LDC.h"
#include "methode_AVL.h"

//codes couleur shell
	
#define CW "\x1b[0m"
#define CR "\x1b[31m"
#define CG "\x1b[32m"
#define CB "\x1b[34m"
#define CY "\x1b[33m"

void menu(){
	printf(CY"\n===============SORTING ROBOT===============\n");
	printf(CG"0: Entrer une nouvelle grille\n");
	printf(CY"- - - - -\n");
	printf(CB"1: Naif\n");
	printf("2: Circulaire\n");
	printf("3: LDC\n");
	printf("4: AVL\n");
	printf(CY"- - - - -\n");
	printf(CR"5: Quitter\n");
	printf(CY"===========================================\n\n"CW);
}


void siSucces(Grille G, Solution S, int choix, int graine, double d){
	char str[256];
	char *modeRecherche[] = { "tampon",
							"recherche_naive",
							"recherche_circulaire",
							"recherche_LDC",
							"recherche_AVL"};
	
	Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);
	printf("Temps de recherche avec la méthode %s: %f\n",
									modeRecherche[choix], d);
	printf("L'algorithme a gagné en %d pas\n", S.cptr_pas);
	
	sprintf(str, "mv Robot_%d_%d_%d_%d.sol Robot_%d_%d_%d_%d_%d.sol ",
				G.m, G.n, G.nbcoul, graine,
				G.m, G.n, G.nbcoul, graine, choix);
	system(str);
}


int main (){
	Grille G; Solution S;
	int m, n, nbcoul, graine, choix, grille=0;
	clock_t t0, t1;	double d;	

	do {
		menu();	
		scanf(" %d", &choix);
		if (choix<0 || choix>5) printf("%d: Commande inconnue\n", choix);
		
		switch(choix){
			
			// parametrage de la grille
			case 0:
				printf("Entrer une nouvelle grille...\n");
				printf("m : ");	scanf(" %d", &m);
				printf("n : ");	scanf(" %d", &n);
				if (m>n){
					printf("Il doit y avoir plus de colonnes que de lignes.\n");
					break;
				}
				printf("nbcoul : "); scanf(" %d", &nbcoul);
				if (nbcoul>m*n){
					printf("Il ne doit pas y avoir plus de couleurs que de cases.\n");
					break;
				}
				printf("graine : "); scanf(" %d", &graine);
				printf("Parametres sauvegardés, choisir une méthode de résolution.");
				grille = 1;
				break;
			
			// methode naive
			case 1:
				if (!grille){
					printf("ERREUR: Il faut d'abord indiquer les parametres de la grille\n");
					break;
				}
				Solution_init(&S);
				G.m=m; G.n=n; G.nbcoul=nbcoul;
				Grille_allocation(&G); Gene_Grille(&G, graine);
				t0 = clock();
				algorithme_naif(&G, &S);
				t1 = clock();
				d = ((double)(t1-t0))/CLOCKS_PER_SEC;
				if (G.cptr_noire==G.n*G.m) siSucces(G, S, choix, graine, d);
				else printf("Echec du calcul de la solution :(\n");
				freeGrille(&G);	//freeSol(&S);
				break;
			
			// methode circulaire
			case 2:
				if (!grille){
					printf("ERREUR: Il faut d'abord indiquer les parametres de la grille\n");
					break;
				}
				Solution_init(&S);
				G.m=m; G.n=n; G.nbcoul=nbcoul;
				Grille_allocation(&G); Gene_Grille(&G, graine);
				t0 = clock();
				algorithme_circulaire(&G, &S);
				t1 = clock();
				d = ((double)(t1-t0))/CLOCKS_PER_SEC;
				if (G.cptr_noire==G.n*G.m) siSucces(G, S, choix, graine, d);
				else printf("Echec du calcul de la solution :(\n");
				freeGrille(&G);	//freeSol(&S);
				break;
			
			// methode LDC
			case 3:
				if (!grille){
					printf("ERREUR: Il faut d'abord indiquer les parametres de la grille\n");
					break;
				}
				Solution_init(&S);
				G.m=m; G.n=n; G.nbcoul=nbcoul;
				Grille_allocation(&G); Gene_Grille(&G, graine);
				t0 = clock();
				algorithme_parcouleur(&G, &S);
				t1 = clock();
				d = ((double)(t1-t0))/CLOCKS_PER_SEC;
				if (G.cptr_noire==G.n*G.m) siSucces(G, S, choix, graine, d);
				else printf("Echec du calcul de la solution :(\n");
				freeGrille(&G);	//freeSol(&S);
				break;
			
			// methode AVL
			case 4:
				if (!grille){
					printf("ERREUR: Il faut d'abord indiquer les parametres de la grille\n");
					break;
				}
				Solution_init(&S);
				G.m=m; G.n=n; G.nbcoul=nbcoul;
				Grille_allocation(&G); Gene_Grille(&G, graine);
				t0 = clock();
				algorithme_AVL(&G, &S);
				t1 = clock();
				d = ((double)(t1-t0))/CLOCKS_PER_SEC;
				if (G.cptr_noire==G.n*G.m) siSucces(G, S, choix, graine, d);
				else printf("Echec du calcul de la solution :(\n");
				freeGrille(&G);	//freeSol(&S);
				break;
			
			// fin prg
			case 5:
				system("rm *.sol");
				return 0;
		}
	
	} while (choix != 5);
	return 0;
}



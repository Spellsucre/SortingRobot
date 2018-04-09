#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fonctions_base.h"
#include "methode_naive.h"
#include "methode_circulaire.h"
#include "methode_LDC.h"
#include "methode_AVL.h"

FILE *f;
clock_t t0, t1;
double d;
Grille G;
Solution S;
int tailleGrille;

void methode_naive(){
	d=0.0;
	f = fopen("courbes/temps_naif.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille\n#nbCases, d (naif)\n");
	
	for (tailleGrille=4; (int)d < 40; tailleGrille+=20){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= tailleGrille;
		Grille_allocation(&G);
		Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_naif(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille*tailleGrille, d);
		printf("recherche naive | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
		//freeSol(&S);
	}
	
	fclose(f);	
}

void methode_circulaire(){
	d=0.0;
	f = fopen("courbes/temps_circ_.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille\n#nbCases, d (circ)\n");
	
	for (tailleGrille=4; (int)d < 40; tailleGrille+=30){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = tailleGrille;
		Grille_allocation(&G);
		Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_circulaire(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille*tailleGrille, d);
		printf("recherche circulaire | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
		//freeSol(&S);
	}
	
	fclose(f);
}

void methode_circulaire_2(){
	d=0.0;
	f = fopen("courbes/temps_circ_2.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille*3\n#nbCases, d (circ)\n");
	
	for (tailleGrille=4; (int)d < 40; tailleGrille+=5){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= tailleGrille*3;
		Grille_allocation(&G);
		Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_circulaire(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille*tailleGrille, d);
		printf("c | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
		//freeSol(&S);
	}
	
	fclose(f);
}

void methode_circulaire_3(){
	d=0.0;
	f = fopen("courbes/temps_circ_3.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille*0.25\n#nbCases, d (circ)\n");
	
	for (tailleGrille=4; (int)d < 40; tailleGrille+=5){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= (int) (tailleGrille*0.25);
		Grille_allocation(&G);
		Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_circulaire(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille*tailleGrille, d);
		printf("c | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
		//freeSol(&S);
	}
	
	fclose(f);
}

void methode_circulaire_4(){
	d=0.0;
	f = fopen("courbes/temps_circ_4.dat", "w");
	fprintf(f, "#nbCoul=6\n#nbCases, d (circ)\n");
	
	for (tailleGrille=4; (int)d < 40; tailleGrille+=5){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= 6;
		Grille_allocation(&G);
		Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_circulaire(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille*tailleGrille, d);
		printf("c | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
		//freeSol(&S);
	}
	
	fclose(f);
}

void methode_LDC(){
	d=0.0;
	f = fopen("courbes/temps_LDC_test.dat", "w");
	fprintf(f, "#nbCoul=N=M\n#nbCases, d (LDC)\n");
	
	for (tailleGrille=4; (int)d < 1; tailleGrille+=100){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= 10;
		Grille_allocation(&G);
		Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_parcouleur(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille*tailleGrille, d);
		printf("recherche LDC | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
		
		
		//sfreeSol(&S);
	}
	
	fclose(f);
}

void methode_AVL(){
	d=0.0;
	f = fopen("courbes/temps_AVL.dat", "w");
	fprintf(f, "#nbCoul=N=M\n#nbCases, d (AVL)\n");
	
	
	for (tailleGrille=4; (int)d < 40; tailleGrille+=100){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= 10;
		Grille_allocation(&G);
		Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_AVL(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille*tailleGrille, d);
		printf("recherche AVL | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		//freeGrille(&G);
		
		
		//sfreeSol(&S);
	}
	
	
	
		
		
	fclose(f);
}


int main(){
	//methode_naive();
	//methode_circulaire();
	//methode_circulaire_2();
	//methode_circulaire_3();
	//methode_circulaire_4();
	methode_LDC();
	methode_AVL();
	
	return 0;
}

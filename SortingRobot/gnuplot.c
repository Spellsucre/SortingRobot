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
	fprintf(f, "#nbCoul=N=M\n#tailleGrille, d (naif)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=8){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= tailleGrille;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_naif(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche naive | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);	
}

void methode_circulaire(){
	d=0.0;
	f = fopen("courbes/temps_circ.dat", "w");
	fprintf(f, "#nbCoul=N=M\n#tailleGrille, d (circ)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=10){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = tailleGrille;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_circulaire(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche circulaire | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);
}

void methode_LDC(){
	d=0.0;
	f = fopen("courbes/temps_LDC.dat", "w");
	fprintf(f, "#nbCoul=N=M\n#tailleGrille, d (LDC)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=70){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = tailleGrille;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_parcouleur(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche LDC | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);
}

void methode_AVL(){
	d=0.0;
	f = fopen("courbes/temps_AVL.dat", "w");
	fprintf(f, "#nbCoul=N=M\n#tailleGrille, d (AVL)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=60){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = tailleGrille;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_AVL(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche AVL | tailleGrille = %d, d = %f\n", tailleGrille, d);
	}
	fclose(f);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void methode_naive_2(){
	d=0.0;
	f = fopen("courbes/temps_naif_2.dat", "w");
	fprintf(f, "#nbCoul=10\n#tailleGrille, d (naif)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=8){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= 10;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_naif(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche naive 2 | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);	
}

void methode_circulaire_2(){
	d=0.0;
	f = fopen("courbes/temps_circ_2.dat", "w");
	fprintf(f, "#nbCoul=10\n#tailleGrille, d (circ)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=10){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = 10;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_circulaire(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche circulaire 2 | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);
}

void methode_LDC_2(){
	d=0.0;
	f = fopen("courbes/temps_LDC_2.dat", "w");
	fprintf(f, "#nbCoul=10\n#tailleGrille, d (LDC)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=21){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = 10;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_parcouleur(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche LDC 2 | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);
}

void methode_AVL_2(){
	d=0.0;
	f = fopen("courbes/temps_AVL_2.dat", "w");
	fprintf(f, "#nbCoul=10\n#tailleGrille, d (AVL)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=39){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = 10;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_AVL(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche AVL 2 | tailleGrille = %d, d = %f\n", tailleGrille, d);
	}
	fclose(f);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void methode_naive_3(){
	d=0.0;
	f = fopen("courbes/temps_naif_3.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille*tailleGrille\n#tailleGrille, d (naif)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=8){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul= 10;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_naif(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche naive 3 | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);	
}

void methode_circulaire_3(){
	d=0.0;
	f = fopen("courbes/temps_circ_3.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille*tailleGrille\n#tailleGrille, d (circ)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=10){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = tailleGrille*tailleGrille;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_circulaire(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche circulaire 3 | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);
}

void methode_LDC_3(){
	d=0.0;
	f = fopen("courbes/temps_LDC_3.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille*tailleGrille\n#tailleGrille, d (LDC)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=300){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = tailleGrille*tailleGrille;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_parcouleur(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche LDC 3 | tailleGrille = %d, d = %f\n", tailleGrille, d);
		
		freeGrille(&G);
	}
	fclose(f);
}

void methode_AVL_3(){
	d=0.0;
	f = fopen("courbes/temps_AVL_3.dat", "w");
	fprintf(f, "#nbCoul=tailleGrille*tailleGrille\n#tailleGrille, d (AVL)\n");
	
	for (tailleGrille=4; (int)d < 35; tailleGrille+=300){
		Solution_init(&S);
		G.m=tailleGrille; G.n=tailleGrille;
		G.nbcoul = tailleGrille*tailleGrille;
		Grille_allocation(&G); Gene_Grille(&G, 1);
	
		t0 = clock();
		algorithme_AVL(&G, &S);
		t1 = clock();
		d = ((double)(t1-t0))/CLOCKS_PER_SEC;
		
		fprintf(f, "%d\t%f\n", tailleGrille, d);
		printf("recherche AVL 3 | tailleGrille = %d, d = %f\n", tailleGrille, d);
	}
	fclose(f);
}


//==============================================================================
int main(){
	//methode_naive();
	//methode_circulaire();
	//methode_LDC();
	//methode_AVL();
	
	//methode_naive_2();
	//methode_circulaire_2();
	//methode_LDC_2();
	//methode_AVL_2();
	
	//methode_naive_3();
	//methode_circulaire_3();
	//methode_LDC_3();
	methode_AVL_3();
	
	return 0;
}



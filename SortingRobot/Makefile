CFLAGS=-Wall -g

all: main_graphe main_test main_p1 test_AVL gnuplot clean2 #Game_SortingRobot Checker_SortingRobot 

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

Solution.o: Solution.c Solution.h entree_sortie.h
	gcc -c Solution.c

Grille.o: Grille.c Grille.h Solution.h
	gcc -c Grille.c

API_AffGrille.o: API_AffGrille.c API_AffGrille.h Grille.h
	gcc -c API_AffGrille.c

Game_SortingRobot.o: Game_SortingRobot.c Grille.h API_AffGrille.h Solution.h 
	gcc -c Game_SortingRobot.c 

Game_SortingRobot: Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Game_SortingRobot Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

Checker_SortingRobot.o: Checker_SortingRobot.c Grille.h API_AffGrille.h Solution.h
	gcc -c Checker_SortingRobot.c

Checker_SortingRobot: Checker_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Checker_SortingRobot Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL



fonctions_base.o: fonctions_base.c fonctions_base.h
	gcc $(CFLAGS) -c fonctions_base.c
	
methode_naive.o: methode_naive.c methode_naive.h
	gcc $(CFLAGS) -c methode_naive.c
	
methode_circulaire.o: methode_circulaire.c methode_circulaire.h
	gcc $(CFLAGS) -c methode_circulaire.c

methode_LDC.o: methode_LDC.c methode_LDC.h
	gcc $(CFLAGS) -c methode_LDC.c
	
fonctions_AVL.o: fonctions_AVL.c fonctions_AVL.h
	gcc $(CFLAGS) -c fonctions_AVL.c
	
methode_AVL.o: methode_AVL.c methode_AVL.h
	gcc $(CFLAGS) -c methode_AVL.c

main_test.o: main_test.c
	gcc $(CFLAGS) -c main_test.c
	
main_test: main_test.o fonctions_base.o methode_naive.o methode_circulaire.o Solution.o Grille.o entree_sortie.o methode_LDC.o fonctions_AVL.o methode_AVL.o
	gcc $(CFLAGS) -o main_test main_test.o fonctions_base.o methode_naive.o methode_circulaire.o Solution.o Grille.o entree_sortie.o methode_LDC.o fonctions_AVL.o methode_AVL.o -lm


main_p1.o: main_p1.c
	gcc $(CFLAGS) -c main_p1.c
	
main_p1: main_p1.o fonctions_base.o methode_naive.o methode_circulaire.o Solution.o Grille.o entree_sortie.o methode_LDC.o fonctions_AVL.o methode_AVL.o
	gcc $(CFLAGS) -o main_p1 main_p1.o fonctions_base.o methode_naive.o methode_circulaire.o Solution.o Grille.o entree_sortie.o methode_LDC.o fonctions_AVL.o methode_AVL.o -lm


test_AVL.o: test_AVL.c
	gcc $(CFLAGS) -c test_AVL.c
	
test_AVL: test_AVL.o fonctions_AVL.o
	gcc $(CFLAGS) -o test_AVL test_AVL.o fonctions_AVL.o


gnuplot.o: gnuplot.c
	gcc $(CFLAGS) -c gnuplot.c

gnuplot: gnuplot.o fonctions_base.o methode_naive.o methode_circulaire.o Solution.o Grille.o entree_sortie.o methode_LDC.o fonctions_AVL.o methode_AVL.o
	gcc $(CFLAGS) -o gnuplot gnuplot.o fonctions_base.o methode_naive.o methode_circulaire.o Solution.o Grille.o entree_sortie.o methode_LDC.o fonctions_AVL.o methode_AVL.o



ListeDC.o: ListeDC.c
	 gcc $(CFLAGS) -c ListeDC.c

Graphe.o: Graphe.c
	gcc $(CFLAGS) -c Graphe.c

main_graphe.o: main_graphe.c Graphe.c Graphe.h
	gcc $(CFLAGS) -c main_graphe.c

main_graphe: main_graphe.o Graphe.o ListeDC.o Grille.o
	gcc $(CFLAGS) -o main_graphe main_graphe.o Graphe.o ListeDC.o Grille.o
	


clean2:
	rm *.o 
	


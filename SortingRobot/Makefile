all: main_naif main_exo1 clean #Game_SortingRobot Checker_SortingRobot

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

Checker_SortingRobot: Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Checker_SortingRobot Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL



exo1.o: exo1.c exo1.h
	gcc exo1.c -o exo.o -lm 

main_exo1.o: main_exo1.c
	gcc -c main_exo1.c 
	
main_exo1: main_exo1.o exo1.o Solution.o entree_sortie.o
	gcc -o main_exo1 main_exo1.o exo1.o Solution.o entree_sortie.o
	
main_naif.o: main_naif.c
	gcc -c main_naif.c 
	
main_naif: main_naif.o exo1.o Solution.o Grille.o entree_sortie.o
	gcc -o main_naif main_naif.o exo1.o Solution.o Grille.o entree_sortie.o
	
	

clean:
	rm *.o 
	
	
	


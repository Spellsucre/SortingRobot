#ifndef __DANIEL_GRAF_H__
#define __DANIEL_GRAF_H__


Cell_char *ajout_action_apres_c(Solution *S, Cell_char *c, int j, char a, Cell_char **Tref);

Cell_char *pluscourtchemin_apres_c(Solution *S, Cell_char *c, int j, int l, Cell_char **Tref);

void ajout_circuit_dans_solution(Cell_circuit *C, Solution *S, Cell_char *c, Cell_char **Tref, int *Jdroite);

void algorithme_circuit_CasLigne1x1(Grille *G, Solution *S);

void afficheTref(Cell_char **Tref, int n);

void afficheCellChar(Cell_char *c, char *label);




#endif

#ifndef __DANIEL_GRAF_H__
#define __DANIEL_GRAF_H__


Solution *daniel_graf(Grille *G);

Cell_char *ajout_action_apres_c(Solution *S, Cell_char *c, int j, char a, Cell_char **Tref);

Cell_char *plus_court_chemin_apres_c(Solution *S, Cell_char *c, int j, int l, Cell_char **Tref);

void ajout_circuit_dans_solution(LDC *L, Solution *S, Cell_char *c, Cell_char **Tref, int *Jdroite);

void algorithme_circuit_CasLigne1x1(Grille *G, Solution *S);






#endif

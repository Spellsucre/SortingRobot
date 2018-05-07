#ifndef __CIRCUITS_H__
#define __CIRCUITS_H__

#include "Graphe.h"
#include "ListeDC.h"
#include "Lcircuit.h"


void recherche_circuit_sommet(Sommet *s, Sommet *init, LDC *L);

Lcircuit *Graphe_Rech_Circuit(Graphe *h);

void CalculJminJmax(Lcircuit *LC);


#endif



#ifndef __LCIRCUITS_H__
#define __LCIRCUITS_H__

#include "Graphe.h"
#include "ListeDC.h"


typedef struct cell_circuit{
    LDC L;
    int jmin, jmax;
    struct cell_circuit *suiv;
} Cell_circuit;

typedef struct {
    int nb_circuit;
    Cell_circuit *premier;
    Cell_circuit *dernier;
} Lcircuit;


Cell_circuit* creerCell_circuit(LDC *L);

void LcircuitInitialise(Lcircuit *Lcircuit);

int LcircuitVide(Lcircuit* Lcircuit);

void LcircuitInsererEnTete(Lcircuit* Lcircuit, LDC *L);

void LcircuitInsererEnFin(Lcircuit* Lcircuit, LDC *L);

void LcircuitenleverCellule(Lcircuit* Lcircuit, Cell_circuit* c);

void Lcircuitafficher(Lcircuit* Lcircuit);

void Lcircuitdesalloue(Lcircuit *Lcircuit);


#endif



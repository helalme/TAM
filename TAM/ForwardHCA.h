//Forward heat conduction algorithm= FHCA
//Forward heat conduction problem= FHCP

#ifndef _FORWARDHCA_H //To prevent multiple inclusion
#define _FORWARDHCA_H


#include "Solver.h"
typedef std::vector<double> dVector1D;
typedef std::vector<dVector1D> dVector2D;
typedef std::vector<dVector2D> dVector3D;

void solveFHCP(const dVector2D&, const dVector2D&, dVector2D&);

void calculateInitialTemp(const dVector2D&, dVector1D &);

#endif


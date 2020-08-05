#ifndef _INVERSEHCA_H 
#define _INVERSEHCA_H

#include <vector>
#include "Solver.h"
typedef std::vector<double> dVector1D;
typedef std::vector<dVector1D> dVector2D;
typedef std::vector<dVector2D> dVector3D;


void solveIHCP(const dVector2D& , const dVector2D& , dVector2D& );

void constructA(const dVector2D& , dVector2D& );

void calculateInitTemp(const dVector2D&, dVector1D &);

#endif
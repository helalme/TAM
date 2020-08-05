//some linking error due to this HEADER, check this later

#ifndef _SOLVER_H 
#define _SOLVER_H

//#include<vector>
//#include<algorithm>
//#include "Matrix.h" 
#include"MatrixVectorManipulations.h"
typedef std::vector<double> dVector1D;
typedef std::vector<dVector1D> dVector2D;
typedef std::vector<dVector2D> dVector3D;
  
const dVector1D conjugateGradient(const dVector2D& A, const dVector1D& b);
//double helperFunction(double i, double alpha){return i*alpha;}

#endif 
#ifndef _MATRIXVECTORMANIPULATIONS_H
#define _MATRIXVECTORMANIPULATIONS_H
 
#include<vector>
#include "Matrix.h" 
typedef std::vector<dVector1D>    dVector2D;
  
const dVector2D addMatrix(const dVector2D& , const dVector2D& );//const return type is not so significant

const dVector2D subtractMatrix(const dVector2D&, const dVector2D& );

const double vectorDotProduct(const dVector1D& , const dVector1D& );

const dVector1D matrixDotVector(const dVector2D&, const dVector1D& );

const dVector2D& matrixTranspose( dVector2D& );

const double norm(const dVector1D&);

const dVector1D addVector(const dVector1D& , const dVector1D& );

const dVector1D subtractVector(const dVector1D& , const dVector1D& );

const dVector1D scalarIntoVector(const dVector1D& , const double& );


#endif
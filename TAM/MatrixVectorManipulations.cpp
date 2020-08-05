
#include "stdafx.h"
const dVector2D addMatrix(const dVector2D& lhs, const dVector2D& rhs )
{
	// Checking the sizes of the matrices
	if( lhs.size() != rhs.size() || lhs[0].size() != rhs[0].size() )
		throw std::invalid_argument( "Matrix sizes do not match" );

	// Creating a temporary matrix
	dVector2D tmp;
	// Performing the matrix addition
	for( std::size_t i=0; i<lhs.size(); ++i ) 
	{
		for( std::size_t j=0; j<lhs[0].size(); ++j ) 
		{
			tmp[i][j] = lhs[i][j] + rhs[i][j];
		}
	}
	// Returning the temporary
	return tmp;
}  
  
const dVector2D subtractMatrix(const dVector2D& lhs, const dVector2D& rhs )
{
	// Checking the sizes of the matrices
	if( lhs.size() != rhs.size() || lhs[0].size() != rhs[0].size() )
		throw std::invalid_argument( "Matrix sizes do not match" );

	// Creating a temporary matrix
	dVector2D tmp;
	// Performing the matrix addition
	for( std::size_t i=0; i<lhs.size(); ++i ) 
	{
		for( std::size_t j=0; j<lhs[0].size(); ++j ) 
		{
			tmp[i][j] = lhs[i][j] - rhs[i][j];
		}
	}
	// Returning the temporary
	return tmp;
}    

const double vectorDotProduct(const dVector1D& lhs, const dVector1D& rhs )
{
	// Checking the sizes of the matrices
	if( lhs.size() != rhs.size() )
		throw std::invalid_argument( "Vector sizes do not match" );
	double tmp=0;
	// Performing the matrix addition
	for( std::size_t i=0; i<lhs.size(); ++i ) 
	{
		tmp += lhs[i]* rhs[i];
		
	}
	// Returning the temporary
	return tmp;
}  

const dVector1D matrixDotVector(const dVector2D& M, const dVector1D& V )
{
	// Checking the sizes of the matrices
	if( M[0].size() != V.size() )
		throw std::invalid_argument( "Row sizes do not match" );
	dVector1D tmp(V.size());
	// Performing the matrix addition
	for( std::size_t i=0; i<M.size(); ++i ) 
	{
		tmp[i]=0.0;
		for( std::size_t j=0; j<V.size(); ++j ) 
		{
			tmp[i] += M[i][j] * V[j];
		}
	}
	// Returning the temporary
	return tmp;
}  

const dVector2D& matrixTranspose( dVector2D& M)
{
	for( std::size_t i=0; i<M.size(); ++i ) 
	{
		double temp=0.0;
		for( std::size_t j=0; j<M[0].size(); ++j ) 
		{
			if (j>i)
			{
				temp =M[i][j];
				M[i][j] = M[j][i];
				M[j][i] = temp;
			}
		}
	}
	return M;
} 

const double norm(const dVector1D& V)
{
	double norm=0;
	for( std::size_t i=0; i<V.size(); ++i )	
		norm += V[i]*V[i];
	norm = sqrt(norm);
	return norm;
}  

const dVector1D addVector(const dVector1D& lhs, const dVector1D& rhs)
{
	// Checking the sizes of the matrices
	if( lhs.size() != rhs.size() )
		throw std::invalid_argument( "Vector sizes do not match" );
	dVector1D tmp(lhs.size(),0);
	// Performing the vector addition
	for( std::size_t i=0; i<lhs.size(); ++i ) 
	{
		tmp[i] = lhs[i]+ rhs[i];
		
	}
	// Returning the temporary
	return tmp;
} 
 
const dVector1D subtractVector(const dVector1D& lhs, const dVector1D& rhs)
{
	// Checking the sizes of the matrices
	if( lhs.size() != rhs.size() )
		throw std::invalid_argument( "Vector sizes do not match" );
	
	dVector1D tmp(lhs.size(),0);
	// Performing the vector subtraction
	for( std::size_t i=0; i<lhs.size(); ++i ) 
	{
		tmp[i] = lhs[i]- rhs[i];
		
	}
	// Returning the temporary
	return tmp;
}  

const dVector1D scalarIntoVector(const dVector1D& V, const double& S )
{
	dVector1D tmp(V.size());
	for( std::size_t i=0; i<V.size(); ++i ) 
	{
		tmp[i] = V[i]*S;
		
	}
	return tmp;
}  

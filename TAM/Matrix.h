#ifndef _MATRIX_H
#define _MATRIX_H

#include <vector>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "FileReader.h"
//using std::size_t;

typedef std::vector<double>    dVector1D;
  
// Definition of the Matrix class
class Matrix
{
  public:
	
	Matrix();// Default constructor

	Matrix( FileReader& fm ); // Constructor for a matrix of size m x n

	~Matrix(); // Destructor
	
	Matrix& operator=( const Matrix& rhs );// Copy assignment operator
		
	void writeMatrixIntoFile( const std::string& outFile, const Matrix& m );
	// Matrix output file operator
	friend std::ofstream& operator<<( std::ofstream& ofs, const Matrix& m )
	{
		for( std::size_t i=0; i<m.rows(); ++i ) 
		{
			for( std::size_t j=0; j<m.columns(); ++j ) 
			{
				ofs << m.m_vvMatrix[i][j] << "\t";
			}
			ofs << "\n";
		}
		return ofs;
	}
	// Matrix input file operator
	/*friend std::ifstream& Matrix::operator>>( std::ifstream& ifs, Matrix& m )
	{
		m.m_ = r;
		m.n_ = c;
		// Creating a temporary matrix
		Matrix tmp;
		// Extracting the matrix elements
		for( size_t i=0; i<r; ++i ) 
		{
			for( size_t j=0; j<c; ++j ) 
			{
				if( !( ifs >> tmp.m_vvMatrix[i][j] ) )
					throw std::runtime_error( "Broken matrix input file" );
			}
		}
		// Copying the matrix
		m = tmp;
		return ifs;
	}*/
		
	// Rows function
	inline std::size_t rows() const 
	{ 
		return m_; 
	}
	// Columns function
	inline std::size_t columns() const 
	{
		return n_; 
	}
	// returning data of 2d vector
	inline const std::vector<dVector1D>& get2dVector() const 
	{ 
		return this->m_vvMatrix; 
	}
	
	// Matrix addition operator
	const Matrix operator+( const Matrix& rhs )
	{
		// Checking the sizes of the matrices
		if( this->rows() != rhs.rows() || this->columns() != rhs.columns() )
			throw std::invalid_argument( "Matrix sizes do not match" );
		// Creating a temporary matrix
		Matrix tmp;
		// Performing the matrix addition
		for( std::size_t i=0; i<this->rows(); ++i ) 
		{
			for( std::size_t j=0; j<this->columns(); ++j ) 
			{
				tmp.m_vvMatrix[i][j] = this->m_vvMatrix[i][j] + rhs.m_vvMatrix[i][j];
			}
		}
		// Returning the temporary
		return tmp;
	}

  private:
	std::size_t m_; // The current number of rows of the matrix.
	std::size_t n_; // The current number of columns of the matrix.
  public:
	std::vector<dVector1D> m_vvMatrix;
};
#endif 


	
	


	
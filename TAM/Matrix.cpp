
#include "stdafx.h"

Matrix::Matrix() : m_ ( 0U ), n_ ( 0U ) 	
{
	this->m_vvMatrix.clear();
}   
  
Matrix::Matrix(FileReader& fm )
{
	this->m_= fm.GetNumRows();
	this->n_ = fm.GetNumColumns();
	this->m_vvMatrix = fm.m_vData;
} 

Matrix::~Matrix()
{
	this->m_vvMatrix.clear();
}  

Matrix& Matrix::operator=( const Matrix& rhs )
{
	if( &rhs == this ) 
		return *this;
	this->m_ = rhs.rows();
	this->n_ = rhs.columns();
	this->m_vvMatrix = rhs.get2dVector();
	
	return *this;
} 

void Matrix::writeMatrixIntoFile( const std::string& filename, const Matrix& m )
{
	std::ofstream outFile;
	outFile.open(filename.c_str());
	if (!outFile.is_open())
	{
		std::cout << "Couldn't open output file.\n";
		exit(EXIT_FAILURE);
	}
	for( std::size_t i=0; i<m.rows(); ++i )
	{
		for( std::size_t j=0; j<m.columns(); ++j ) 
		{
			outFile << std::setw(8) << m.m_vvMatrix[i][j];
		}
		outFile << "\n";
	}
	outFile.close();
}  
 
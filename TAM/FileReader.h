//need to define a file type object, that will be used in file reader and writer
//so modify FileReader and FileWriter
#ifndef _FILEREADER_H 
#define _FILEREADER_H

//#define NOMINMAX
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>


//using namespace std;//bad practice
//using std::ifstream; // slightly bad practice
//declaring std scope in the narrowest scope is the best practice!!!!
//using std::ofstream;//avoid wider scope
//using std::fstream;//avoid wider scope
//using std::vector;//avoid wider scope
//using std::string;//avoid wider scope

typedef std::vector<std::string>    sVector1D;
typedef std::vector<double> dVector1D;
typedef std::vector<dVector1D> dVector2D;
typedef std::vector<dVector2D> dVector3D;

class FileReader
{
	public:
		FileReader();
		FileReader(const std::string&);

		FileReader(const std::string&, const std::size_t, const std::size_t );

		//constructor to construct file taking name and fileContents only, like for output file
		//FileManager(const string&, const vector<doubleVector>& );
		
		~FileReader();
		
		int ReadMatrix();
		
		inline size_t GetNumRows()
		{
			return m_iNumRows;
		}

		inline size_t GetNumColumns()
		{
			return m_iNumColumns;
		}

		void Clear();
	
	private:
		size_t getColumnSize();
		size_t getRowSize();

	public:
		std::vector<dVector1D>	m_vData;
	private:
		//stringVector			m_vTypes;
		std::string					m_strFile;
		size_t					m_iNumRows;
		size_t					m_iNumColumns;

};
#endif //_FILEREADER_H
#include "stdafx.h"


FileReader::FileReader()
{
	Clear();
}  
  
FileReader::FileReader(const std::string& sFilename ): m_strFile(sFilename)
{
	ReadMatrix();
}  
  
FileReader::FileReader(const std::string& sFilename, const std::size_t R, const std::size_t C  ): m_strFile(sFilename)
{
	m_iNumRows=R;
	m_iNumColumns=C;
	std::ifstream in(m_strFile.c_str());
	//in.open(m_strFile.c_str());
	/*TCHAR CDirec[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,CDirec);
	std::cout<<CDirec<<std::endl;*/

	double dTemp =0;
	bool b = in.good();
	if (!in.is_open())
	{
		std::cout << "Cannot open file.\n";
		exit(EXIT_FAILURE);
	}
	//here we can use std::copy(..) instead of double for loop
	for (size_t row=0; row<R; row++)
	{
		dVector1D vTemp;
		for (std::size_t col=0; col<C; col++)
		{
			in >>dTemp;
			vTemp.push_back(dTemp); ///getline() diye ek row ke ek line hisebe niye ta std::stringstream type e convert kore alada vabe read kora jay
		}
		m_vData.push_back(vTemp);
		vTemp.clear();
	}

	in.close();
}

  
FileReader::~FileReader()
{
	Clear();
}
  
void FileReader::Clear()
{
	m_strFile = "";
	m_iNumRows = 0;
	m_iNumColumns = 0;
	//m_vTypes.clear();
	m_vData.clear();
	
} 
  
std::size_t FileReader::getColumnSize()
{
	double temp=0;
	std::size_t ncols=0;
	const char EOL = '\n'; 
	std::ifstream infile(m_strFile.c_str());

	if (!infile.is_open())
	{
		std::cout << "Couldn't evaluate number of columns.\n";
		return EXIT_FAILURE;
	}
	infile.seekg(std::ios_base::beg);
	while ( infile.peek()!=EOL && infile.good())
	{
		infile>>temp; 
		ncols++; 
	}
	infile.close();
	return ncols;
}  
 
std::size_t FileReader::getRowSize()
{
	double temp=0;
	std::size_t nrows=0,col_count=0;
	const char EOL = '\n'; 

	std::ifstream in(m_strFile.c_str());
	
	if (!in.is_open())
	{
		std::cout << "Cannot evaluate number of rows.\n";
		return EXIT_FAILURE;
	}
	in.seekg(std::ios_base::beg);  
	while (!in.eof() && in.good())  
	{ 
		if (in.peek()==EOL)
		{
			//in.ignore(std::numeric_limits<std::streamsize>::max(),EOL); //take care, why error introduced later??
			nrows++; 
			in >>temp;
			
		}
		else
		{ 
			while (in.peek()!=EOL)
			{ 
				in >>temp;
				col_count++; 
				if (in.eof())
					break;
			}
		}
	}
	in.close();
	return nrows;
}    
  
int FileReader::ReadMatrix()
{
	std::size_t ncols=getColumnSize();
	std::size_t nrows=getRowSize();
	m_iNumRows=nrows;
	m_iNumColumns=ncols;
	std::ifstream in(m_strFile.c_str());
	double dTemp =0;
	if (!in)
	{
		std::cout << "Cannot open file.\n";
		return EXIT_FAILURE;
	}
	//here we can use std::copy(..) instead of double for loop
	for (size_t row=0; row<nrows; row++)
	{
		dVector1D vTemp;

		for (std::size_t col=0; col<ncols; col++)
		{
			in >>dTemp;
			vTemp.push_back(dTemp);
		}
		m_vData.push_back(vTemp);
		vTemp.clear();
	}

 in.close();
 return EXIT_SUCCESS;
}
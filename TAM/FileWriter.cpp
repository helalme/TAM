#include "stdafx.h"


FileWriter::FileWriter()
{
	this->m_strFileName.clear();
	this->m_fmFile.Clear();
}
  
FileWriter::FileWriter(const std::string& sFileName):m_strFileName(sFileName)
{
	this->m_fmFile = FileReader::FileReader(this->m_strFileName);
}

FileWriter::FileWriter(const dVector2D& vvData)
{
	this->m_fmFile.m_vData = vvData;
	this->m_strFileName.clear();
}
FileWriter::~FileWriter()
{
	closeWriter();
}

void FileWriter::closeWriter()
{
	if (!this->m_strFileName.empty())
	{
		this->m_strFileName.clear();
	}
	this->m_fmFile.Clear();
}
 
void FileWriter::write(const std::string& filename)
{
	/*if(boost::filesystem::exists(filename.c_str())//boost library need to be installed
		remove(filename);*/
//	GetFileAttributes(filename.c_str());
	if (INVALID_FILE_ATTRIBUTES != GetFileAttributesA(filename.c_str()) && GetLastError() != ERROR_FILE_NOT_FOUND)
		remove(filename.c_str());

	std::ofstream outFile;
	outFile.open(filename.c_str());
	if (!outFile.is_open())
	{
		std::cout << "Couldn't open output file.\n";
		exit(1);
	}
	//outFile.write(&file.m_vData[0], file.m_vData.size());//this approach for cosnt char*
	//std::copy er jonno ofstream_iterator lagbe bodhoy, ja define kora nai.... 
	//std::copy(file.m_vData.begin(), file.m_vData.end(), std::ostream_iterator<std::string>(outFile, "\n") outFile);
	std::size_t i = 0;
	for (std::vector<dVector1D>::iterator it=this->m_fmFile.m_vData.begin(); it != this->m_fmFile.m_vData.end(); ++it)
	{
		dVector1D vTemp;
		outFile<<i<<'\t';
		for (std::vector<double>::iterator it1=it->begin(); it1 != it->end(); ++it1)
		{
			outFile<<*it1<<'\t';
		}
		outFile<<'\n';
		++i;
	}
	outFile.close();
}
	

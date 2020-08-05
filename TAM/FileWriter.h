//for simplicity, only write method is enough instead of a class or struct

#ifndef _FILEWRITER_H
#define _FILEWRITER_H

#include<string>
#include "FileReader.h"
#include<vector>
//#include<boost>
#include "winbase.h"
#include <cstdio>


typedef std::vector<double> dVector1D;
typedef std::vector<dVector1D> dVector2D;
typedef std::vector<dVector2D> dVector3D;

struct FileWriter
{
 	FileWriter();
	FileWriter(const std::string&);
	FileWriter(const dVector2D&);
	~FileWriter();
	void closeWriter();
	void write(const std::string&);

	//Data members
 	std::string m_strFileName; // THE NAME OF THE TEXT FILE THIS OBJECT WILL WRITE TO
	FileReader m_fmFile;  //FileReader Object


};
#endif
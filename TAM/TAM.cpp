// TAM.cpp : Defines the entry point for the console application.
//TAM=Thermal Analysis module

#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h> //TCHAR, MAX_PATH, GetCurrentDirectory
#include "FileReader.h"
#include "FileWriter.h"
#include "Matrix.h"
#include "MatrixVectorManipulations.h"
#include "Solver.h"
#include "ForwardHCA.h"
#include "InverseHCA.h"

#include<direct.h> //_chdir(), _mkdir()
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib") //necessary to put linker>input>additional dependency??

typedef std::vector<double> dVector1D;
typedef std::vector<dVector1D> dVector2D;
typedef std::vector<dVector2D> dVector3D;

void DisplayErrorBox(LPTSTR lpszFunction);

int _tmain(int argc, _TCHAR* argv[])
{
	//======================================================== 
	//Reading .txt file list from the directory
   WIN32_FIND_DATA ffd;
   LARGE_INTEGER filesize;
   TCHAR szDir[MAX_PATH];
   size_t length_of_arg;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;
   std::vector<std::string> vsFileList;

   //check current directory
	TCHAR CDirec[MAX_PATH];
	_chdir("..\\data\\");//up the directory to data folder
	GetCurrentDirectory(MAX_PATH,CDirec);
	//_mkdir(".");

   
   // Check that the input path plus 3 is not longer than MAX_PATH.
   // Three characters are for the "\*" plus NULL appended below.

   StringCchLength(CDirec, MAX_PATH, &length_of_arg);

   if (length_of_arg > (MAX_PATH - 3))
   {
	   std::cout<<std::endl<<"Directory path is too long."<<std::endl;
      return (-1);
   }
	
    _tprintf(TEXT("\nData directory: %s\n\n"), CDirec);
   //std::cout<<"Data directory:  "<<CDirec<<std::endl;

   // Prepare string for use with FindFile functions.  First, copy the
   // string to a buffer, then append '\*' to the directory name.

   StringCchCopy(szDir, MAX_PATH, CDirec);
   StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

   // Find the first file in the directory.

   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) 
   {
      DisplayErrorBox(TEXT("FindFirstFile"));
      return dwError;
   } 
   
   // List all the files in the directory with some info about them.

   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
        // _tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);//do nothing
      }
      else
      {
         filesize.LowPart = ffd.nFileSizeLow;
         filesize.HighPart = ffd.nFileSizeHigh;
		  //convert from wide char to narrow char array
		 char ch[260];
		 char DefChar = ' ';
		 WideCharToMultiByte(CP_ACP,0,ffd.cFileName,-1, ch,260,&DefChar, NULL);
		 std::string str(ch);
		 const std::string str1 = ".txt";
		 std::size_t found = str.find(str1);
		 if(found!=std::string::npos){
			vsFileList.push_back(ch);
			std::cout<<vsFileList.size()-1<<"	";
			 _tprintf(TEXT("%s \n"), ffd.cFileName);
		 }
      }
   }
   while (FindNextFile(hFind, &ffd) != 0);
 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) 
   {
      DisplayErrorBox(TEXT("FindFirstFile"));
   }
   FindClose(hFind);
	
   //======================.txt file names generated======

	//starting computation either forward or inverse
	
    std::cout<<std::endl<<"Enter 1 for forward heat conduction and 2 for inverse problem: "<<std::endl;
	int iChoice=0;
	std::cin>>iChoice;

	//std::cout<<"Reference file should have "<< iLayer*iLayer+1<<" columns"<<std::endl;
	std::cout<<std::endl<<"Enter reference data-file number (given at the beginning): "<<std::endl;
	int iRefFileNo=0, iTimeStep=0;
	std::cin>>iRefFileNo;
	std::cout<<std::endl<<"File reading......... "<<std::endl;
	FileReader fRefT(vsFileList[iRefFileNo]);
	int iLayer=(int)sqrt(fRefT.GetNumColumns()-1.0);
	std::cout<<std::endl<<"It is a "<<iLayer<<" points/layers stratification problem.";
	std::cout<<" Number of time steps is "<<fRefT.GetNumRows()-1<<std::endl;

	
	int iInnTFileNo=0,iOutTFileNo=0;
	if (iChoice==1)
	{
		std::cout<<std::endl<<"Enter file number of inner temperature history"<<std::endl;
		std::cin>>iInnTFileNo;
		FileReader fInT(vsFileList[iInnTFileNo]);
		if (fInT.GetNumColumns() != iLayer)
		{
			std::cout <<std::endl<< "Warning: Inner temperature file should contain "<<iLayer<<"columns."<<std::endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
		
		if (fInT.GetNumRows() != fRefT.GetNumRows())
		{
			std::cout <<std::endl<< "Warning: number of rows in two files are not equal. Results might not be accurate always. "<<std::endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
		std::cout<<std::endl<<"Running forward heat conduction algorithm......."<<std::endl;
		
		std::vector<dVector1D> calOutTemp(fInT.GetNumRows(),dVector1D(fInT.GetNumColumns()));
		solveFHCP(fInT.m_vData, fRefT.m_vData, calOutTemp);

		
		// FileWriter
		FileWriter fwOutFile(calOutTemp);//why an output file cannot be read by filemanager and filewriter
		_chdir("..\\output\\");
		fwOutFile.write("outerWall_temp.txt");
		std::cout<<std::endl<<"Outer wall temperature file has been generated, please check the 'output' directory."<<std::endl;
	}
	
	if (iChoice==2)
	{
		std::cout<<std::endl<<"Enter file number of outer wall temperature history"<<std::endl;
		std::cin>>iOutTFileNo;
		FileReader fOutT(vsFileList[iOutTFileNo]);

		if (fOutT.GetNumColumns() != iLayer+1)
		{
			std::cout <<std::endl<< "Warning: Outer wall temperature file should contain "<<iLayer+1<<"columns including additional column for time."<<std::endl;
			exit(EXIT_FAILURE);
		}

		if (fOutT.GetNumRows() != fRefT.GetNumRows())
		{
			std::cout <<std::endl<< "Warning: number of rows in two files are not equal. Results might not be accurate, so stopping computations. "<<std::endl;
			system("pause");
			exit(EXIT_FAILURE);
		}

		std::cout<<std::endl<<"Running inverse heat conduction algorithm......."<<std::endl;
		
		dVector2D calInnTemp(fOutT.GetNumRows(), dVector1D(fOutT.GetNumColumns() - 1));
		solveIHCP(fOutT.m_vData, fRefT.m_vData, calInnTemp);

		
		// FileWriter
		FileWriter fwInnFile(calInnTemp);
		_chdir("..\\output\\");
		fwInnFile.write("InnerWall_temp.txt");
		std::cout<<std::endl<<"Inner wall temperature file has been generated, pleae check the 'output' directory."<<std::endl;
	}
	
   system("pause");
   return 0;
}


//supporting function for getting file list
void DisplayErrorBox(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and clean up

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
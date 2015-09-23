#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "txtParse.h"

#define INPUTFILE "input.txt"
#define OUTPUTFILE "output.txt"

using namespace std;

int totPageFrames;
int maxSegmentLength;
int pageSize;
int numPageFramePerSec;
int min, max;
int totNumProcs;
int PageFaultCount;
int algoValue;
ofstream fout(OUTPUTFILE);

vector < vector < string > > pidWithTotPageFrame;

/*****************************************************************/
//Function Name : getIPFromFile
//Function Defn : For parsing the input from the input.txt file
/*****************************************************************/
int getIPFromFile()
{
 vector <string> buffVectorA;
 vector < vector <string> > pidWithTotPageFrameBuff;
 ifstream infile;
 int iBuff = 0, countBuff = 0, intBuff, jBuff = 0; 
 int procsCount = 0;

 infile. open( INPUTFILE );
 if ( !infile ) 
 {
  cout << "The Input File input.txt is not Open" << endl;
  cin.get ();
  exit (1);
 }

 string tmpStr, tmpStr1;
 while ( !infile.eof() )
 {
  std :: getline ( infile, tmpStr );
  buffVectorA.push_back ( tmpStr );
 }

 for ( iBuff = 0; iBuff < buffVectorA.size(); iBuff ++ )
 {
  istringstream iss( buffVectorA[iBuff] );
  switch  (iBuff)
  {
   case 0:{ istringstream(buffVectorA[0]) >> ::totPageFrames; break; }
   case 1:{ istringstream(buffVectorA[1]) >> ::maxSegmentLength; break; }
   case 2:{ istringstream(buffVectorA[2]) >> ::pageSize; break; }
   case 3:{ istringstream(buffVectorA[3]) >> ::numPageFramePerSec; break; }
   case 4:{ istringstream(buffVectorA[4]) >> ::min; break; }
   case 5:{ istringstream(buffVectorA[5]) >> ::max; break; }
   case 6:{ istringstream(buffVectorA[6]) >> ::totNumProcs; break; }
   default:
   {
    pidWithTotPageFrameBuff. push_back( vector<string>() );
    while ( getline( iss, tmpStr, ' ' ))
    {
     switch (countBuff)
     {
      case 0:{ tmpStr1 = tmpStr.c_str(); countBuff++; pidWithTotPageFrameBuff[procsCount]. push_back(tmpStr1); break; }
      case 1:{ tmpStr1 = tmpStr.c_str(); countBuff = 0; pidWithTotPageFrameBuff[procsCount]. push_back(tmpStr1); break; }
     }
    }
    procsCount++;
    break;
   }
  } 
 }
 
 countBuff = 0;
 int count = 2, tempCount;
 for ( iBuff = 0; iBuff < totNumProcs; iBuff ++ ) pidWithTotPageFrame. push_back( vector<string>() );
 for ( iBuff = 0; iBuff < procsCount; iBuff ++ )
 { 
   if ( countBuff == 0 )
   {
    pidWithTotPageFrame[0]. push_back( pidWithTotPageFrameBuff[iBuff][0] ); 
    pidWithTotPageFrame[0]. push_back( pidWithTotPageFrameBuff[iBuff][1] );
    countBuff ++;
   }
   else
   {
    tempCount = 0;
    for ( jBuff = 0; jBuff < countBuff; jBuff ++)
    {
     if ( pidWithTotPageFrame[jBuff][0] == pidWithTotPageFrameBuff[iBuff][0] )
     {
      pidWithTotPageFrame[jBuff]. push_back( pidWithTotPageFrameBuff[iBuff][1]);
      count++; tempCount++;
      break;
     }
    }
    if(tempCount == 0)
    {
     pidWithTotPageFrame[countBuff]. push_back( pidWithTotPageFrameBuff[iBuff][0] );
     pidWithTotPageFrame[countBuff]. push_back( pidWithTotPageFrameBuff[iBuff][1] );
     countBuff ++; tempCount = 0;
    }    
   }
 }
}//fn end

/*****************************************************************/
//Function Name : prntOut
//Function Defn : to print all the outputs of the text parsing
/*****************************************************************/
int prntOut()
{

 fout << "*****************************************************************" << endl;
 fout << "*****************************************************************" << endl;
 fout << "******  Virtual Memory Manager with Page Fault Calculation ******" << endl;
 fout << "*****************************************************************" << endl;
 fout << "*****************************************************************" << endl;

 fout << endl ;
 fout << "*******************    Input Datum    ************************" << endl;
 
 int iBuff, jBuff;
 fout << "Total Pages per frame  :" << ::totPageFrames << endl;
 fout << "Maximum Segment Length :" << ::maxSegmentLength << endl;
 fout << "Page Size              :" << ::pageSize << endl;
 fout << "Number of Page Frame per second :" << ::numPageFramePerSec << endl;
 fout << "Min                    :" << ::min << endl; 
 fout << "Max                    :" << ::max << endl;
 fout << "Total Number of Process:" << ::totNumProcs << endl;
 
 int temp;
 for ( iBuff = 0; iBuff < totNumProcs; iBuff ++ ){  
   fout << endl << "processID : " << pidWithTotPageFrame[iBuff][0] << endl;
    for ( jBuff = 1; jBuff < pidWithTotPageFrame[iBuff]. size (); jBuff++ )
     fout << "----------->" << pidWithTotPageFrame[iBuff][jBuff] << endl; }

 fout << endl << endl;
 fout << "**************************************************************" ;
}    

/*****************************************************************/
//Function Name : getAlgoValue
//Function Defn : To get the Input from the user on the algorithm
/*****************************************************************/
int getAlgoValue()
{
  cout << "*****************************************************************" << endl;
  cout << "*****************************************************************" << endl;
  cout << "******  Virtual Memory Manager with Page Fault Calculation ******" << endl;
  cout << "*****************************************************************" << endl;
  cout << "*****************************************************************" << endl;

  cout << endl << "Feed the Page Replacement Algorithm to be Used" << endl;
  cout << "1. First In First Out - FIFO" << endl;
  cout << "2. Last In Last Out - LIFO" << endl;
  cout << "3. Least Frequently Used - LRU" << endl;
  cout << "4. Most Frequently Used - MFU" << endl;
  cout << "5. Random" << endl;
  cout << "6. Working Set" << endl;
  cout << "NOTE : Please Make sure, you have compiled the correct files before selecting the Algorithm" << endl;
  cin >> algoValue;
	
  if ( algoValue == 1 || algoValue == 2 || algoValue == 3 || algoValue == 4 || algoValue == 5 || algoValue == 6 )
  {
     switch (algoValue)
      {
 	case 1:
	{
 	cout << endl << "Algorithm FIFO is being processed" << endl;
	fout << endl << "Virtual Page Replacement Algorithm - FIFO used for Page Fault Calcualtion" << endl;
	fout << "**************************************************************" << endl ;
    fout.close ();
	break;
	}
        case 2:
        {
        cout << endl << "Algorithm LIFO is being processed" << endl;
        fout << endl << "Virtual Page Replacement Algorithm - LIFO used for Page Fault Calcualtion" << endl;
        fout << "**************************************************************" << endl ;
	break;
        }
        case 3:
        {
        cout << endl << "Algorithm LRU is being processed" << endl;
        fout << endl << "Virtual Page Replacement Algorithm - LRU used for Page Fault Calcualtion" << endl;
	fout << "**************************************************************" << endl ;
        break;
        }
        case 4:
        {
        cout << endl << "Algorithm MFU is being processed" << endl;
        fout << endl << "Virtual Page Replacement Algorithm - MFU used for Page Fault Calcualtion" << endl;
	fout << "**************************************************************" << endl ;
        break;
        }
        case 5:
        {
        cout << endl << "Algorithm RANDOM is being processed" << endl;
        fout << endl << "Virtual Page Replacement Algorithm - RANDOM used for Page Fault Calcualtion" << endl;
        fout << "**************************************************************" << endl ;
        break;
        }
        case 6:
        {
        cout << endl << "Working Set Algorithm is being processed" << endl;
        fout << endl << "Virtual Page Replacement Algorithm - WORKING SET used for Page Fault Calcualtion" << endl;
        fout << "**************************************************************" << endl ;
        break;
        }
      }
  }
  else
  {
	cout << endl << "Please select a valid algorithm" << endl << "Program Terminating" << endl;
	cin.get();
	exit(0);
  }
  return (algoValue);
}

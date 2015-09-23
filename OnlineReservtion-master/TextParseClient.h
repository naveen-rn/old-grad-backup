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

#define INPUTFILE "input.txt"
#define OUTPUTFILE "output.txt"

using namespace std;

extern int numOfFlights;
extern int numOfAgents;
extern ifstream infile;
extern ofstream fout;
extern vector <string> buffVectorA;
extern vector <string> requestVector;

/*****************************************************************/
//Function Name : getIPFromFile
//Function Defn : For parsing the input from the input.txt file
/*****************************************************************/
int getIPFromFile()
{
 
 string tmpStr;
 numOfFlights = 0;
 
 infile. open( INPUTFILE );
 if ( !infile ) 
 {
  cout << "The Input File input.txt is not Open" << endl;
  cin.get ();
  exit (1);
 }

 /* getting all the values stored in the buffer Vector from the input.txt file */
 while ( !infile.eof() )
 {
  std :: getline ( infile, tmpStr );
  buffVectorA.push_back ( tmpStr );
 }
 
  /* getting the values for the numOfFlights and numOfAgents */
 for ( int iBuff = 0; iBuff < buffVectorA.size(); iBuff ++ )
 {
  istringstream iss( buffVectorA[iBuff] );
  if ( iBuff == 0 ) 
	istringstream(buffVectorA[0]) >> ::numOfFlights; 
  if ( numOfFlights != 0 && iBuff == (numOfFlights + 1) ) 
	istringstream(buffVectorA[iBuff]) >> ::numOfAgents; 
 }

 for ( int iBuff = 0; iBuff < numOfAgents; iBuff++ )
 {
	string temp, temp1;
	string appendTemp;
	int intIBuff = 0; 
	for ( int jBuff = numOfFlights + 3 + ( iBuff * 10 ) ; jBuff < numOfFlights + 3 + ( iBuff * 10 ) +  8 ; jBuff++ )
	{
		stringstream s ( buffVectorA[jBuff] );
		int intJBuff = 0;
		while  ( s >> temp )
		{
			if ( ( intJBuff == 1 ) && ( intIBuff < 4 ) )
				{
					appendTemp. append ( "Agent " );
					ostringstream convert; convert << iBuff + 1; temp1 = convert.str ();
					appendTemp. append ( temp1 );
					appendTemp. append ( " " );
					appendTemp. append ( temp );
					appendTemp. append ( " " );
					appendTemp. append ( buffVectorA[jBuff+4] );
					requestVector.push_back ( appendTemp );
					appendTemp.clear();
				}
			intJBuff++;
		}
		intIBuff++;
	}	
 }
}

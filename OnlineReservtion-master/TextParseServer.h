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
#define SSTR( x ) dynamic_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()
using namespace std;

extern int numOfFlights;
extern int numOfAgents;
extern ifstream infile;
extern ofstream fout;

vector<string> ticketResults;
vector < vector < int > > flightPlan;
vector < vector <int> > flightPlanBuffer;
int intBuff = 0;

vector < vector < int > > seatStatus;
vector < vector < string > > seatStatusName;

	
/*****************************************************************/
//Function Name : getIPFromFile
//Function Defn : For parsing the input from the input.txt file
/*****************************************************************/
int getIPFromFile()
{
 
 vector <string> buffVectorA;
 string tmpStr;
 numOfFlights = 0;
 
 infile. open( INPUTFILE );
 if ( !infile ) 
 {
  cout << "The Input File input.txt is not Open" << endl;
  cin.get ();
  exit (1);
 }

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

 for ( int iBuff = 0; iBuff < numOfFlights; iBuff++ )
 {	flightPlanBuffer. push_back(vector<int>()); }
 
 string temp;
 for ( int iBuff = 1; iBuff <= numOfFlights; iBuff ++ )
 {
	stringstream s ( buffVectorA[iBuff] );
	while  ( s >> temp )
	{
		istringstream ( temp ) >> intBuff;
		flightPlanBuffer[iBuff-1] .push_back( intBuff );
	}
 }
 
}

/*****************************************************************/
//Function Name : arrangeIPUserFormat
//Function Defn : For modifing the parsed input data to usr defined
//				  data
/*****************************************************************/
int arrangeIPUserFormat ()
{
 
 for ( int iBuff = 0; iBuff < numOfFlights; iBuff ++ )
	intBuff = intBuff + flightPlanBuffer[iBuff][1];

 for ( int iBuff = 0; iBuff < intBuff; iBuff++ )
 {	
	flightPlan. push_back(vector<int>()); 
 }

 intBuff = 0;
 for ( int iBuff = 0; iBuff < numOfFlights; iBuff++ )
 {	
	for ( int jBuff = 0; jBuff < flightPlanBuffer[iBuff][1]; jBuff++ )
	{	
		flightPlan[intBuff]. push_back( flightPlanBuffer[iBuff][0] );  	
		for ( int kBuff = 0; kBuff < flightPlanBuffer[iBuff][2]; kBuff++ )
			flightPlan[intBuff]. push_back(0);
		intBuff++; 
	} 
 }
 
}

/*****************************************************************/
//Function Name : printOPFromFileBefore
//Function Defn : For printing the intermediatory results
/*****************************************************************/
int printOPFromFileBefore ()
{
 fout. open( OUTPUTFILE );

 fout << "*****************************************************************" << endl;
 fout << "*****************************************************************" << endl;
 fout << "*********  Interprocess Communication with Unix Sockets *********" << endl;
 fout << "*****************************************************************" << endl;
 fout << "*****************************************************************" << endl;
 
 /*fout << endl << endl << "*********  Flight Plan Before Requests are Processed *********" << endl << endl;
 
 for ( int iBuff = 0; iBuff < intBuff; iBuff++ )
 {
	fout << "Flight Number " ;
 	for ( int jBuff = 0; jBuff < flightPlan[iBuff]. size(); jBuff++ )
	{	fout << flightPlan[iBuff][jBuff] << " "; 	}
	fout << endl;
	if ( iBuff +1 != intBuff ) if ( flightPlan[iBuff][0] !=  flightPlan[iBuff + 1][0] ) { fout << endl; }
 } 
 
 fout << endl;
 fout << "*****************************************" << endl;
 fout << "NOTE : 0 represents the un-occupied seats" << endl;
 fout << "*****************************************" << endl;
 fout << endl << endl;*/

 fout << endl << endl << "*****************************************************************" << endl;
 fout << "*****               Client Request Details                  *****" << endl;
 fout << "*****************************************************************" << endl << endl; 
 
}

/*****************************************************************/
//Function Name : convertSeatNumber
//Function Defn : For coverting the seat number from alphabet to
//				  to number
/*****************************************************************/
int convertSeatNumber ( string tempBuffer )
{
	if (( tempBuffer == "A" )||( tempBuffer == "a" )) return 1;
	else if (( tempBuffer == "B" )||( tempBuffer == "b" )) return 2;
	else if (( tempBuffer == "C" )||( tempBuffer == "c" )) return 3;
	else if (( tempBuffer == "D" )||( tempBuffer == "d" )) return 4;
	else if (( tempBuffer == "E" )||( tempBuffer == "e" )) return 5;
	else if (( tempBuffer == "F" )||( tempBuffer == "f" )) return 6;
	else if (( tempBuffer == "G" )||( tempBuffer == "g" )) return 7;
	else if (( tempBuffer == "H" )||( tempBuffer == "h" )) return 8;
	else if (( tempBuffer == "I" )||( tempBuffer == "i" )) return 9;
	else return 0;
}

/*****************************************************************/
//Function Name : checkSeat
//Function Defn : For checking whether the seat is available
/*****************************************************************/
int checkSeat ( int type, int flight, int row, int column, int agentID, string passengerName, string tempBuff )
{
	int count = 0;
	switch(type)
	{
	case 1:
		{
			for ( int iBuff = 0; iBuff < seatStatus. size(); iBuff++ )
			{
				if ( ( seatStatus[iBuff][0] == flight ) && ( seatStatus[iBuff][1] == row ) && ( seatStatus[iBuff][2] == column ) )
				{
					count++;
					fout << " : Seat already reserved or ticketed" << endl;
					tempBuff. append ( " : Seat already reserved or ticketed");
					ticketResults. push_back ( tempBuff );
					return 0;
				}
			}
			if ( count == 0 )
			{
				seatStatus. push_back( vector<int>() );
				seatStatusName. push_back( vector<string>() );

				int pointLocation = seatStatus. size ();
				seatStatus[pointLocation - 1].push_back ( flight );
				seatStatus[pointLocation - 1].push_back ( row );
				seatStatus[pointLocation - 1].push_back ( column );
				seatStatus[pointLocation - 1].push_back ( type );
				seatStatus[pointLocation - 1].push_back ( agentID );
				seatStatusName[pointLocation - 1].push_back ( passengerName );
				fout << " : Seat Reserved" << endl; 
				tempBuff. append ( " : Seat Reserved");
				ticketResults. push_back ( tempBuff );
				return 1;
			}
		}
	case 2:
		{
			for ( int iBuff = 0; iBuff < seatStatus. size(); iBuff++ )
			{
				if ( ( seatStatus[iBuff][0] == flight ) && ( seatStatus[iBuff][1] == row ) && ( seatStatus[iBuff][2] == column ) )
				{
					count++;
					fout << " : Seat already reserved or ticketed" << endl;
					tempBuff. append ( " : Seat already reserved or ticketed");
					ticketResults. push_back ( tempBuff );
					return 0;
				}
			}
			if ( count == 0 )
			{
				seatStatus. push_back( vector<int>() );
				seatStatusName. push_back( vector<string>() );

				int pointLocation = seatStatus. size ();
				seatStatus[pointLocation - 1].push_back ( flight );
				seatStatus[pointLocation - 1].push_back ( row );
				seatStatus[pointLocation - 1].push_back ( column );
				seatStatus[pointLocation - 1].push_back ( type );
				seatStatus[pointLocation - 1].push_back ( agentID );
				seatStatusName[pointLocation - 1].push_back ( passengerName );
				fout << " : Seat Ticketed" << endl;
				tempBuff. append ( " : Seat Ticketed");
				ticketResults. push_back ( tempBuff );
				return 1;
			}
		}
		case 3:
		{
			//cout << type <<"type"<< flight <<"flight"<< row <<"row"<< column <<"column"<< agentID <<"agentID"<< passengerName <<"passengerName"<< endl;
			for ( int iBuff = 0; iBuff < seatStatus. size(); iBuff++ )
			{
				if ( ( seatStatus[iBuff][0] == flight ) && ( seatStatus[iBuff][1] == row ) && ( seatStatus[iBuff][2] == column ) && ( seatStatusName[iBuff][0] == passengerName) )
				{
					count++;
					seatStatus[iBuff][3] = 0;
					fout << " : Cancellation Done" << endl;
					tempBuff. append ( " : Cancellation Done");
					ticketResults. push_back ( tempBuff );
					return 1;
				}
			}
			if ( count == 0 )
			{
				fout << " : Ticket Not Reserved or Ticketed" << endl;
				tempBuff. append ( " : Ticket Not Reserved or Ticketed");
				ticketResults. push_back ( tempBuff );
				return 0;
			}
		}
		case 4:
		{
			for ( int iBuff = 0; iBuff < seatStatusName. size(); iBuff++ )
			{
				if ( ( seatStatusName[iBuff][0] == passengerName ) && ( seatStatus[iBuff][4] == agentID ) )
				{
					count++;
					switch ( seatStatus[iBuff][3] )
					{
					case 1:
						{
							fout << "Seat [" << seatStatus[iBuff][1] << "*" << seatStatus[iBuff][2] << "] has been reserved for " << passengerName << " in Flight : ";
							fout << seatStatus[iBuff][0] << " by Agent : " << seatStatus[iBuff][4] << endl;
							tempBuff. append ( " : Seat [");
							tempBuff. append ( SSTR( seatStatus[iBuff][1] ) );
							tempBuff. append ( "*");
							tempBuff. append ( SSTR( seatStatus[iBuff][2] ) );
							tempBuff. append ( "] has been reserved for " );
							tempBuff. append ( "in Flight : " );
							tempBuff. append ( SSTR( seatStatus[iBuff][0] ) );
							tempBuff. append ( " by Agent : " );
							tempBuff. append ( SSTR( seatStatus[iBuff][4] ) );
							ticketResults. push_back ( tempBuff );
							return 1;
						}
					case 2:
						{
							fout << "Seat [" << seatStatus[iBuff][1] << "*" << seatStatus[iBuff][2] << "] has been ticketed for " << passengerName << " in Flight : ";
							fout << seatStatus[iBuff][0] << " by Agent : " << seatStatus[iBuff][4] << endl;
							tempBuff. append ( " : Seat [");
							tempBuff. append ( SSTR( seatStatus[iBuff][1] ) );
							tempBuff. append ( "*");
							tempBuff. append ( SSTR( seatStatus[iBuff][2] ) );
							tempBuff. append ( "] has been ticketed" );
							tempBuff. append ( " in Flight : " );
							tempBuff. append ( SSTR( seatStatus[iBuff][0] ) );
							tempBuff. append ( " by Agent : " );
							tempBuff. append ( SSTR( seatStatus[iBuff][4] ) );
							ticketResults. push_back ( tempBuff );
							return 1;
						}
					case 0:
						{
							fout << "Seat [" << seatStatus[iBuff][1] << "*" << seatStatus[iBuff][2] << "] had been reserved/ticketed for " << passengerName << " in Flight : ";
							fout << seatStatus[iBuff][0] << " by Agent : " << seatStatus[iBuff][4] << " and now cancelled" << endl;
							tempBuff. append ( " : Seat [");
							tempBuff. append ( SSTR( seatStatus[iBuff][1] ) );
							tempBuff. append ( "*");
							tempBuff. append ( SSTR( seatStatus[iBuff][2] ) );
							tempBuff. append ( "] had been reserved/ticketed" );
							tempBuff. append ( " in Flight : " );
							tempBuff. append ( SSTR( seatStatus[iBuff][0] ) );
							tempBuff. append ( " by Agent : " );
							tempBuff. append ( SSTR( seatStatus[iBuff][4] ) );
							tempBuff. append ( " and now cancelled" );
							ticketResults. push_back ( tempBuff );
							return 1;						
						}
					}
				}
			}
			if ( count == 0 )
			{
				fout << "No Ticket has been ticketed or reserved on the Passenger Name in any Flights " << endl;
				tempBuff. append ( " : No Ticket has been ticketed or reserved on this Name in any Flights " );
				ticketResults. push_back ( tempBuff );
				return 0;
			}
		}
	}
		
}

/*****************************************************************/
//Function Name : processData
//Function Defn : For processing the input obtained from clients
/*****************************************************************/
string processData ( string tempBuffer )
{
	fout << endl << endl << "For the following Request : " << endl << tempBuffer << endl;
	vector < string > tempRequestString;
	string temp;
	stringstream s ( tempBuffer );
	while ( s >> temp )
	{
		tempRequestString. push_back ( temp );
	}

	int agentID, delayTime, FlightID, requestType, headCount;

	if ( tempRequestString[3] == "reserve" ) requestType = 1;
	else if ( tempRequestString[3] == "ticket" ) requestType = 2;
	else if ( tempRequestString[3] == "cancel" ) requestType = 3;
	else requestType = 4;
	
	int sendCount = 0;
	switch ( requestType )
	{
		case 1:
		{
			fout << "Request Type : reserve" << endl;
			istringstream ( tempRequestString[1] ) >> agentID; 
			fout << "Agent ID     : " << agentID << endl;
			istringstream ( tempRequestString[4] ) >> FlightID; 
			fout << "Request to Reserve ticket at Flight " << FlightID << endl;
			istringstream ( tempRequestString[2] ) >> delayTime; 
			istringstream ( tempRequestString[5] ) >> headCount; 
			sleep( delayTime );
			ticketResults. erase(ticketResults.begin(), ticketResults.end());
			for ( int iBuff = 6; iBuff < tempRequestString. size(); iBuff = iBuff + 2 )
			{				
				fout << "seat " << tempRequestString[iBuff] << " requested for Passenger " << tempRequestString[iBuff + 1 ] << " to be reserved" ;
				string tempBuff; 
				tempBuff. append ( "Seat " ); tempBuff. append ( tempRequestString[iBuff] ); tempBuff. append ( " Passenger " );tempBuff. append ( tempRequestString[iBuff + 1 ] );
				if ( tempRequestString[iBuff]. length() == 2 )
				{
					int columnNumber, rowNumber; string tmpColumnNumber, tmpRowNumber; 
					tmpColumnNumber = tempRequestString[iBuff].at (tempRequestString[iBuff]. length() -1);
					columnNumber = convertSeatNumber (tmpColumnNumber);
					string temp; int CountBuff = 0;
					stringstream s ( tempRequestString[iBuff] );
					while ( s >> temp )
					{
						if ( CountBuff < 2 )
						{
							tmpRowNumber. append ( temp ); 							
						}	
						CountBuff++;
					}
					istringstream ( tmpRowNumber ) >> rowNumber;
					int sendCount1 = checkSeat ( requestType, FlightID, rowNumber, columnNumber, agentID, tempRequestString[iBuff + 1 ], tempBuff );
				}
				else if ( tempRequestString[iBuff]. length() == 3 )
				{
					int columnNumber, rowNumber; string tmpColumnNumber, tmpRowNumber; 
					tmpColumnNumber = tempRequestString[iBuff].at (tempRequestString[iBuff]. length() -1);
					columnNumber = convertSeatNumber (tmpColumnNumber);
					string temp; int CountBuff = 0;
					stringstream s ( tempRequestString[iBuff] );
					while ( s >> temp )
					{
						if ( CountBuff < 3 )
							tmpRowNumber. append ( temp ); 
						CountBuff++;
					}
					istringstream ( tmpRowNumber ) >> rowNumber;
					int sendCount1 = checkSeat ( requestType, FlightID, rowNumber, columnNumber, agentID, tempRequestString[iBuff + 1 ], tempBuff );
				}
				else
				{
					fout << " : Seat Details not available in the Flight" << endl;
				}
			}
			break;
		}
		case 2:
		{
			fout << "Request Type : ticket" << endl;
			istringstream ( tempRequestString[1] ) >> agentID; 
			fout << "Agent ID     : " << agentID << endl;
			istringstream ( tempRequestString[4] ) >> FlightID; 
			fout << "Request to Book ticket at Flight " << FlightID << endl;
			istringstream ( tempRequestString[2] ) >> delayTime; 
			istringstream ( tempRequestString[5] ) >> headCount; 
			sleep( delayTime );
			ticketResults. erase(ticketResults.begin(), ticketResults.end());
			for ( int iBuff = 6; iBuff < tempRequestString. size(); iBuff = iBuff + 2 )
			{				
				fout << "seat " << tempRequestString[iBuff] << " requested for Passenger " << tempRequestString[iBuff + 1 ] << " to be ticketed" ;
				string tempBuff; 
				tempBuff. append ( "Seat " ); tempBuff. append ( tempRequestString[iBuff] ); tempBuff. append ( " requested for Passenger " );tempBuff. append ( tempRequestString[iBuff + 1 ] );
				if ( tempRequestString[iBuff]. length() == 2 )
				{
					int columnNumber, rowNumber; string tmpColumnNumber, tmpRowNumber; 
					tmpColumnNumber = tempRequestString[iBuff].at (tempRequestString[iBuff]. length() -1);
					columnNumber = convertSeatNumber (tmpColumnNumber);
					string temp; int CountBuff = 0;
					stringstream s ( tempRequestString[iBuff] );
					while ( s >> temp )
					{
						if ( CountBuff < 2 )
						{
							tmpRowNumber. append ( temp ); 							
						}	
						CountBuff++;
					}
					istringstream ( tmpRowNumber ) >> rowNumber;
					sendCount = checkSeat ( requestType, FlightID, rowNumber, columnNumber, agentID, tempRequestString[iBuff + 1 ], tempBuff );
				}
				else if ( tempRequestString[iBuff]. length() == 3 )
				{
					int columnNumber, rowNumber; string tmpColumnNumber, tmpRowNumber; 
					tmpColumnNumber = tempRequestString[iBuff].at (tempRequestString[iBuff]. length() -1);
					columnNumber = convertSeatNumber (tmpColumnNumber);
					string temp; int CountBuff = 0;
					stringstream s ( tempRequestString[iBuff] );
					while ( s >> temp )
					{
						if ( CountBuff < 3 )
							tmpRowNumber. append ( temp ); 
						CountBuff++;
					}
					istringstream ( tmpRowNumber ) >> rowNumber;
					sendCount = checkSeat ( requestType, FlightID, rowNumber, columnNumber, agentID, tempRequestString[iBuff + 1 ], tempBuff );
				}
				else
				{
					fout << " : Seat Details not available in the Flight" << endl;
				}
			}	
			break;
		}
		case 3:
		{
			fout << "Request Type : cancel" << endl;
			istringstream ( tempRequestString[1] ) >> agentID; 
			fout << "Agent ID     : " << agentID << endl;
			istringstream ( tempRequestString[4] ) >> FlightID; 
			fout << "Request to Cancel ticket at Flight " << FlightID << endl;
			istringstream ( tempRequestString[2] ) >> delayTime; 
			istringstream ( tempRequestString[5] ) >> headCount; 
			sleep( delayTime );
			ticketResults. erase(ticketResults.begin(), ticketResults.end());
			for ( int iBuff = 6; iBuff < tempRequestString. size(); iBuff = iBuff + 2 )
			{				
				fout << "seat " << tempRequestString[iBuff] << " requested for Passenger " << tempRequestString[iBuff + 1 ] << " to be cancelled" ;
				string tempBuff; 
				tempBuff. append ( "Seat " ); tempBuff. append ( tempRequestString[iBuff] ); tempBuff. append ( " Passenger " );tempBuff. append ( tempRequestString[iBuff + 1 ] );
				if ( tempRequestString[iBuff]. length() == 2 )
				{
					int columnNumber, rowNumber; string tmpColumnNumber, tmpRowNumber; 
					tmpColumnNumber = tempRequestString[iBuff].at (tempRequestString[iBuff]. length() -1);
					columnNumber = convertSeatNumber (tmpColumnNumber);
					string temp; int CountBuff = 0;
					stringstream s ( tempRequestString[iBuff] );
					while ( s >> temp )
					{
						if ( CountBuff < 2 )
						{
							tmpRowNumber. append ( temp ); 							
						}	
						CountBuff++;
					}
					istringstream ( tmpRowNumber ) >> rowNumber;
					sendCount = checkSeat ( requestType, FlightID, rowNumber, columnNumber, agentID, tempRequestString[iBuff + 1 ], tempBuff );
				}
				else if ( tempRequestString[iBuff]. length() == 3 )
				{
					int columnNumber, rowNumber; string tmpColumnNumber, tmpRowNumber; 
					tmpColumnNumber = tempRequestString[iBuff].at (tempRequestString[iBuff]. length() -1);
					columnNumber = convertSeatNumber (tmpColumnNumber);
					string temp; int CountBuff = 0;
					stringstream s ( tempRequestString[iBuff] );
					while ( s >> temp )
					{
						if ( CountBuff < 3 )
							tmpRowNumber. append ( temp ); 
						CountBuff++;
					}
					istringstream ( tmpRowNumber ) >> rowNumber;
					sendCount = checkSeat ( requestType, FlightID, rowNumber, columnNumber, agentID, tempRequestString[iBuff + 1 ], tempBuff );
				}
				else
				{
					fout << " : Seat Details not available in the Flight" << endl;
				}
			}
			break;
		}
		case 4:
		{
			fout << "Request Type : check_passenger" << endl;
			istringstream ( tempRequestString[1] ) >> agentID; 
			fout << "Agent ID      : " << agentID << endl;
			istringstream ( tempRequestString[2] ) >> delayTime; 
			sleep ( delayTime );
			fout << "Passenger Name: " << tempRequestString[4] << endl;
			ticketResults. erase(ticketResults.begin(), ticketResults.end());
			string tempBuff; 
			tempBuff. append ( "Passenger " ); tempBuff. append ( tempRequestString[4] );
			sendCount = checkSeat ( requestType, 0, 0, 0, agentID, tempRequestString[4], tempBuff );
			break;
		}
	}

	string tempBuff;
	for ( int iBuff = 0; iBuff < ticketResults.size(); iBuff++ )
	{	tempBuff. append( ticketResults[iBuff] ); tempBuff. append("\n"); }

	return tempBuff;
}

/*****************************************************************/
//Function Name : printOPFromFileAfter
//Function Defn : For printing the intermediatory results
/*****************************************************************/
int printOPFromFileAfter ()
{
 
 fout << endl << endl << "*********  Flight Plan After Requests being Processed  *********" << endl << endl;
 
 for ( int iBuff = 0; iBuff < intBuff; iBuff++ )
 {
	fout << "Flight Number " ;
 	for ( int jBuff = 0; jBuff < flightPlan[iBuff]. size(); jBuff++ )
	{	fout << flightPlan[iBuff][jBuff] << " "; 	}
	fout << endl;
	if ( iBuff +1 != intBuff ) if ( flightPlan[iBuff][0] !=  flightPlan[iBuff + 1][0] ) { fout << endl; }
 } 
 
 fout << endl;
 fout << "*****************************************" << endl;
 fout << "NOTE : 0 represents the un-occupied seats" << endl;
 fout << "*****************************************" << endl;
 fout << endl << endl;
 
}

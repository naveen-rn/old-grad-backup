/* user defined header files */
#include "TextParseClient.h"
#include "ClientSocket.h"
#include "SocketException.h"

using namespace std;

/* global declaration */
int numOfFlights;
int numOfAgents;
ifstream infile;
ofstream fout;

/* initializing the process variables */
int child;
pid_t pids[2];

/* initializing the input vector */
vector <string> buffVectorA;
vector <string> requestVector;

int main ( int argc, int argv[] )
{
	system("clear");
	getIPFromFile (); 			/* get the IP from the input.txt file */
	
	cout << endl << "-----------------------------------------------------------------------------------\n";
	cout << endl << "--------         Client Portal for Airline Ticket Reservation             ---------\n";
	cout << endl << "-----------------------------------------------------------------------------------\n";

	for( int i = 0; i < numOfAgents; i++)
	{
		pids[i] = fork();
		child = i;
		if(pids[i] == 0)	break;
	}
	
    if(pids[child] == 0) // fork was successful
    {
        if(child == 0) // child process
        {
			for ( int iBuff = 0; iBuff < 4; iBuff++ ) 
			{
				try
				{
					ClientSocket client_socket ( "localhost", 30000 );
					string reply;
					try
					{
						client_socket << requestVector[iBuff];
						client_socket >> reply;
					}catch ( SocketException& ) {}
					cout << endl << "---------------------------------------------------------" ;
					cout << endl << "For the Following request:" << endl << requestVector[iBuff] << endl;
					cout << "---------------------------------------------------------" << endl;
					cout << "We received this response from the server:" << endl << reply << endl ;;
				}catch ( SocketException& e )
				{
					cout << "Exception was caught:" << e.description() << "\n";
					break;
				}
			}
		}
		else // parent process
		{
			for ( int iBuff = 4 * child; iBuff < (4 * child ) + 4; iBuff++ ) 
			{
				try
				{
					ClientSocket client_socket ( "localhost", 30000 );
					string reply;
					try
					{
						client_socket << requestVector[iBuff];
						client_socket >> reply;
					}catch ( SocketException& ) {}
					cout << endl << "---------------------------------------------------------" ;
					cout << endl << "For the Following request:" << endl << requestVector[iBuff] << endl;
					cout << "---------------------------------------------------------" << endl;
					cout << "We received this response from the server:" << endl << reply << endl ;;
					if ( iBuff == ( numOfAgents *4 )-1)
					{
						client_socket << "quit";
					}
				}catch ( SocketException& e )
				{
					cout << "Exception was caught:" << e.description() << "\n";
					break;
				}
			}		
		}
	}	

	return 0;
}

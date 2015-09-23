/* user defined header files */
#include "TextParseServer.h"
#include "ServerSocket.h"
#include "SocketException.h"

using namespace std;

/* global declaration */
int numOfFlights;
int numOfAgents;
ifstream infile;
ofstream fout;
string tempString;

int main ( int argc, int argv[] )
{
	system("clear");
	getIPFromFile (); 			/* get the IP from the input.txt file */
	arrangeIPUserFormat (); 	/* arranging the IP in the user format */
	printOPFromFileBefore ();			/* print the Output in the output.txt file */
	cout << "running server...." << endl << "keep the server running while processing the request" << endl;
	try
    {
		ServerSocket server ( 30000 );
		while ( true )
		{
			ServerSocket new_sock;
			server.accept ( new_sock );
			try
			{
				while ( true )
				{
					std::string data;
					new_sock >> data;
					tempString = data;
					data.clear();
					if( tempString == "quit" ) 
					{
						//printOPFromFileAfter ();
						sleep(5);
						return 0;
					}
					else
					{
						string temp = processData ( tempString );			/* sending data for processing */
						sleep(1); 
						new_sock << temp;
					}
				}
			}catch ( SocketException& ) {}
		}
    }
	catch ( SocketException& e )
    {
		cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

	return 0;
}

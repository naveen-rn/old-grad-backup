OnlineReservtion
================

Online Flight Ticket Reservation including Client Server Communication using Sockets

--------------------------------------------------------------
AIRLINE TICKET RESERVATION AND BOOKING - Socket Implementation
--------------------------------------------------------------
--------------------------------------------------------------



There are 17 set of files in the Naveen-Namashivayam-hw3.zip document.

Please follow the following steps to execute and verify the assignment 3 results.


EXECUTION PROCEDURES:
-------------------------------------------------
The following execution procedures, directly clears all unwanted files, compiles and then directly execute the process


1. Extract all the files from the Naveen-Namashivayam-hw3 folder and then enter the directory where all the extracted files are available

2. To execute the program we have to open two terminals/consoles - one for the server and the other for client

3. Use the following command in the first terminal

4. Execute the following sets of commands in the first terminal
   $make all
   $./server
   
5. Now the server program is started in this terminal

6. Let the server be running on this terminal and now open a new terminal

7. This new terminal is going to be the client window

8. Go to the directory where all the files are extracted previously from the Naveen-Namashivayam-hw3

9. Execute the following command and the client will automatically start communicating with the server
   $./client


CLEAR FILES PROCEDURES:
-------------------------------------------------
These clear procedures are already a part of the execution make command. These are just additional features.

1. To clear all unwanted dump files, use 
   $make clean


OUTPUT VERIFICATION:
-------------------------------------------------

How to understand the output?
The output of each request will be obtained in the Client Window and we candirectly look at the status of each Ticket reservation

Is there any other way to find the ouput?
All the Output results are also available in the output.txt file. It gives the result of the communication between server and the client

How to understand the request sent from the Client?
The request are text parsed and then sent to the Server. The single parsed request is in the following format

Agent <ID> <delay time> <request type - reserve/ticket/cancel/status> <ticket details name and seat number list>
Agent 2 1 ticket 1115 8 1A A2 1B B2 5C C2 19D D2 11A E2 15B F2 2C G2 16D H2

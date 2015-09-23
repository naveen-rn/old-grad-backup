/**********************************************************************************************************/
/*Author : Naveen Namashivayam UHID : 1266872*/
/*Dated  : 27-Oct-2013*/
/*Virtual Memory Manager with paged Segments*/
/**********************************************************************************************************/
#include <iostream>
#include <sys/ipc.h>

/* user defined header files */
#include "txtParse.h"

void sem_wait(int semid) 
{
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -1; 
	sb.sem_flg = 0;
	semop(semid, &sb, 1);
}

void sem_signal(int semid) 
{
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = 1; 
	sb.sem_flg = 0;
	semop(semid, &sb, 1);
}
 
/*****************************************************************/
//Function Name : main
//Function Defn : The main function, which defines all the other fn
/*****************************************************************/
int main()
{
 getIPFromFile (); /* getting input from the input.txt file */
 prntOut ();	   /* printing the obatined and the processed output file */
 system("clear");
 int algoValue = getAlgoValue(); /* choosing the Algorithm to be used for the Page Fault Calculation */
 switch(algoValue)
 {
	case 1: { FIFO(); break; } /* calling FIFO Algorithm */
	case 2: { LIFO(); break; } /* calling LIFO Algorithm */
	case 3: { LRU(); break; }  /* calling LRU Algorithm */
	case 4: { MFU(); break; }  /* calling MFU Algorithm */
	case 5: { RANDOM(); break; } /* calling RANDOM Algorithm */
	case 6: { wrkSet(); break; } /* calling Working Set Algorithm */
 }
 return 0;
}

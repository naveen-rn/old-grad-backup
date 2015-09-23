/* Page Fault Calculation Using RANDOM Algorithm */

/* General header files */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>

/* User specific Header files */
#include "txtParse.h"

using namespace std;

/* declaring Input and Output Files */
#define INPUTFILENAME "input.txt"
#define OUTPUTFILENAME "pagefault.txt"

/* fucntion defileIPitions for improper Algorithm Selection */
int LIFO()
{
 cout << "Please read the README file and execute the proper Page Fault Algorithm" << endl;
 cout << "You have compiled only RANDOM !!!" << endl;
 return 0;
}

int FIFO()
{
 cout << "Please read the README file and execute the proper Page Fault Algorithm" << endl;
 cout << "You have compiled only RANDOM !!!" << endl;
 return 0;
}

int LRU()
{
 cout << "Please read the README file and execute the proper Page Fault Algorithm" << endl;
 cout << "You have compiled only RANDOM !!!" << endl;
 return 0;
}

int MFU()
{
 cout << "Please read the README file and execute the proper Page Fault Algorithm" << endl;
 cout << "You have compiled only RANDOM !!!" << endl;
 return 0;
}

int wrkSet()
{
 cout << "Please read the README file and execute the proper Page Fault Algorithm" << endl;
 cout << "You have compiled only RANDOM !!!" << endl;
 return 0;
}

/* shareed memory declaration */ 
struct iRequest *DT1;
struct diskRequest *DT2;
struct diskRequest *DT3;
int sharedMemID1;
int sharedMemID2;
int sharedMemID3;

/* semaphore declaration */
int semaphoreID1;
int semaphoreID2;
int semaphoreID3;
int semaphoreID4;
int semaphoreID5;
int semaphoreID6;

/* process defileIPition */
int child;
pid_t pids[2];

/* queue for calculating the pagefaults */
processQueue pQueue[3];

int RANDOM()
{
	fstream fileIP;
    fileIP.open (INPUTFILENAME);
    ofstream fileOP(OUTPUTFILENAME);
    vector <numPageFramesDisk> vecFramesOnDisk;
    numPageFramesDisk pageOnDisk;
	
	string tempString;
	char ch;
	int randomNumber;
	
	int numberOfPageFrames, maximumSegmentLength, TotalNumberPageFramesPerProcess, TotalNumOfProcess;
	bool bufferFlag = false;

	vector <request> vecRequest;
	request req;

	cout << "Have a look at the following Files :" << endl ;
	cout << "Processed Input Details   --------> output.txt" << endl;
	cout << "Page Fault Details        --------> pagefault.txt" << endl;

	fileOP << "*******************************************************" << endl;
	fileOP << "Page Fault Calculation - RANDOM Algorithm Used" << endl;
	fileOP << "*******************************************************" << endl;
 	while(!fileIP.eof())
	{
	    fileIP >> numberOfPageFrames;     
		fileIP >> maximumSegmentLength; 
		int SizeOfPage;
		fileIP >> SizeOfPage;  
		fileIP >> TotalNumberPageFramesPerProcess;
		int min;
		fileIP >> min;
		int max;
		fileIP >> max;
		fileIP >> TotalNumOfProcess;
		
		/* creating Frames */
		for(int i = 0; i < TotalNumOfProcess; i++)
		{
			fileIP >> pageOnDisk.pid >> pageOnDisk.size;
			vecFramesOnDisk.push_back(pageOnDisk);
		}

		/* getting the page size value from the given input file */
		while(!fileIP.eof())
		{
			fileIP.get(ch);
			if(bufferFlag)
			{ 
				if(ch == ' ')
				{
					req.pid = atoi(tempString.c_str());
					tempString.clear();
				}
				else if ( (ch == '\n') || (fileIP.eof()) )
				{
					if(tempString.size() == 0 || tempString.size() == 2 || tempString.size() == 4 || tempString.size() == 5)
					{
						req.logicalAddress = tempString;
						vecRequest.push_back(req);
					}
					tempString.clear();
				}
				else
				{
					tempString.push_back(ch);
				}
			}
			bufferFlag = true;
		}		
	}

	/* creating separate process */
	for(int i = 0; i < TotalNumOfProcess; i++)
	{
		pids[i] = fork();
		child = i;
		if(pids[i] == 0)	break;
	}
	    
	/* allocating shared memory */
	sharedMemID1 = shmget(1111, sizeof(struct iRequest), IPC_CREAT | 0666);
	DT1 = (struct iRequest*)shmat(sharedMemID1, (void*) 0, 0);
	sharedMemID2 = shmget(101, 1024, IPC_CREAT | 0666);
	DT2 = (struct diskRequest*)shmat(sharedMemID2, (void*) 0, 0);
	sharedMemID3 = shmget(102, 1024, IPC_CREAT | 0666);
	DT3 = (struct diskRequest*)shmat(sharedMemID3, (void*) 0, 0);
	
	if( (sharedMemID1 == -1) || (sharedMemID2 == -1) || (sharedMemID3 == -1) )
	{        exit(1);	}
	if( (!DT1) || (!DT2) || (!DT3) ) 
	{        exit(1);	}
	
	/* creating semaphores */
	semaphoreID1 = semget(300, 1, IPC_CREAT | 0666);
	semaphoreID2 = semget(301, 1, IPC_CREAT | 0666);
    semaphoreID3 = semget(302, 1, IPC_CREAT | 0666);
    semaphoreID4 = semget(303, 1, IPC_CREAT | 0666);
    semaphoreID5 = semget(304, 1, IPC_CREAT | 0666);
    semaphoreID6 = semget(304, 1, IPC_CREAT | 0666);

	if( (semaphoreID1 == -1) || (semaphoreID2 == -1) || (semaphoreID3 == -1) || (semaphoreID4 == -1) || (semaphoreID5 == -1) || (semaphoreID6 == -1) )
	{		exit(1);    }
    	
	if(pids[child] == 0)
	{
		if(child == 0)
		{	
			vector <Frames> vecFrames;
			vector <DPT> vecDPT;
			vector <DPT> vecD;

			vecFrames.resize(numberOfPageFrames);
			Frames f;
			
			DPT d;
			
			diskRequest tempDiskReq;
			
			bool bFound = false;
			int *numPageFault = new int[TotalNumOfProcess];
			
			int iBuff = 1;			
			do
			{
				pQueue[iBuff-1].pid = vecFramesOnDisk[iBuff-1].pid;
				iBuff++;
			}while( iBuff <= TotalNumOfProcess );
		    
			DT1->logAddress[2]=1;//setting up arbitary value initially	
		    while(DT1->logAddress[2])
			{
				sem_wait(semaphoreID1);
				for(int iBuff = 0; iBuff < TotalNumOfProcess; iBuff++)
				{   
				    if( pQueue[iBuff].pid == DT1->pid )
					    if ( DT1->logAddress[2] > 0 )
							{
                                fileOP << "process " << pQueue[iBuff].pid << " requests address";
								fileOP << " --> " << DT1->logAddress[2] << " | ";
								if(pQueue[iBuff].page.size() < TotalNumberPageFramesPerProcess)
							    {
								  /* counting the page fault */
                            	  ++pQueue[iBuff].count;
								  
								  /* pushing the incoming page value to the empty frame */
								  pQueue[iBuff].page.push_front(DT1->logAddress[2]);
								  f.pid = tempDiskReq.pid = DT1->pid;  
								  f.pagenum = tempDiskReq.pagenum = DT1->logAddress[2];   f.address = DT1->logAddress;
								  vecFrames.push_back(f);
								  
								  strcpy(tempDiskReq.address,DT1->logAddress);
								  *DT2 = tempDiskReq;
								  d.pid = DT2->pid;
								  
								  /* signalling the completion of the page replacement */
								  sem_signal(semaphoreID3);
								  
								  /* waiting for the new set of requests */
								  sem_wait(semaphoreID4);
								  d.diskAddress = DT2->count;
								  d.pagenum = DT2->pagenum;
								  d.address = DT2->address;
								  vecDPT.push_back(d);
								
								  /* printing the queue list in the file */
  								  int jBuff = 0;
								  do  
								  { 	fileOP << pQueue[iBuff].page[jBuff] << " "; jBuff++;
								  }while(jBuff < pQueue[iBuff].page.size());
								  
								  fileOP << endl;
							  }
							  else
							  {
							      int jBuff = 0;
								  do
								  {
									  /* checking for the presence of page in the system */
									  if(pQueue[iBuff].page.at(jBuff) == DT1->logAddress[2])
									  {
									  	bFound = true;
									  }
									jBuff++;
								  }while( jBuff < pQueue[iBuff].page.size());
								  
								  if(!bFound)
								  {
									  ++pQueue[iBuff].count; 
									  int jBuff = 0;
									  do
									  {
										  if(vecFrames[jBuff].pid == DT1->pid && vecFrames[jBuff].pagenum == pQueue[iBuff].page.front())
										  {
											  vecFrames[jBuff].pagenum = tempDiskReq.pagenum = DT1->logAddress[2]; 
											  vecFrames[jBuff].pid = tempDiskReq.pid = DT1->pid;
											  vecFrames[jBuff].address = DT1->logAddress;
											  strcpy(tempDiskReq.address,DT1->logAddress);
											  *DT2 = tempDiskReq;
											  d.pid = DT2->pid;
											  d.pagenum = DT2->pagenum; d.diskAddress = DT2->count; d.address = DT2->address;

											  sem_signal(semaphoreID3);
											  sem_wait(semaphoreID4);

											  vecDPT.push_back(d);
										  }
									  jBuff++;
									  }while( jBuff < vecFrames.size() );
									  
									  /* selecting a random number in between the TotalNumberPageFramePerProcess and 1 */
									  randomNumber = rand() %  TotalNumberPageFramesPerProcess;
   								      deque <char> bufferQ;
 									  for ( int jBuff = 0; jBuff < randomNumber; jBuff++ )
									  {
										bufferQ.push_front(pQueue[iBuff].page.back());
										pQueue[iBuff].page.pop_back();                  
										pQueue[iBuff].page.push_front(DT1->logAddress[2]);
                                      }
									  for ( int jBuff = 0; jBuff < TotalNumberPageFramesPerProcess - (randomNumber); jBuff++ )
									  {
										bufferQ.push_back(pQueue[iBuff].page.back());
										pQueue[iBuff].page.pop_back();                  
										pQueue[iBuff].page.push_front(DT1->logAddress[2]);
                                      }
									  bufferQ.pop_front();
									  bufferQ.push_front(DT1->logAddress[2]);
									  pQueue[iBuff].page = bufferQ;
									  bufferQ.clear();
									  
                                  }
								  
								  bFound = false;
								  
								  int kBuff = 0;
								  //cout << randomNumber << "|" ; 
								  do
								  {
									fileOP << pQueue[iBuff].page[kBuff] << " "; kBuff++;
									//cout << pQueue[iBuff].page[kBuff] << " "; kBuff++;
								  }while(kBuff < pQueue[iBuff].page.size());
								  
								  fileOP << endl;//cout << endl;
							  }
						  }
						  numPageFault[iBuff] = pQueue[iBuff].count;
					}
				
               sem_signal(semaphoreID2);
			}
			    {
				fileOP << "*******************************************************" << endl;
				fileOP << "Total Number of Page Faults in each Process:" << endl;
				fileOP << "*******************************************************" << endl;
				cout <<  endl << "*******************************************************" << endl;
				cout << "Total Number of Page Faults in each Process:" << endl;
				cout << "*******************************************************" << endl;
				}
			
			for(int jBuff = 0; jBuff < TotalNumOfProcess; jBuff++)
			{
				fileOP << "Process " << pQueue[jBuff].pid;
				cout << "Process " << pQueue[jBuff].pid;
				fileOP << " Page Faults Obtained " << pQueue[jBuff].count << endl;
				cout << " Page Faults Obtained " << pQueue[jBuff].count << endl;
			}
		}
	
		if(child == 1)
		{
			int count  = 0;
			diskRequest dreq;
			diskRequest pageDisk;
			
			while(count < 50)
			{
				sem_wait(semaphoreID3);			
				pageDisk.pid = DT2->pid;
				pageDisk.pagenum = DT2->pagenum;
				strcpy(pageDisk.address, DT2->address);				
				*DT3 = pageDisk;				
				sem_signal(semaphoreID5);
				
				sem_wait(semaphoreID6);				
				dreq.pid = DT3->pid;
				dreq.count = DT3->count;
				dreq.pagenum = DT3->pagenum;
				strcpy(dreq.address, DT3->address);				
				*DT2 = pageDisk;
				sem_signal(semaphoreID4);

				count++;				

			}
		}
	
		if(child == 2)
		
		{
			diskRequest dReq;
			int count = 0;
			
			while(count < 30)
			{
				sem_wait(semaphoreID5);
				dReq.count = count;
				dReq.pagenum = DT3 -> pagenum;
				dReq.pid = DT3 -> pid;
				strcpy(dReq.address, DT3 -> address);
				*DT3 = dReq;
				sem_signal(semaphoreID6);

				count++;
			}
		}
	}
	else
	{
		struct iRequest r;
		for( int iBuff = 1; iBuff < vecRequest.size(); iBuff++)
		{
			r.logAddress[0] = '\0';
			r.logAddress[1] = '\0';
			r.logAddress[2] = '\0';
			r.logAddress[3] = '\0';
			r.logAddress[4] = '\0';
			if(vecRequest[iBuff].logicalAddress.compare("-1") != 0)
			{	
				r.pid = vecRequest[iBuff].pid;
				int jBuff = 0;
				do
				{
					r.logAddress[jBuff] = vecRequest[iBuff].logicalAddress[jBuff];
					jBuff++;
				}while ( jBuff < vecRequest[iBuff].logicalAddress.size() );
			}
			*DT1 = r;
			sem_signal(semaphoreID1);
			sem_wait(semaphoreID2);
		}	
	}
	
	/* freeing up disk space used */
	shmctl(sharedMemID1, IPC_RMID, 0);
	shmctl(sharedMemID2, IPC_RMID, 0);
	shmctl(sharedMemID3, IPC_RMID, 0);
	
	/* free the created semaphores */
	semctl(semaphoreID1, 0, IPC_RMID, 0);
	semctl(semaphoreID2, 0, IPC_RMID, 0);
	semctl(semaphoreID3, 0, IPC_RMID, 0);
	semctl(semaphoreID4, 0, IPC_RMID, 0);
	semctl(semaphoreID5, 0, IPC_RMID, 0);
	semctl(semaphoreID6, 0, IPC_RMID, 0);
	return 0;

}

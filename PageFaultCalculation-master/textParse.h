#include <deque>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

/* Function Definition :
 * getIPFromFile is used to obtain the input data from the input.txt file and
 * the obtained values are stored in the vector for further processing
 */
 int getIPFromFile();
 
 
 
/* Function Definition :
 * prntOut is used to display the obtained and the processed input
 * all the requests are processed and then placed in the respective process 
 * vector, now the requests are grouped together
 */
 int prntOut();
 
 
 
/* Function Definition :
 * getAlgoValue is used to obtain the input data from the user; regarding the 
 * Algorithm to be used for the Page Fault Calculation
 */
 int getAlgoValue();
 
 
 
/* Function Definition :
 * FIFO First In First Out Algorithm And page Fault Calculation
 */
 int FIFO();

 
 
 /* Function Definition :
 * LIFO Last In First Out Algorithm And page Fault Calculation*/
 int LIFO();
 
 
 
 
/* Function Definition :
 * LRU Least Recently Used Algorithm And page Fault Calculation
 */
 int LRU();
 
 
 
 
/* Function Definition :
 * MFU Most Frequently Used Algorithm And page Fault Calculation
 */
 int MFU();
 
 
 
 
/* Function Definition :
 * RANDOM Algorithm And page Fault Calculation
 */
 int RANDOM();
 
 
 
/* Function Definition :
 * Working Set Algorithm And page Fault Calculation
 */
 int wrkSet();
 
/* Semaphore Declaration */
 void sem_wait(int semid);
 void sem_signal(int semid1);  
/* Structure Declaration:
 * Structures declared to be used in other functions 
 */ 
struct Frames
{	int pid; char pagenum; string address; };

struct DPT
{	int pid;	int diskAddress;	char pagenum;	string address; };

typedef struct 
{	int pid;	int size;	}numPageFramesDisk;

struct request
{	int pid;	string logicalAddress;	};

struct iRequest
{	int pid;	char logAddress[5]; };

struct diskRequest
{	int pid;	char pagenum;		int count;		char address[5];	};

typedef struct
{   int pid;    deque <char> page;  int count; }processQueue;

/*
 * example program to check matrix multiplication with 
 * pthreads parallel computation
 * arrays used are representing a a(1 * N) and b(N * 1) with final 
 * result stored in c(1 * 1)
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <pthread.h>

#define NUM_THREADS 10
#define classB 1000

using namespace std;

vector < vector < int > >matrixA;
vector < vector < int > >matrixB;
vector < vector < int > >matrixC;
int arraysize;
pthread_t threads[NUM_THREADS];

int
arraySizeCalculation ()
{
    return classB;
}

int
selectClassType ()
{
  return arraySizeCalculation ();
}

void
assignValues ()
{
  for (int i = 0; i < arraysize; i++)
    {
      matrixA.push_back (vector < int >());
      matrixB.push_back (vector < int >());
      matrixC.push_back (vector < int >());
    }

  for (int i = 0; i < arraysize; i++)
    for (int j = 0; j < arraysize; j++)
      {
	matrixA[i].push_back (1);
	matrixB[i].push_back (1);
	matrixC[i].push_back (0);
      }
}

int
resultVerification ()
{
  int count = 0;
  for (int i = 0; i < arraysize; i++)
    for (int j = 0; j < arraysize; j++)
      if (matrixC[i][j] == arraysize)
	count++;
  return count;
}

void
finalResultDisplay (time_t start, time_t end, int result)
{
  if (result == 1)
    {
      double totalTime = difftime (end, start);
      cout << "Matrix Multiplication Successfully Completed" << endl;
      cout << "Total time : " << totalTime << endl;
    }
  else
    {
      cout << "Matrix Multiplication Failed" << endl;
    }
}

void
*matrixMultiplication (void *threadID)
{
  long tid = (long) threadID;
  int start, end, range;

  range = arraysize/NUM_THREADS;
  if (tid == 0)
  {
  	start = 0;
  	end = range;
  }
  else
  {
  	start = (range*tid);
  	end = (range*(tid+1));
  }

  for (int i = start; i < end; i++)
    {
      for (int j = 0; j < arraysize; j++)
	{
	  int sum = 0;
	  for (int k = 0; k < arraysize; k++)
	    {
	      matrixC[i][j] = matrixC[i][j] + (matrixA[i][k] * matrixB[k][j]);
	    }
	}
    }
   
}

int
main (int argc, char *argv[])
{
  arraysize = selectClassType ();
  time_t start, end;
  double totalTime;
 // pthread_t threads[NUM_THREADS];

  assignValues ();


  /*
   * multiplication logic starts here
   */
  time (&start);
  long threadID;
  for (threadID = 0; threadID < NUM_THREADS; threadID++)
    pthread_create (&threads[threadID], NULL, matrixMultiplication,
		    (void *) threadID);

  for(threadID = 0; threadID < NUM_THREADS; threadID++)
    pthread_join (threads[threadID], NULL);

  time (&end);
  /*
   * multiplication logic ends here
   */

  int count = resultVerification ();

  if (count == (arraysize * arraysize))
    finalResultDisplay (start, end, 1);
  else
    finalResultDisplay (start, end, 0);

  pthread_exit(0);
  return 0;
}


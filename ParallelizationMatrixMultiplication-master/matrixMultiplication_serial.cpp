/*
 * example program to check matrix multiplication with 
 * pthreads parallel computation
 * arrays used are representing a a(1 * N) and b(N * 1) with final 
 * result stored in c(1 * 1)
 */

# include <stdio.h>
# include <iostream>
# include <algorithm>
# include <ctime>
# include <vector>

# define classB 1000

using namespace std;

int arraySizeCalculation()
{
	return classB;
}

int selectClassType()
{
	return arraySizeCalculation();
}

void finalResultDisplay(time_t start, time_t end, int result)
{
	if ( result == 1 )
	{
		double totalTime = difftime(end, start);
		cout << "Matrix Multiplication Successfully Completed" << endl;
		cout << "Total time : " << totalTime << endl;
	}	
	else
	{
		cout << "Matrix Multiplication Failed" << endl;
	}
}

int main()
{
	int arraysize = selectClassType();
	vector < vector<int> > matricA;
	vector < vector<int> > matricB;
	vector < vector<int> > matricC;
	time_t start,end;
	double totalTime;

	for(int i=0;i<arraysize;i++)
	{
		matricA.push_back(vector<int>());
		matricB.push_back(vector<int>());
		matricC.push_back(vector<int>());
	}	   

	for(int i=0; i<arraysize; i++)
		for(int j=0; j<arraysize; j++)
		{
			matricA[i].push_back(1);
			matricB[i].push_back(1);
			matricC[i].push_back(0);
		}	   

	time (&start);
	for(int i = 0; i < arraysize; i++)
	{
		for(int j = 0; j < arraysize; j++)
		{
			for(int k = 0; k < arraysize; k++)
			{
				matricC[i][j] = matricC[i][j] + (matricA[i][k] * matricB[k][j]);
			}
		}
	}	
	time (&end);

	int count = 0;
	for(int i = 0; i < arraysize; i++)
		for(int j = 0; j < arraysize; j++)
			if(matricC[i][j] == arraysize)
				count++;

	if(count == (arraysize*arraysize))
		finalResultDisplay(start, end, 1);
	else
		finalResultDisplay(start, end, 0);
	return 0;
}

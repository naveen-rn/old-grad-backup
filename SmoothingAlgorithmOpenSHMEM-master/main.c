/*
 *
 * Copyright (c) 2011 - 2013
 *   University of Houston System and Oak Ridge National Laboratory.
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * o Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 
 * o Neither the name of the University of Houston System, Oak Ridge
 *   National Laboratory nor the names of its contributors may be used to
 *   endorse or promote products derived from this software without specific
 *   prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */



/*
 * get on PE 0 (master) from PE 1, but with a non-symmetric variable
 */

/*
 *Smoothing Algorithm Implementation in OpenSHMEM
 */
 
/*
 *OpenSHMEM is an effort to create a specification for a standardized API for parallel programming in the 
  Partitioned Global Address Space. Along with the specification the project is also creating a reference
  implementation of the API. This implementation attempts to be portable, to allow it to be deployed in 
  multiple environments, and to be a starting point for implementations targeted to particular hardware 
  platforms.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <shmem.h>
#include <time.h>

/* some constants */
#define FILTERHEIGHT 5
#define FILTERWIDTH  5
#define SEGMENTS     5
#define ITERATIONS   10

/* some prototupes */
void allocate_2D_int_matrix (int ***matrix, int dim0, int dim1);
void free_2D_int_matrix (int ***matrix);
void gray_erode(int **img, int height, int width, int filterheight, int filterwidth, int iterations, int pixrange, int localheight, int heightoffset ); 
void update_ghostcells ( int **buffer, int height, int width, int fhlimit, int localheight, int heightoffset );

/* shmem init variables */
int rank, size;

/* variables for calculating the time */
double wtime, wtime1, wtime2;
struct timeval start, end;
double t;

/* main function */
int main(int argc, char **argv) 
{
  int localheight=0;	
  int realheight=0;	
  int height, width,i, j, k, heightoffset;
  int **labels=NULL;
  FILE *fpa;

  /* initializing shmem values */
  start_pes (0);
  size = _num_pes ();
  rank = _my_pe ();

  /* determining inputs */
  if (argc != 5 ) {
    printf("usage: %s <inputfile> <outputfile> <height> <width>\n", argv[0]);
    exit(0);
  }
  height = atoi ( argv[3]);
  width  = atoi ( argv[4]); 

  /* creating symmetric memory */
  labels = (int **) shmalloc (height*sizeof(int *));
  for ( i = 0; i < height; i++ )
  { labels[i] = (int*) shmalloc (width*sizeof(int*)); }  

  allocate_2D_int_matrix ( &labels, height, width );

  /* reading from the input file */  
  if ( rank == 0 )
  {
  fpa = fopen ( argv[1], "rb");
  fread ( &(labels[0][0]), sizeof(int), height*width, fpa);
  fclose ( fpa );
  }
  
  /* datapartitioning between the processes */
  localheight = height/size;
  realheight  = localheight + 4 ;
  heightoffset = 2;
  if ( rank == 0 ) {
           realheight -= 2 ;
           heightoffset = 0;
  }
  if ( rank == (size -1) )  {
           realheight -= 2;
  }
  
  shmem_barrier_all ();
  /* distributing input datum to all the symmetric variables */
  for ( i=1; i<size; i++ ) {
    if ( rank == i )
   	    if ( shmem_addr_accessible(&labels[0][0], 0)) {
            if ( rank == ( size -1 ) ) { k = 0; } else { k = 2; }
	    for ( j = 0; j < localheight+k; j++ ) {
		    shmem_int_get(&labels[j+heightoffset][0], &labels[j+(localheight*rank)][0], width, 0);
		}
	}
	else { printf("Not_accessible_Error_00"); }
  } 

  /* gray erode calculation */
  shmem_barrier_all();
  gettimeofday(&start, NULL);
  gray_erode(labels, height, width, FILTERHEIGHT,FILTERWIDTH, ITERATIONS, SEGMENTS, localheight, heightoffset );
  gettimeofday(&end, NULL);
  
  /* calculating and displaying time taken */
  if( rank == 0 ) 
  {
	    t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000.0;
		printf("Total Time%f \n",t); 
  } 
  
  /* transferring datum back to root */
  shmem_barrier_all ();
  for ( k = 0; k < size; k++){ 
    if ( rank == k ) {
		for ( i = 0; i < localheight; i++ ) { 
			shmem_int_put(&labels[i+(localheight*rank)][0], &labels[i+heightoffset][0], width, 0);
		} 
	}
  }
  	
  shmem_barrier_all ();
  /* creating output file */
  if(rank == 0)	{
    fpa = fopen ( argv[2], "wb");
    fwrite( &(labels[0][0]), sizeof(int), height*width, fpa );	
    fclose( fpa );
  }
  
  free_2D_int_matrix ( &labels);
  return 0;
}
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
void gray_erode(int **img, int height /*realheight*/, int width, int filterheight,
		int filterwidth, int iterations, int pixrange, int localheight, int heightoffset ) 
{
    int maxlabel=0;
    int fh, fw, iters, pixval=0, i, j, s;
    int fhlimit = filterheight/2;
    int fwlimit = filterwidth/2;
    int **smoothedlabels;
    int* labeltemp;
    int realheight;

    allocate_2D_int_matrix ( &smoothedlabels, height, width );
    
    realheight  = localheight + 4 ;
    if ( rank == 0 ) {
            realheight -= 2 ;
    }
    if ( rank == (size -1) )  {
             realheight -= 2;
    }
   
    height = realheight;

    for (i=heightoffset; i<heightoffset+localheight; i++)
	for (j=0; j<width; j++)
	    smoothedlabels[i][j] = img[i][j];

    labeltemp = (int*)malloc(sizeof(int) * pixrange);
    for (s=0; s<pixrange; s++)
	labeltemp[s] = 0;

    
  for (iters=0; iters<iterations; iters++)  {
	    /* update ghost cells first */
	    update_ghostcells ( img, height, width, fhlimit, localheight, heightoffset );
	    shmem_barrier_all();
	for (i=fhlimit; i<height-fhlimit; i++) {
	    for (j=fwlimit; j<width-fwlimit; j++)  {

		for (fh=-fhlimit; fh<=fhlimit; fh++) {
		    for (fw=-fwlimit; fw<=fwlimit; fw++)   {
			labeltemp[img[i+fh][j+fw]]++;
		    }
		}
		for (s=0; s<pixrange; s++) {
		    if (labeltemp[s]>maxlabel) {
			maxlabel = labeltemp[s];
			pixval = s;
		    }
		}
		smoothedlabels[i][j]=pixval;

		for (s=0; s<pixrange; s++)
		    labeltemp[s] = 0;
		maxlabel = 0;
	    }// End of Width Loop
	}// End of Height Loop
    
	for (i=heightoffset; i<heightoffset + localheight; i++)
	    for (j=0; j<width; j++)
		img[i][j] = smoothedlabels[i][j];	

    }

    free_2D_int_matrix ( &smoothedlabels );
    free(labeltemp);
    return;
}
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
void allocate_2D_int_matrix (int ***matrix, int dim0, int dim1)
{
  int i;
  int ** tmp_field0;
  int *data;

  data = (int *) shmalloc(dim0*dim1*sizeof(int));
  if (data == NULL ) {
      printf("%d @ %s, Could not allocate memory\n",  __LINE__,__FILE__);
      return;
  }

  tmp_field0 = (int **) shmalloc (dim0*sizeof(int *));
  if (tmp_field0 == NULL ) {
      printf("%d @ %s, Could not allocate memory\n",  __LINE__,__FILE__);
      return;
  }
  for (i=0; i<dim0; i++) {
    tmp_field0[i] = &(data[i*dim1]);
  }

  *matrix=tmp_field0;
  return;
}
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
void free_2D_int_matrix (int ***matrix)
{
  int *matrix_tmp0;
  int **matrix_tmp1;

  matrix_tmp0=**matrix;
  matrix_tmp1=*matrix;

  shfree(matrix_tmp0);
  shfree(matrix_tmp1);

  *matrix=NULL;
  return;
}
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
void update_ghostcells ( int **buffer, int height, int width, int fhlimit,int localheight, int heightoffset )
{

    int i, j, k;

    shmem_barrier_all() ;   

    if ( size < 2 ) {
        /* Nothing to be done */
        return;
    }

    if ( rank != 0 ) {
	if ( shmem_addr_accessible(&buffer[0][0], rank-1)) {	
	    if ( (rank - 1 ) == 0 )	
	    { for ( i = 0; i < 2; i++ ) shmem_int_get ( &(buffer[i][0]), &(buffer[i+(localheight-2)][0]), width, rank-1); }
	    else {
 	      for ( i = 0; i < 2; i++ ) shmem_int_get ( &(buffer[i][0]), &(buffer[i+(localheight)][0]), width, rank-1); } } 
	else {
	    printf("Not_Accessible_Error_01"); }
	
	if ( shmem_addr_accessible(&buffer[0][0], rank-1)) {
	    if ( (rank - 1 ) == 0 )
	    { for ( i = 0; i < 2; i++ ) shmem_int_put ( &(buffer[i+(localheight)][0]), &(buffer[i+heightoffset][0]), width, rank-1); }
	    else {
	      for ( i = 0; i < 2; i++ ) shmem_int_put ( &(buffer[i+(localheight)+2][0]), &(buffer[i+heightoffset][0]), width, rank-1); } }
        else {
	    printf("Not_Accessible_Error_02"); }
    }

    shmem_barrier_all ();
    return;
}
  

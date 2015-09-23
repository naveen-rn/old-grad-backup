# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <shmem.h>

# define SIZE 8000

/* shmem init variables */
int rank, size;
long pSync[_SHMEM_BCAST_SYNC_SIZE];

int main ( void );
void jacobi ( int n, double a[], double b[], double x[], double x_old[] );
void r8vec_uniform_01 ( int n, int *seed, double r[] );

/******************************************************************************/

int main ( void )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for JACOBI.
*/
{
  double *a;
  double *b;
  int i;
  int j;
  int n = SIZE;
  double row_sum;
  int seed;
  double *x;
  double *x_old;
    
  /* initializing shmem values */
  start_pes (0);
  size = _num_pes ();
  rank = _my_pe ();

  a = ( double * ) shmalloc ( n * n * sizeof ( double ) );
  b = ( double * ) shmalloc ( n * sizeof ( double ) );
  x = ( double * ) shmalloc ( n * sizeof ( double ) );
  x_old = ( double * ) shmalloc ( n * sizeof ( double ) );

  if ( rank == 0 )
  {
  printf ( "\n" );
  printf ( "JACOBI\n" );
  printf ( "  C version\n" );
  printf ( "  Problem size N = %d\n", n );
  }
  
  seed = 123456789;

  r8vec_uniform_01 ( n * n, &seed, a );

  for ( i = 0; i < n; i++ )
  {
    row_sum = 0.0;
    for ( j = 0; j < n; j++ )
    {
      row_sum = row_sum + fabs ( a[i+j*n] );
    }
    a[i+i*n] = 1.0 + 2.0 * row_sum;
  }

  for ( i = 0; i < n; i++ )
  {
    x[i] = ( double ) ( i + 1 );
  }

  for ( i = 0; i < n; i++ )
  {
    b[i] = 0.0;
    for ( j = 0; j < n; j++ )
    {
      b[i] = b[i] + a[i+j*n] * x[j];
    }
  }

  shmem_barrier_all();
  r8vec_uniform_01 ( n, &seed, x );

  shmem_barrier_all();
  jacobi ( n, a, b, x, x_old );

  shfree ( a );
  shfree ( b );
  shfree ( x );
  shfree ( x_old );

  return 0;
}
/******************************************************************************/

void jacobi ( int n, double a[], double b[], double x[], double x_old[] )

/******************************************************************************/
/*
  Purpose:

    JACOBI carries out the Jacobi iteration.
*/
{
  double axi;
  double diff;
  double diff_tol;
  int i;
  int it;
  int it_max = 100;
  int j;
  double r8_epsilon = 1.0E-14;
  double wtime;
  double wtime1;
  double wtime2;
  struct timeval start, end;
  double t;
  int local_i, local_j, local_n;

  if ( size > 1 )
  {
	if ( size % 2 != 1 )
	{
		local_n = n/size;
		local_i = rank * local_n;
		local_j = ( rank * local_n ) + local_n;
		printf("rank %d local_n %d local_i %d local_j %d \n", rank, local_n, local_i, local_j);  
	}
	else
	{
		if ( rank == 0 ){
	    printf ( "\n Fatal Error : Feed a Proper Node numbers \n");
		return;}
	}
  }
  else
  {
	local_n = n;
	local_i = rank * local_n;
	local_j = ( rank * local_n ) + local_n;
  }
 
  for (i = 0; i < _SHMEM_BCAST_SYNC_SIZE; i += 1)
  {
    pSync[i] = _SHMEM_SYNC_VALUE;
  }
  
  diff_tol = 0.0;
  for ( i = 0; i < n; i++ )
  {
    diff_tol = diff_tol + fabs ( b[i] );
  }
  diff_tol = ( diff_tol + 1.0 ) * r8_epsilon;
  
  gettimeofday(&start, NULL);
  
  for ( it = 1; it <= it_max; it++ )
  {
	if ( rank == 0 )
	{
	  for ( i = 0; i < n; i++ )
	  {
       x_old[i] = x[i];
	  }
	}
	
	for ( i = 1; i < size; i++ )
	{
	  if ( i == rank ){
	  for ( j = 0; j < n; j ++ )
	  shmem_double_get ( &x_old[j], &x_old[j], 1, 0); }
	}
	
    for ( i = local_i; i < local_j; i++ )
    {
      axi = 0.0;
      for ( j = 0; j < n; j++ )
      {
        axi = axi + a[i+j*n] * x_old[j];
      }
      x[i] = x_old[i] + ( b[i] - axi ) / a[i+i*n];
	  if ( rank != 0 )
	  { 
		if ( shmem_addr_accessible(&x[i], 0) )
		{  shmem_double_put ( &x[i], &x[i], 1, 0);
		}
		else
		{  printf("x not accessible \n:"); }
	  }
	}

	if ( rank == 0 )
	{
		diff = 0.0;
		for ( i = 0; i < n; i++ )
		{
			diff = diff + fabs ( x[i] - x_old[i] );
		}

		printf ( "  %8d  %14e\n", it, diff );

		if ( diff <= diff_tol )
		{
		break;
		}
	}
	
  }

  
  if ( rank == 0 )
  {
	gettimeofday(&end, NULL);
	t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000.0;

	printf ( "\n" );
	printf ( "DIFF     = %e\n", diff );
	printf ( "DIFF_TOL = %e\n", diff_tol );
	printf ( "TIME     = %f s\n", t);

	printf ( "\n" );
	printf ( "  First 10 elements of estimated solution:\n" );
	printf ( "\n" );

	for ( i = 0; i < 10; i++ )
	{
		printf ( "  %8d  %14f\n", i, x[i] );
	}
   }

  return;
}
/******************************************************************************/

void r8vec_uniform_01 ( int n, int *seed, double r[] )

/******************************************************************************/
/*
  Purpose:

    R8VEC_UNIFORM_01 returns a unit pseudorandom vector.

  Parameters:

    Input, int N, the number of entries in the vector.

    Input/output, int *SEED, a seed for the random number generator.

    Output, double R[N], the vector of pseudorandom values.
*/
{
  int i;
  int i4_huge = 2147483647;
  int k;

  if ( *seed == 0 )
  {
    printf ( "\n" );
    printf ( "R8VEC_UNIFORM_01 - Fatal error!\n" );
    printf ( "  Input value of SEED = 0.\n" );
    exit ( 1 );
  }

  for ( i = 0; i < n; i++ )
  {
    k = *seed / 127773;

    *seed = 16807 * ( *seed - k * 127773 ) - k * 2836;

    if ( *seed < 0 )
    {
      *seed = *seed + i4_huge;
    }

    r[i] = ( double ) ( *seed ) * 4.656612875E-10;
  }

  return;
}


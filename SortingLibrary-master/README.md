Sorting Library

A simple sorting library with various sorting algorithms implemented using various parallel programming models.

Available programming models :
serial
OpenMPI
OpenMP
OpenSHMEM

currently the various algorithms included are:

1. selection sort
2. bubble sort
3. insertion sort
4. merge sort
5. heap sort
6. quick sort
7. bucket sort
8. shell sort

How to use the MakeFile in the test directory:

make serial(default)|omp|mpi|shmem SORT=sel(default)|bubble|insert|merge|heap|quick|bucket|shell 

--> will generate a simple executable to demonstrate and verify the sorting, no performance is considered

make serial(default)|omp|mpi|shmem SORT=sel(default)|bubble|insert|merge|heap|quick|bucket|shell CLASS=A(default)|B|C PERFORMANCE=ON|OFF

--> will generate a executable to demonstrate and verify the sorting for various sizes of CLASS to check its performance


SIZE description:

CLASS A = 100
CLASS B = 1000
CLASS C = 4000

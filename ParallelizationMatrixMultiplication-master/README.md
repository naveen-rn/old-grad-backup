This is a 2dimensional matrix multiplication example. 
Both the serial and the parallel version are provided.

The parallel version is obtained using pthreads.

This source code is not to check the level of optimization. Only the matrix multiplication computation
part is optimized. This is to check how a pthread can be used to achive optimization.


make all 
make ser
make par

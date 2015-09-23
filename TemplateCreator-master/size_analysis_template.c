#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#ifndef DOS
#include <sys/time.h>
#endif

const size_t MAX_MSG_SIZE = 4*1024*1024;
const int TIMEOUT         = 5;
const int NITER           = 1000;

double 
get_Wtime()
{
    double t;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    t = (tv.tv_sec*1000000LL + tv.tv_usec)/1000000.0;
    return t;
}

void run_tests();

int
main(int argc, char **argv)
{
    run_tests();
    return 0;
}

void
run_tests()
{
    double start, stop;
    size_t nsize;
    int *target;
    const size_t MAX_BLKSIZE = MAX_MSG_SIZE / (sizeof *target);

    printf("%20s %20s %20s\n", "blksize", "nrep", "customize_result");
    for (nsize = 1;nsize <= MAX_BLKSIZE; nsize = nsize*2) {
        int i;
        int nrep = NITER;

        start = get_Wtime(); 
        for (i = 0; i < nrep; i++) {
            /*
             * perform some function
             */
            if ( (i % 10 == 0) && (get_Wtime() - start) > TIMEOUT) {
                nrep = i;
            }
        }
        stop = get_Wtime();

        printf("%20ld %20ld %17.3f \n", 
                (long)nsize, (long)nrep, 1000000*(stop-start)/nrep);
    }
}


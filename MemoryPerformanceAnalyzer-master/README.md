MemoryPerformanceAnalyzer
=========================

A performance analysis benchmark code for various memory calls like memcpy, malloc and page segmentation

To run this benchmark, please follow the step:

For testing memcpy:
    make VERIFY=VERIFY MEMCPY_ALG=<NATIVE|NAIVE|> memcpy
    ./memcpy.o

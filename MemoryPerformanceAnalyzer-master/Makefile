CC=gcc
VERIFY?=
MEMCPY_ALG?=NATIVE
CC_OPT=-Ofast -march=native

memcpy:
ifeq ($(VERIFY), VERIFY)
	$(CC) -D$(VERIFY) -D$(MEMCPY_ALG) $(CC_OPT) src/analyze/memcpy_analyze.c src/lib/memcpy_lib.c -o memcpy.o
else
	$(CC) -D$(MEMCPY_ALG) $(CC_OPT) src/analyze/memcpy_analyze.c src/lib/memcpy_lib.c -o memcpy.o
endif

clean:
	rm -rf *.o

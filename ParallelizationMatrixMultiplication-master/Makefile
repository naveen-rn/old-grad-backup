CC = g++
CFLAGS_SERIAL = -w
CFLAGS_PARALL = -w -lpthread

#serial run
all: clean ser par

ser:
	clear
	$(CC) $(CFLAGS_SERIAL) -o serial matrixMultiplication_serial.cpp
	
par:
	clear
	$(CC) $(CFLAGS_PARALL) -o parallel matrixMultiplication_parallel.cpp

clean:
	rm -f *.o *.out serial parallel 



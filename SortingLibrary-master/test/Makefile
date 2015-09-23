CC=g++
CFLAG=-c -Wall

CLASS ?=A
SORT ?=sel
PERFORMANCE ?=OFF

COMMON =../src/common/sort_general.h
SERIAL =../src/serial/sorting.h

all: serial

serial: serial.o
	$(CC) serial_test.o -o serial.out

ifeq ($(PERFORMANCE), ON)
serial.o:serial_test.cpp
	$(CC) $(CFLAG) -DCLASS$(CLASS) -DPERFORMANCE -D$(SORT) serial_test.cpp $(COMMON) $(SERIAL)
else
serial.o:serial_test.cpp
	$(CC) $(CFLAG) -D$(SORT) serial_test.cpp $(COMMON) $(SERIAL)
endif

clean:
	rm *.o *.out *.txt

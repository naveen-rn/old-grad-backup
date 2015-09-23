# Makefile for Page Fault Calculation using Virtual Memory Manager

# *****************************************************

CC = g++
CFLAGS = -w

# ****************************************************
#creating the executable file and executing the pgm
# ****************************************************

#FIFO algorithm
FIFO:
	-rm outFIFO output.txt pagefault.txt;
	-clear;  
	$(CC) $(CFLAGS) -o outFIFO main.cpp txtParse.cpp FIFO.cpp; ./outFIFO

#LIFO algorithm
LIFO:
	-rm outLIFO output.txt pagefault.txt;
	-clear; 
	$(CC) $(CFLAGS) -o outLIFO main.cpp txtParse.cpp LIFO.cpp; ./outLIFO

#LRU algorithm	
LRU:
	-rm outLRU output.txt pagefault.txt;
	-clear; 
	$(CC) $(CFLAGS) -o outLRU main.cpp txtParse.cpp LRU.cpp; ./outLRU

#MFU algorithm	
MFU:
	-rm outMFU output.txt pagefault.txt;
	-clear;
	$(CC) $(CFLAGS) -o outMFU main.cpp txtParse.cpp MFU.cpp; ./outMFU

#Random algorithm	
RAND:
	-rm outRAND output.txt pagefault.txt;
	-clear; 
	$(CC) $(CFLAGS) -o outRAND main.cpp txtParse.cpp RANDOM.cpp; ./outRAND

#WS algorithm	
WS:
	-rm outWS output.txt pagefault.txt;
	-clear; 
	$(CC) $(CFLAGS) -o outWS main.cpp txtParse.cpp wrkSet.cpp; ./outWS

# ****************************************************
# clearing all the executable files
# ****************************************************

clearall:
	-rm outFIFO outLIFO outLRU outMFU outRAND outWS;
	-rm output.txt pagefault.txt;
	-clear

clearFIFO:
	-rm outFIFO output.txt pagefault.txt;
	-clear
	
clearLIFO: 
	-rm outLIFO output.txt pagefault.txt;
	-clear

clearLRU: main.cpp txtParse.cpp LRU.cpp
	-rm outLRU output.txt pagefault.txt;
	-clear
	
clearMFU: main.cpp txtParse.cpp MFU.cpp
	-rm outMFU output.txt pagefault.txt;
	-clear
	
clearRAND: main.cpp txtParse.cpp RANDOM.cpp
	-rm outRAND output.txt pagefault.txt;
	-clear
	
clearWS: main.cpp txtParse.cpp wrkSet.cpp
	-rm outWS output.txt pagefault.txt;	
	-clear
	
# ****************************************************

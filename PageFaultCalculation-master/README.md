pageFaultCalculation
====================

Page Fault Calculation using 6 Paging Algorithms FIFO, LIFO, LRU, MFU, RANDOM and 
Working Set involving semaphores and Process management


-------------------------------------------------
VIRTUAL MEMORY MANAGER - Page Fault Calculation
-------------------------------------------------
-------------------------------------------------



There are 11 set of files in the Naveen-Namashivayam-hw2 document.

Please follow the following steps to execute and verify the various Page Replacement Algorithms.


EXECUTION PROCEDURES:
-------------------------------------------------
The following execution procedures, directly clears all unwanted files, compiles and then directly execute the algorithm


1. Extract all the files from the Naveen-Namashivayam-hw2 folder and then enter the directory

2. To execute the specific algorithm use the following make commands

3. To execute FIFO, use
   $make FIFO

4. To execute LIFO, use
   $make LIFO

5. To execute LRU, use
   $make LRU

6. To execute MFU, use
   $make MFU

7. To execute RANDOM, use
   $make RAND

8. To execute Working Set, use
   $make WS

9. Finally to clear all the unwanted files, use
   $make clearall


CLEAR FILES PROCEDURES:
-------------------------------------------------
These clear procedures are already a part of the execution make command. These are just additional features.

1. To clear all unwanted dump files, use 
   $make clearall

2. To clear all files related to FIFO, use  	
   $make clearFIFO

3. To clear all files related to LIFO, use  	
   $make clearLIFO

4. To clear all files related to LRU, use  	
   $make clearLRU

5. To clear all files related to MFU, use  	
   $make clearMFU

6. To clear all files related to RANDOM, use  	
   $make clearRAND

7. To clear all files related to Working set, use  	
   $make clearWS


OUTPUT VERIFICATION:
-------------------------------------------------
There will be two sets of output files generated after each algorithm execution.
The two files are:
1. output.txt
2. pagefaultcalculation.txt

what does 'output.txt' file have ?
This file contains the parsed input file with the requests separated as per the process ID and other basic input details

what does 'pagefaultcalculation.txt' file have ?
The pagefaultcalculation.txt contains the step by step page replacement results of the algorithm and the final Page Fault Count


How to read the pagefaultcalculation.txt file ? 
This file gives the detailed step by step Page Fault Calculations.
The results will be provided in the following format;

process <processID for process-1> requests the page <page number> -> <page number> | <frame 1> <frame 2> <frame 3> .....<total frames>
process <processID for process-2> requests the page <page number> -> <page number> | <frame 1> <frame 2> <frame 3> .....<total frames>
process <processID for process-3> requests the page <page number> -> <page number> | <frame 1> <frame 2> <frame 3> .....<total frames>
: 	:	: 	: 	: 	:	:	:	:	:	:	:	:	:	:	:	:	:
: 	:	: 	: 	: 	:	:	:	:	:	:	:	:	:	:	:	:	:
: 	:	: 	: 	: 	:	:	:	:	:	:	:	:	:	:	:	:	:
: 	:	: 	: 	: 	:	:	:	:	:	:	:	:	:	:	:	:	:
: 	:	: 	: 	: 	:	:	:	:	:	:	:	:	:	:	:	:	:
: 	:	: 	: 	: 	:	:	:	:	:	:	:	:	:	:	:	:	:
process <processID for process-n> requests the page <page number> -> <page number> | <frame 1> <frame 2> <frame 3> .....<total frames>


Based on the page replacement the final page fault count will be displayed.


How are the page numbers specified?
The requests are denoted behind the | pipe-delimites

How the Page replacements shown?
For every process there is a separate calculation and each of the replacements are made as per the incoming requests

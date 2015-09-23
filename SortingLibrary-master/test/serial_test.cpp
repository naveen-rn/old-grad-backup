#include <iostream>
#include <stdio.h>  /* printf */
#include <fstream>  /* file open close */
#include <stdlib.h> /* rand() */
#include <string>
#include "../src/common/sort_general.h"
#include "../src/serial/sorting.h"

/*
 * size declaration for performance analysis
 */
#ifdef CLASSA
#define SIZE 1000
#elif CLASSB
#define SIZE 10000
#elif CLASSC
#define SIZE 40000
#else
#define SIZE 5
#endif

using namespace std;

double start, end, total;
int input_unsorted_array[SIZE];
int input_array_size = SIZE;

void
setting_input_file()
{
    ofstream input_file;
    input_file.open("input.txt");
    for (int buffer = 0; buffer < SIZE; buffer++) {
        input_file << rand() % ((1000+buffer) + (10000+buffer)) << endl;
    }
    input_file.close();
}

void
reading_input_file()
{
    string line;
    int count = 0;
    ifstream read_ip_file("input.txt");
    if (read_ip_file.is_open()) {
        while (getline(read_ip_file, line)) {
            int temp = atoi(line.c_str());
            input_unsorted_array[count] = temp; 
            count++;
        }
        read_ip_file.close();
    } else {
    }
}

void
setting_input_array()
{
    input_unsorted_array[0] = 64;
    input_unsorted_array[1] = 25;
    input_unsorted_array[2] = 12;
    input_unsorted_array[3] = 22;
    input_unsorted_array[4] = 11;
}

void
start_sorting(string sort_type)
{
    sort_general<int> srt_gen;
    cout << "sorting started : " << sort_type << endl;
#ifdef PERFORMANCE
    reading_input_file ();
    start = srt_gen.timer();
#else
    cout << "The unsorted array" << endl;
    setting_input_array();
    srt_gen.print(input_unsorted_array, input_array_size);
#endif
}

void
end_sorting()
{
    sort_general<int> srt_gen;
#ifdef PERFORMANCE
    end = srt_gen.timer();
    cout << "sort completed" << endl;
    total = srt_gen.total_time(start, end);
    if (srt_gen.verify(input_unsorted_array, input_array_size)) {
        cout << "Verification successful" << endl;
        printf ( "TOTAL TIME   = %f s\n", total);
    } else {
        cout << "verification unsuccessful" << endl; 
    }
#else
    cout << "The sorted array after sorting" << endl;
    srt_gen.print(input_unsorted_array, input_array_size);
#endif
}

void
sel_sort() 
{
    sorting<int> srt;
    start_sorting("selection sort");
    srt.selection_sort(input_unsorted_array, input_array_size);
    end_sorting();
}

int
main(void)
{
#ifdef PERFORMANCE
    setting_input_file ();
#endif

    /*
     * sorting started
     */
#ifdef sel
    sel_sort();
#endif

    return 0;
}


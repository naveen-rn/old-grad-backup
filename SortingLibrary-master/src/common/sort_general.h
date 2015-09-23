#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

template <class T>
class sort_general
{
public:
    void print(T array[], int array_size);
    bool verify(T array[], int array_size);
    double timer();
    double total_time(double start_time, double end_time);
};

template <class T>
void sort_general<T> :: print(T array[], int array_size) {
    for(int buffer = 0; buffer < array_size; buffer++) {
        cout << array[buffer] << endl;
    }
}

template <class T>
double sort_general<T> :: timer() {
    struct timeval time;
    gettimeofday(&time, NULL);
    double time_current = (double) (time.tv_sec * 1000000 + time.tv_usec);
    return time_current;
}

template <class T>
double sort_general<T> :: total_time(double start, double end) {
    double total = (end - start) / 1000000;
    return total;
}

template <class T>
bool sort_general<T> :: verify(T array[], int array_size) {
    int count = 0;
    for(int buffer = array_size-2; buffer >= 0; buffer--) {
        if (array[buffer] <= array[buffer+1]) {
            count++;
        } else {
            return false;
        }
    }
    
    if (count == array_size-1) {
        return true;
    }

    return false;
}


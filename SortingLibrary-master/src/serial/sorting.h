#include <iostream>

template<class T>
class sorting
{
    public:
        void swap_elements(T *element1, T *element2);
        void selection_sort(T *array, T array_size);
};

template <class T>
void sorting<T> :: swap_elements(T *element1, T *element2) {
    int temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}

template <class T>
void sorting<T> :: selection_sort(T *array, T array_size)
{
    sorting srt;
    int min_idx;
    for (int main_array_buffer = 0; 
            main_array_buffer < array_size-1; 
            main_array_buffer++) {

        min_idx = main_array_buffer;
        for(int sub_array_buffer = main_array_buffer+1; 
                sub_array_buffer < array_size; 
                sub_array_buffer++) {

            if (array[sub_array_buffer] < array[min_idx]) {
                min_idx = sub_array_buffer;
            }
        }

        srt.swap_elements(&array[min_idx], &array[main_array_buffer]);
    }

}


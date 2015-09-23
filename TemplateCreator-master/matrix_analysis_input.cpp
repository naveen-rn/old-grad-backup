/**
 * This program helps to generate a sample input file for testing
 * matrix algorithms. Using this we can generate various types of
 * input file. The various types are:
 * 1. size -> the default size is 100 and user can implictly mention
 *            the size also
 * 2. dimension -> the default dimension is 1 and we can extend till 7
 * 3. input -> the input value is usually random, the user can also
 *            mention the value to be sequential from a particular
 *            starting digit to the ending digit. Or random between a 
 *            limit and also same  sequence.
 */
#include <iostream>
#include <cstdlib>
#include <fstream>

#define DEFAULT_SIZE 100
#define DEFAULT_DIMENSION 2 

using namespace std;

int 
set_size(int size) {
    if (size == DEFAULT_SIZE || size == 0) {
        cout << "Setting the default size as 100" << endl;
        return DEFAULT_SIZE;
    }
    return size;
}

int 
set_dimension(int dimension) {
    if (dimension == 0) {
        cout << "Setting the default dimension as 2" << endl;
        return DEFAULT_DIMENSION;
    }
    return dimension;
}

void
generate_input_file(int size, int dimension) {
    ofstream file;
    file.open("generated_source_file.txt");
 
    for (int i = 0; i < size; i++) {
        file << rand() % (rand() % 100 + 1) << endl;
    }

    file.close();
}

void
setting_input_wrapper(int *input, int input_size)
{
    int size        = set_size(input[0]);
    int dimension   = set_dimension(input[1]);
    generate_input_file(size, dimension);
}

int 
main(int argc, char **argv)
{
    int input[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for(int i = 1; i < argc; i++) {
        input[i-1] = atoi(argv[i]);
    }

    setting_input_wrapper(input, argc);

    return 0;
}

#include "fft.h"
#include <cstdlib>
int main(){
    float* x = (float*)malloc(2 * SQUENCE_LENGTH * sizeof(float));
    generate_test_data(x);
    cl_fft(x);
    return 0;
}
#include "fft.h"
#include <cstdlib>
#include <cstring>
#include <vector>
#include <chrono>
using namespace std::chrono;
#define PRINT_INPUT
#define PRINT_OUTPUT
void test_case(int squence_length, std::vector<int>& decompose_factor, int test_case_num){
    float* ref_x = (float*)malloc(2 * squence_length * sizeof(float));
    float* x = (float*)malloc(2 * squence_length * sizeof(float));
    float* output = (float*)malloc(2 * squence_length * sizeof(float));
    for(int c = 0; c < test_case_num; c++){
        generate_test_data(x, squence_length);
        #ifdef PRINT_INPUT
            printf("input data is\n");
            for(int i = 0; i < squence_length; i++){
                printf("%f + %fi, ", x[2 * i], x[2 * i + 1]);        
            }
            printf("\n");
        #endif
        memcpy(ref_x, x, 2 * squence_length * sizeof(float));
        auto cl_start = high_resolution_clock::now();
        cl_fft(ref_x, squence_length);
        auto cl_stop = high_resolution_clock::now();
        auto sq_start = high_resolution_clock::now();
        squential_fft(squence_length, decompose_factor, (complex_t*)x, (complex_t*)output);
        auto sq_stop = high_resolution_clock::now();
        output = (float*)output;
        x = (float*)x;
        #ifdef PRINT_OUTPUT
            printf("result is: \n");
            for(int i = 0; i < squence_length; i++)
                printf("%d : (%f, %f)\n", i, output[2 * i], output[ 2 * i + 1]);
            printf("correct result is: \n");
            for(int i = 0; i < squence_length; i++)
                printf("%d : (%f, %f)\n", i, ref_x[2 * i], ref_x[ 2 * i + 1]);
        #endif
            int correct_num = check_correctness(output, ref_x, squence_length);
            printf("test case %d correct rate: %d / %d\n", c, correct_num, squence_length);
            auto cl_duration = duration_cast<microseconds>(cl_stop - cl_start);
            auto sq_duration = duration_cast<microseconds>(sq_stop - sq_start);
            printf("test case %d: clfft consumes %ld ms\n", c, cl_duration.count());
            printf("test case %d: naive fft consumes %ld ms\n", c, sq_duration.count());
    }
    free(x);
    free(ref_x);
    free(output);

}
int main(int argc, char** argv){
    if (argc < 3){
        printf("input param error\n");
        return -1;
    }
    std::vector<int> decompose_factor;
    for(int i = 1; i < argc - 1; i++){
        decompose_factor.push_back(atoi(argv[i]));
    }
    int squence_length = 1;
    for(int f = 0; f < decompose_factor.size(); f++){
        squence_length *= decompose_factor[f];
    }
    int test_num = atoi(argv[argc - 1]);
    test_case(squence_length, decompose_factor, test_num);
    return 0;
}
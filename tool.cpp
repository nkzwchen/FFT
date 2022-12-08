#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include "fft.h"

#define RAND() (float(rand()) / float(RAND_MAX)) * float(MAX - MIN) + float(MIN);

void generate_test_data(float* input_data, int squence_length){
    srand((unsigned)time(NULL));
    for(int i = 0; i < 2 * squence_length; i++){
        input_data[i] = RAND();
    }
}

char* read_cl_file(const char* file_name){
    FILE *fp = fopen(file_name, "rb");
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    char* cl_file_buffer = (char*)malloc(filesize);
    fseek(fp, 0, SEEK_SET);
    if(fread(cl_file_buffer, filesize, 1, fp) == 1){
        return cl_file_buffer;
    }
    else{
        printf("fread fail\n");
        free(cl_file_buffer);
        return NULL;
    }
    
}
int abs_error(float a, float b){
    return abs(a - b);
}
int check_correctness(const float* output, const float* ref_output, int squence_length){
    int correct_num = 0;
    for(int i = 0; i < squence_length; i++){
        if((abs_error(output[2 * i], ref_output[2 * i]) < ERROR_TOLERANCE) &&
        (abs_error(output[2 * i + 1], ref_output[2 * i + 1]) < ERROR_TOLERANCE)){
            correct_num += 1;
        }
        // else{
            
        //     // printf("error in %d for output: %.7lf + %.7lf i, ref: %.7lf + %.7lf * i\n", i, output[2 * i], output[2 * i + 1],
        //     // ref_output[2 * i], ref_output[2 * i + 1]);
        // }
            
    }
    return correct_num;
}
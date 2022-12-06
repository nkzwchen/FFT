#ifndef FFT_H
#define MAX 10
#define MIN 0
#define SQUENCE_LENGTH 64
#define TEST_CASE_NUM 1
#define ERROR_TOLERANCE 1e-6

// tool.cpp
void generate_test_data(float* input_data);
char* read_cl_file(const char* file_name);

// cl_fft.cpp
void cl_fft(float* X);
#endif
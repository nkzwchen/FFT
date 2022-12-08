#ifndef FFT_H
#define MAX 1
#define MIN 0
#define ERROR_TOLERANCE 1e-4
#include<vector>
#include<complex>
typedef std::complex<float> complex_t;

// tool.cpp
void generate_test_data(float* input_data, int squence_length);
char* read_cl_file(const char* file_name);
int check_correctness(const float* output, const float* ref_output, int squence_length);

// cl_fft.cpp
void cl_fft(float* X, int squence_length);

// squential_fft.cpp
void squential_fft(int N, std::vector<int>& decompose_factor, complex_t* dataI, complex_t* dataO);
#endif
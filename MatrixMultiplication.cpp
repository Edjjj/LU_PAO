#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

const int m = 1000;
int TIMES_RUN = 10;
float A[m][m], B[m][m], C[m][m] = {};


void print_matrix(const float M[m][m]) {
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j < m; j++) {
			std::cout << (float)M[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void random_matrix(float M[m][m]) {
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j < m; j++) {
			M[i][j] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
		}
	}
}

void basic_mul() {
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int j = 0; j < m; j++) {
			for (unsigned int k = 0; k < m; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}



void inv_cycle() {
	for (unsigned int i = 0; i < m; i++) {
		for (unsigned int k = 0; k < m; k++) {
			for (unsigned int j = 0; j < m; j++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void run_func(void (*func)()) {
	long long unsigned int time = 0;

	for (unsigned int i = 0; i < TIMES_RUN; i++) {
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		(*func)();
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - start).count();

		time += duration;
	}
	
	std::ofstream outfile;
	outfile.open("mul_matrix.results", std::ios_base::app);
	outfile << m << " " << TIMES_RUN << " " << time << "\n";

	std::cout << "Average time elapsed : "<< time / TIMES_RUN << " microseconds" << std::endl;
}

int main()
{

	std::srand(std::time(0));

	random_matrix(A);
	random_matrix(B);

	// print_matrix(A);
	// print_matrix(B);

	//run_func(basic_mul);
	run_func(inv_cycle);

	// print_matrix(C);
}\
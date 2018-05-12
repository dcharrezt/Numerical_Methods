#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

void create_matrix( double** matrix_A, int rows, int cols );
void print_vector( double* vector, int size );
void print_matrix( double** matrix_A, int rows, int cols );

double norm_sum( double* vect, int size);
void jacobi_method( double** matrix_A, int rows, int cols, double* x, 
													int n_iterations);

void gauss_seidel_method( double** matrix_A, int rows, int cols, double* x, 
														int n_iterations );


int main() {

	int rows, cols;
	cin >> rows >> cols;
	
	double** A = new double*[rows];
	for( int i = 0; i < rows; i++ )
		A[i] = new double[cols];

	double* x = new double[rows];

	create_matrix(A, rows, cols);
		
	print_vector(x, rows);
	gauss_seidel_method(A, rows, cols, x, 10);
	// jacobi_method(A, rows, cols, x, 10);
	print_vector(x, rows);

	for (int i = 0; i < rows; ++i)
		delete [] A[i];
	delete [] A;

	delete [] x;

	return 0;
}

void create_matrix( double** matrix_A, int rows, int cols ) {
	for( int i = 0; i < rows; i++ ) {
		for( int j = 0; j < cols; j++ ) {
			cin >> matrix_A[i][j];
		}
	}
}

void print_matrix( double** matrix_A, int rows, int cols ) {
	cout << "\nMatrix of " << rows << " rows and " << cols << " cols\n";
	for( int i = 0; i < rows; i++) {
		for( int j = 0; j < cols; j++ )
			cout << matrix_A[i][j] << ' ';
		cout << endl;
	}	
}

void print_vector( double* vector, int size ) {
	cout << "\nVector of size "<< size << endl;
	for( int i=0; i < size; i++) {
		cout << vector[i] << ' ';
	}
	cout << endl;
}

double norm_sum( double* vect, int size) {
	double s = 0;
	for (int i = 0; i < size; ++i) {
		s+= vect[i];
	}
	return s;
}

double norm_sum(double* vect, int size) {
	double sum = 0.;
	for (int i = 0; i < size; ++i) {
		sum += vect[i];
	}
	return sum;
}

void jacobi_method( double** matrix_A, int rows, int cols, double* x, 
														int n_iterations) {
	int iter = 0;
	double* tmp_x = new double[rows];

	print_matrix(matrix_A, rows, cols);

	while( iter < n_iterations) {
		// cout << "iteration #" << iter << endl;
		// print_vector(x, rows);
		// print_vector(tmp_x, rows);
		for(int i=0; i<rows; i++) {
			tmp_x[i] = 0.;
			for(int j=0; j<rows; j++) {
				if(i != j){
					tmp_x[i] += matrix_A[i][j]*x[j];
				}
			}
			tmp_x[i] = (-tmp_x[i]+matrix_A[i][cols-1])/matrix_A[i][i];
		}
		for (int k = 0; k < rows; ++k) {
			double asd = tmp_x[k];
			x[k] = asd;
		}
		iter++;
	}

	delete [] tmp_x;
}

void gauss_seidel_method( double** matrix_A, int rows, int cols, double* x, 
														int n_iterations ) {
	int iter = 0;
	double tmp = 0.;

	print_matrix(matrix_A, rows, cols);

	while( iter < n_iterations) {
		for(int i=0; i<rows; i++) {
			tmp = 0.;
			for(int j=0; j<rows; j++) {
				if(i != j){
					tmp += matrix_A[i][j]*x[j];
				}
			}
			tmp = (-tmp+matrix_A[i][cols-1])/matrix_A[i][i];
			x[i] = tmp;
		}
		iter++;
		print_vector(x, rows);
	}
}
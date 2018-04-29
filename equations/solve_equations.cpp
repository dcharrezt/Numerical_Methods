#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

// escalona A
// Sust regresiva (An b)
// AX = B
// Met gauss(A, b )
// AX = B
// Ecalona Piv A
// Met Gaus Piv A b
// AX = B

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void create_matrix( double** matrix, int rows, int cols );
void print_matrix( double** matrix, int rows, int cols );
void print_vector( double* vector, int size );


void gauss_elimination( double** matrix, int rows, int cols );
void backward_substitution( double** matrix, int rows, double* x  );
void gauss_method( double** matrix, int rows, int cols, double* x);

void scaled_partial_pivot( double** matrix, int rows, int cols);
void gauss_partial_pivot_method( double** matrix, int rows, int cols, double* x );

int main() {

	int rows, cols;
	cin >> rows >> cols;
	
	double** A = new double*[rows];
	for( int i = 0; i < rows; i++ )
		A[i] = new double[cols];
		
	double* x = new double[rows];
	
	
	gauss_method(A, rows, cols, x);

//	gauss_partial_pivot_method( A, rows, cols, x);
	

	for (int i = 0; i < rows; ++i)
		delete [] A[i];
	delete [] A;
	
	delete [] x;

	return 0;
}

void create_matrix( double** matrix, int rows, int cols ) {
	for( int i = 0; i < rows; i++ ) {
		for( int j = 0; j < cols; j++ ) {
			cin >> matrix[i][j];
		}
	}
}

void print_matrix( double** matrix, int rows, int cols ) {
	cout << "\nMatrix of " << rows << " rows and " << cols << " cols\n";
	for( int i = 0; i < rows; i++) {
		for( int j = 0; j < cols; j++ )
			cout << matrix[i][j] << ' ';
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

void gauss_elimination( double** matrix, int rows, int cols ) {
	for(int k = 0; k < rows-1; k++ ) {
		for( int j = k+1; j < rows; j++ ) {
			matrix[j][k] = matrix[j][k] / matrix[k][k];
			for( int i = k+1; i < cols; i++ )
				matrix[j][i] = matrix[j][i] - matrix[j][k]*matrix[k][i];
			matrix[j][k] = 0;
		}
	}
}
void backward_substitution( double** matrix, int rows, double* x ) {
	double s;
	for(int i = rows-1; i >= 0; i--) {
		s = matrix[i][rows];
		for(int j=i+1; j<rows; j++)
			s -= matrix[i][j]*x[j];
		x[i] = s/matrix[i][i];
	}
}

void gauss_method( double** matrix, int rows, int cols, double* x) {

	create_matrix( matrix, rows, cols);
	print_matrix( matrix, rows, cols);
	
	gauss_elimination( matrix, rows, cols);
	
	print_matrix( matrix, rows, cols);
	
	backward_substitution(matrix, rows, x);

	print_vector( x, rows);
}

void scaled_partial_pivot( double** matrix, int rows, int cols) {

	for(int k = 0; k < rows-1; k++ ) {
	
		double tmp = 0;
		int index_max = 0;
		for(int m=0; m<rows; m++) {
			tmp = MAX( tmp, abs(matrix[m][k]) );
			index_max = m;
		}
		
		
		for(int n=0; n<cols; n++) {
			tmp = matrix[k][n];
			matrix[k][n] = matrix[index_max][n];
			matrix[index_max][n] = tmp;
		}
	
		for( int j = k+1; j < rows; j++ ) {
			matrix[j][k] = matrix[j][k] / matrix[k][k];
			for( int i = k+1; i < cols; i++ )
				matrix[j][i] = matrix[j][i] - matrix[j][k]*matrix[k][i];
			matrix[j][k] = 0;
		}
	}
}

void gauss_partial_pivot_method( double** matrix, int rows, int cols, double* x ) {
	
	create_matrix( matrix, rows, cols);
	print_matrix( matrix, rows, cols);
	
	scaled_partial_pivot( matrix, rows, cols);
	
	print_matrix( matrix, rows, cols);
	
	backward_substitution(matrix, rows, x);

	print_vector( x, rows);
}








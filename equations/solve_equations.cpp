#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

// escalona A
// Sust regresiva (An b)
// AX = B
// Met gauss(A, b )
// AX = B
// Ecalona Piv A
// Met Gaus Piv A b
// AX = B

/* Global Variables */

void print_matrix( double** matrix, int rows, int cols );
void create_matrix( double** matrix, int rows, int cols );


int main() {

	int rows, cols;
	cin >> rows >> cols;
	
	double** matrix = new double*[rows];
	for( int i = 0; i < rows; i++ )
		matrix[i] = new double[cols];
	
	create_matrix( matrix, rows, cols);
	print_matrix( matrix, rows, cols);
	
	



	

	for (int i = 0; i < rows; ++i)
		delete [] matrix[i];
	delete [] matrix;

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









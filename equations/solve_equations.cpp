#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void create_matrix( double** matrix_A, int rows, int cols );
void print_matrix( double** matrix_A, int rows, int cols );
void print_vector( double* vector, int size );


void gauss_elimination( double** matrix_A, int rows, int cols );
void backward_substitution( double** matrix_A, int rows, double* x  );
void gauss_method( double** matrix_A, int rows, int cols, double* x);

void scaled_partial_pivot( double** matrix_A, int rows, int cols);
void gauss_partial_pivot_method( double** matrix_A, int rows, int cols, double* x );

void forward_substitution( double** matrix_A, int rows, double* x  );
void LU_decomposition( double** matrix_A, int rows, int cols, 
												double** L, double* x );
void LU_method( double** matrix_A, int rows, int cols, double* x );

void PLU_descomposition( double** matrix_A, int rows, int cols, double** P);
void PLU_method( double** matrix_A, int rows, int cols, double* x );
// DescompLU(A) "No admite descomposicion" si no hay decom
// ResuelveSistConLU(A, b) AX=B 
// DescompPlu(A) con pv parcial
// ResuelveSistPLU(A, b) 

int main() {

	int rows, cols;
	cin >> rows >> cols;
	
	double** A = new double*[rows];
	for( int i = 0; i < rows; i++ )
		A[i] = new double[cols];
		
	double* x = new double[rows];
	
	PLU_method(A, rows, cols, x);
	// LU_method(A, rows, cols, x);
	// gauss_method(A, rows, cols, x);
	// gauss_partial_pivot_method( A, rows, cols, x);
	

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

void gauss_elimination( double** matrix_A, int rows, int cols ) {
	for(int k = 0; k < rows-1; k++ ) {
		for( int j = k+1; j < rows; j++ ) {
			matrix_A[j][k] = matrix_A[j][k] / matrix_A[k][k];
			for( int i = k+1; i < cols; i++ )
				matrix_A[j][i] = matrix_A[j][i] - matrix_A[j][k]*matrix_A[k][i];
			matrix_A[j][k] = 0;
		}
	}
}

void backward_substitution( double** matrix_A, int rows, double* x ) {
	double s;
	for(int i = rows-1; i >= 0; i--) {
		s = matrix_A[i][rows];
		for(int j=i+1; j<rows; j++)
			s -= matrix_A[i][j]*x[j];
		x[i] = s/matrix_A[i][i];
	}
}



void gauss_method( double** matrix_A, int rows, int cols, double* x) {

	create_matrix( matrix_A, rows, cols);
	print_matrix( matrix_A, rows, cols);
	
	gauss_elimination( matrix_A, rows, cols);
	
	print_matrix( matrix_A, rows, cols);
	
	backward_substitution(matrix_A, rows, x);

	print_vector( x, rows);
}

void scaled_partial_pivot( double** matrix_A, int rows, int cols) {

	for(int k = 0; k < rows-1; k++ ) {
		double tmp = 0;
		int index_max = 0;
		for(int m=0; m<rows; m++) {
			tmp = MAX( tmp, abs(matrix_A[m][k]) );
			index_max = m;
		}
		
		for(int n=0; n<cols; n++) {
			tmp = matrix_A[k][n];
			matrix_A[k][n] = matrix_A[index_max][n];
			matrix_A[index_max][n] = tmp;
		}
	
		for( int j = k+1; j < rows; j++ ) {
			matrix_A[j][k] = matrix_A[j][k] / matrix_A[k][k];
			for( int i = k+1; i < cols; i++ )
				matrix_A[j][i] = matrix_A[j][i] - matrix_A[j][k]*matrix_A[k][i];
			matrix_A[j][k] = 0;
		}
	}
}

void gauss_partial_pivot_method( double** matrix_A, int rows, int cols, double* x ) {
	
	create_matrix( matrix_A, rows, cols);
	print_matrix( matrix_A, rows, cols);
	
	scaled_partial_pivot( matrix_A, rows, cols);
	
	print_matrix( matrix_A, rows, cols);
	
	backward_substitution(matrix_A, rows, x);

	print_vector( x, rows);
}

void forward_substitution( double** matrix_A, int rows, double* x  ) {
	double s;
	for(int i = 0; i < rows; i++) {
		s = matrix_A[i][rows];
		for(int j=0; j < rows; j++)
			s -=  matrix_A[i][j]*x[j];
		x[i] = s/matrix_A[i][i];
	}
}

void LU_decomposition( double** matrix_A, int rows, int cols, 
												double** L, double* x ) {
	if(matrix_A[0][0] == 0)
		cout << "Factorization impossible" << endl;

	for(int k = 0; k < rows-1; k++ ) {
		for( int j = k+1; j < rows; j++ ) {
			matrix_A[j][k] = matrix_A[j][k] / matrix_A[k][k];
			L[j][k] = matrix_A[j][k];
			for( int i = k+1; i < cols; i++ )
				matrix_A[j][i] = matrix_A[j][i] - matrix_A[j][k]*matrix_A[k][i];
			matrix_A[j][k] = 0;
		}
	}

	for(int i = 0; i < rows; i++ ) {
		for( int j = 0; j < cols; j++ ) {
			( i==j ? L[i][j] = 1 : 1);
			( j == cols-1 ? L[i][j] = matrix_A[i][j] : 1 );
		}
	}

	cout << "\nMatrix L:" << endl;
	print_matrix(L, rows, cols);
	// forward_substitution(L, rows, y);
	// print_vector(y , rows);
}


void LU_method( double** matrix_A, int rows, int cols, double* x ) {

	double** L = new double*[rows];
	for( int i = 0; i < rows; i++ )
		L[i] = new double[cols];
		
	double** U = new double*[rows];
	for( int i = 0; i < rows; i++ )
		U[i] = new double[cols];

	double* y = new double[rows];
	
	create_matrix( matrix_A, rows, cols);

	cout << "Matriz A:" << endl;
	print_matrix(matrix_A, rows, cols);

	LU_decomposition( matrix_A, rows, cols, L, x);

	cout << "\nMatrix U:" << endl;
	print_matrix(matrix_A, rows, cols);

	backward_substitution(matrix_A, rows, x);
	cout << "\nVector X:" << endl;
	print_vector(x, rows);


	for (int i = 0; i < rows; ++i)
		delete [] L[i];
	delete [] L;
	
	for (int i = 0; i < rows; ++i)
		delete [] U[i];
	delete [] U;

	delete [] y;

}

void PLU_descomposition( double** matrix_A, int rows, int cols, double** P ) {

	for(int k = 0; k < rows-1; k++ ) {
		double tmp = 0;
		int index_max = 0;
		for(int m=0; m<rows; m++) {
			tmp = MAX( tmp, abs(matrix_A[m][k]) );
			index_max = m;
		}
		
		for(int n=0; n<cols; n++) {
			tmp = matrix_A[k][n];
			matrix_A[k][n] = matrix_A[index_max][n];
			matrix_A[index_max][n] = tmp;
		}

		for(int n=0; n<rows; n++) {
			tmp = P[k][n];
			P[k][n] = P[index_max][n];
			P[index_max][n] = tmp;
		}
	
		for( int j = k+1; j < rows; j++ ) {
			matrix_A[j][k] = matrix_A[j][k] / matrix_A[k][k];
			for( int i = k+1; i < cols; i++ )
				matrix_A[j][i] = matrix_A[j][i] - matrix_A[j][k]*matrix_A[k][i];
		}
	}

	cout << "\nMatrix P after:" << endl;
	print_matrix(P, rows, rows);

}
void PLU_method( double** matrix_A, int rows, int cols, double* x ) {

	double** P = new double*[rows];
	for( int i = 0; i < rows; i++ )
		P[i] = new double[rows];

	double** L = new double*[rows];
	for( int i = 0; i < rows; i++ )
		L[i] = new double[rows];

	double** U = new double*[rows];
	for( int i = 0; i < rows; i++ )
		U[i] = new double[rows];

	for(int i = 0; i < rows; i++ ) {
		for( int j = 0; j < rows; j++ ) {
			if( i == j)
				P[i][j] = 1;
		}
	}

	cout << "Initial matrix P:" << endl;
	print_matrix(P, rows, rows);


	create_matrix( matrix_A, rows, cols);

	cout << "Matriz A:" << endl;
	print_matrix(matrix_A, rows, cols);

	PLU_descomposition(matrix_A, rows, cols, P);
	// scaled_partial_pivot(matrix_A, rows, cols);
	print_matrix(matrix_A, rows, cols);

	for(int i=0; i<rows; i++) {
		for(int j=0; j<rows; j++) {
			if(i>j) {
				L[i][j] = matrix_A[i][j];
				matrix_A[i][j] = 0;
			}
			else
				U[i][j] = matrix_A[i][j];
		}
	}

	cout << "\nMatriz L:" << endl;
	print_matrix(L, rows, rows);

	cout << "\nMatriz U:" << endl;
	print_matrix(U, rows, rows);

	cout << "vector X" << endl;

	// for(int i=0; i<rows; i++)
	// 	cout << matrix_A[i][rows] << ' ';
	// cout << endl;

	backward_substitution(matrix_A, rows, x);
	print_vector(x, rows);


	for (int i = 0; i < rows; ++i)
		delete [] P[i];
	delete [] P;

	for (int i = 0; i < rows; ++i)
		delete [] L[i];
	delete [] L;

	for (int i = 0; i < rows; ++i)
		delete [] U[i];
	delete [] U;

}


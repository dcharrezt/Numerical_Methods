#include <iostream>
#include <cmath>
#include "equation_solver.h"

using namespace std;

typedef float FF;
typedef double DD;

double function_1( double x_1, double x_2);
double function_2( double x_1, double x_2);

double dev_f_1_1( double x_1, double x_2 );
double dev_f_1_2( double x_1, double x_2 );
double dev_f_2_1( double x_1, double x_2 );
double dev_f_2_2( double x_1, double x_2 );


double norm_sum(double* vect, int size);
double vector_substration(double* vect_1, double* vect_2, int size);

void newton_method(double** JF_F, double* x0 ,double tol, int n_iter );


void func_2( double x, double y );
void JF_2( double x, double y);


int rows, columns;

int main() {

	cin >> rows >> columns;

	double** JF_F = new double*[rows];
	for( int i = 0; i < rows; i++ )
		JF_F[i] = new double[columns];

	double* x_n_0 = new double[rows];

	x_n_0[0]=1.2;
	x_n_0[1]=0.2;

	newton_method( JF_F, x_n_0, 1e-1, 200 );

	for (int i = 0; i < rows; ++i)
		delete [] JF_F[i];
	delete [] JF_F;

	delete [] x_n_0;

	return 0;
}

void func_2( double x, double y, double** JF_F) {
	JF_F[0][columns-1] = function_1( x, y );
	JF_F[1][columns-1] = function_2( x, y );
}

void JF_2( double x, double y, double** JF_F) {
	JF_F[0][0] = dev_f_1_1( x, y);
	JF_F[0][1] = dev_f_1_2( x, y);
	JF_F[1][0] = dev_f_2_1( x, y);
	JF_F[1][1] = dev_f_2_2( x, y);
}

void newton_method(double** JF_F, double* x_n_0 ,double tol, int n_iter ) {
	int iter = 0;
	double* x_n_1 = new double[rows];
	while(iter < n_iter) {
		cout << "ITERATION " << iter << endl;
		func_2( x_n_0[0], x_n_0[1], JF_F );
		JF_2( x_n_0[0], x_n_0[1], JF_F);
		print_vector( x_n_0, rows);
		PLU_method( JF_F, rows, columns, x_n_1 );
		for (int i = 0; i < rows; ++i)
		{
			x_n_1[i] = x_n_0[i] - x_n_1[i];
		}
		// cout << "VECT " << vector_substration(x_n_0, x_n_1, rows) << endl;
		// cout << "VECT " << tol << endl;
		if( vector_substration(x_n_1, x_n_0, rows) < tol ) {
			break;
		}
		for (int i = 0; i < rows; ++i)
		{
			x_n_0[i] = x_n_1[i];
		}
		iter++;
	}

	print_vector( x_n_1, rows );

	delete [] x_n_1;
}

double function_1( double x_1, double x_2) {
	return x_1*x_1 + x_2*x_2 - 2;
}

double function_2( double x_1, double x_2) {
	return x_1 - x_2 - 1;
}

double dev_f_1_1( double x_1, double x_2 ) {
	return 2*x_1;
}

double dev_f_1_2( double x_1, double x_2 ) {
	return 2*x_2;
}

double dev_f_2_1( double x_1, double x_2 ) {
	return 1;
}

double dev_f_2_2( double x_1, double x_2 ) {
	return -x_2;
}

double norm_sum(double* vect, int size) {
	double sum = 0.;
	for (int i = 0; i < size; ++i) {
		sum += vect[i];
	}
	return abs(sum);
}

double vector_substration(double* vect_1, double* vect_2, int size) {
	double* tmp = new double[size];
	for (int i = 0; i < size; ++i) {
		tmp[i] = vect_1[i] - vect_2[i];
	}
	return norm_sum( tmp, size );
}
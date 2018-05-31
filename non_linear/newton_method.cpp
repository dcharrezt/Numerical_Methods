#include <iostream>
#include <cmath>

using namespace std;

typedef float FF;
typedef double DD;

double function_1( double x_1, double x_2);
double function_2( double x_1, double x_2);

double norm_sum(double* vect, int size);
double vector_substration(double* vect_1, double* vect_2, int size);

void newton_method( double** jacobian, double* x0 ,double tol, int n_ecutations );


int main() {

	int n_ecutations, n_variables;
	cin >> n_ecutations >> n_variables;

	double** JF = new double*[n_ecutations];
	for( int i = 0; i < n_ecutations; i++ )
		JF[i] = new double[n_variables];

	double* x_n_0 = new double[n_ecutations];


	for (int i = 0; i < n_ecutations; ++i)
		delete [] JF[i];
	delete [] JF;

	delete [] x_n_0;

	return 0;
}

void newton_method( double** jacobian, double* x_n_0 ,double tol, int n_ecutations ) {
	int iter = 0;
	double* x_n_1 = new double[n_ecutations];

	while(true) {
		cout << "Iteration "<< iter << endl;

		if( vector_substration(x_0, x_1, n_ecutations) < tol ) {
			break;
		}
		iter++;
	}

	delete [] x_n_1;
}

double function_1( double x_1, double x_2) {
	return x_1*x_1 + x_2*x_2 - 2;
}

double function_2( double x_1, double x_2) {
	return x_1 - x_2 - 1;
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
		tmp[i] = abs( vect_1[i] - vect_2[i] );
	}
	return norm_sum( tmp, size );
}
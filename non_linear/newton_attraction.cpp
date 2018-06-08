#include <iostream>

using namespace std;


double function_1( double x, double y );
double function_2( double x, double y );
double partial_derivative( double(*f)(double,double), int e, double x, double y );
void jacobian( double** JF, int n, double x, double y );
void inverse_matrix( double** JF, int n );
void newton_method( double** JF, double x, double y, int n );

int main() {

	int n_functions = 2;

	

	return 0;
}

void newton_method( double** JF, double x, double y, int n_functions ) {
	double** JF_F = new double*[n_functions];
	for( int i = 0; i < n_functions; i++ )
		JF_F[i] = new double[n_functions];


	double* F = new double[n_functions];
	double* X = new double[n_functions];

	F[0] = function_1( x, y );
	F[1] = function_2( x, y );

	jacobian( JF_F, n_functions, x, y );
	inverse_matrix( JF_F, n_functions );

	for (int i = 0; i < n_functions; ++i) {
		double tmp = 0.;
		for (int j = 0; j < n_functions; ++j ) {
			tmp += JF[i][j]*F[j];
		}
		X[i] = tmp;
	}

	X[0] += x;
	X[1] += y;

	cout << X[0] << endl;
	cout << X[1] << endl;


	// for (int i = 0; i < n_functions; ++i) {
	// 	double tmp = .0;
	// 	for (int j = 0; j < n_functions; ++j) {
	// 		cout << JF_F[i][j] << ' ';
	// 	}
	// 	cout << endl;
	// }

	for (int i = 0; i < n_functions; ++i)
		delete [] JF_F[i];
	delete [] JF_F;

	delete [] F;
	delete [] X;
}

void inverse_matrix( double** JF, int n ) {
	double tmp = JF[0][0];
	JF[0][0] = JF[1][1];
	JF[1][1] = tmp;

	tmp = -1*JF[0][1];
	JF[0][1] = -1*JF[1][0];
	JF[1][0] = tmp;

	double det = JF[0][0]*JF[1][1] - JF[0][1]*JF[1][0];

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			JF[i][j] *= det;
		}
	}
}

double partial_derivative( double(*f)(double,double), int e, double x, double y) {
	double h = 1e-4;
	if( e == 0) {
		return ( f( x + h , y ) - f( x , y) ) / h;
	} else {
		return ( f( x, y + h ) - f( x, y) ) / h ;
	}
}

void jacobian( double** JF, int n, double x, double y ) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if( i == 0 )
				JF[i][j] = partial_derivative( function_1, j, x ,y );
			else
				JF[i][j] = partial_derivative( function_2, j, x ,y );
		}
	}
}

double function_1( double x, double y ) {
	return x*x + y*y -1;
}

double function_2( double x, double y ) {
	return -(x*x)+y;
}
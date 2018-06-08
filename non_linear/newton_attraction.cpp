#include <iostream>
#include <cmath>

using namespace std;


double function_1( double x, double y );
double function_2( double x, double y );
double partial_derivative( double(*f)(double,double), int e, double x, double y );
void jacobian( double** JF, int n, double x, double y );
void inverse_matrix( double** JF, int n );
double* newton_method( double* xy, int n, int iter );

int main() {

	int n_functions = 2;
	double tol = 1e-3;

	double* XY = new double[2];
	double* Xs = new double[3];
	double* Ys = new double[3];

	Xs[0] = -0.786;
	Ys[0] = 0.618;

	Xs[1] = 0.;
	Ys[1]  = 0.;

	Xs[2] = 0.786;
	Ys[2]  = 0.618;



	for (int i = -1.5; i <= 2; i+=1) {

		XY[0] = i;
		XY[1] = i;

		newton_method( XY , n_functions, 10);

		cout << XY[0] << ' ' << XY[1] << ' ';

		if( abs(XY[0]-Xs[0]) < tol && abs(XY[1]-Ys[0]) < tol )
			cout << "Green" << endl;
		if( abs(XY[0]-Xs[1]) < tol && abs(XY[1]-Ys[1]) < tol )
			cout << "Blue" << endl;
		if( abs(XY[0]-Xs[2]) < tol && abs(XY[1]-Ys[2]) < tol )
			cout << "Red" << endl;
		else
			cout << "black" << endl;
	}


	return 0;
}

double* newton_method(double* xy, int n_functions, int iter ) {
	double** JF_F = new double*[n_functions];
	for( int i = 0; i < n_functions; i++ )
		JF_F[i] = new double[n_functions];


	double* F = new double[n_functions];
	double* X = new double[n_functions];

	double x = xy[0];
	double y = xy[1];

	for (int k = 0; k < iter; ++k)
	{
		F[0] = function_1( x, y );
		F[1] = function_2( x, y );

		jacobian( JF_F, n_functions, x, y );
		inverse_matrix( JF_F, n_functions );

		// for (int i = 0; i < n_functions; ++i)
		// {
		// 	for (int j = 0; j < n_functions; ++j)
		// 	{
		// 		cout << JF_F[i][j] << ' ';			
		// 	}
		// 	cout << endl;
		// }

		for (int i = 0; i < n_functions; ++i) {
			double tmp = 0.;
			for (int j = 0; j < n_functions; ++j ) {
				tmp += JF_F[i][j]*F[j];
			}
			X[i] = tmp;
		}

		// cout << X[0] << ' ' << X[1] << endl;

		x = x - X[0];
		y = y - X[1];

	}


	for (int i = 0; i < n_functions; ++i)
		delete [] JF_F[i];
	delete [] JF_F;

	delete [] F;
	delete [] X;

	xy[0] = x;
	xy[1] = y;
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
			JF[i][j] /= det;
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
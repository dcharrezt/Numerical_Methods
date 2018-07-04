#include <bits/stdc++.h>

using namespace std;

float function( float x){
	return x;
}

float function_2 ( float x ) {
	return x * x;
}

float function_3 ( float x ) {
	return sin(x);
}

float trapeze_method(float(*f)(float), float a, float b, int n) {
	float h = ( b - a ) / (n);
	float sum = 0.;
	for (int i = 1; i <= n-1; ++i) {
		sum += f(  h*i + a );
	}
	sum *= 2;
	sum += f(a) + f(b);
	sum *= (h/2.);
	cout << "Integral with Trapeze " << sum << endl;
	return sum;
}

void simpson_method( float(*f)(float), float a, float b, int n ) {
	float h = (b-a)/(n);
	float sum = 0.;
	for (int i = 1; i <= (n/2)-1; ++i) {
		sum += f( h*i*2 + a);
	}
	sum *= 2;
	float tmp = 0.;
	for (int i = 1; i <= (n/2); ++i) {
		tmp += f( h*(2*i-1) + a );
	}
	tmp *= 4;
	sum += f(a) + f(b) + tmp;
	sum *= (h/3.);
	cout << "Integral with Simpson " << sum << endl;
}

void print_matrix( double** matrix_A, int rows, int cols ) {
	cout << "\nMatrix of " << rows << " rows and " << cols << " cols\n";
	for( int i = 0; i < rows; i++) {
		for( int j = 0; j < cols; j++ )
			cout << matrix_A[i][j] << ' ';
		cout << endl;
	}	
}

void romberg_method( float(*f)(float), float a, float b, int n ) {
	double** A = new double*[n];
	for( int i = 0; i < n; i++ )
		A[i] = new double[n];

	for( int i = 0; i < n; i++ )
		A[i][0] = trapeze_method( f, a, b, pow(2, i ) );

	for (int j = 1; j < n; ++j) {
		for (int i = 1; i < n; ++i) {
			if( j <= i ) {
				cout << j << " " << i << " "<< A[i][j-1] << " "
						<< A[i-1][j-1] << endl;
				cout << pow(4, j-1) << " "  << (pow(4, j-1)-1) << endl;
				A[i][j] = (pow(4, j) * A[i][j-1] - A[i-1][j-1])/(pow(4, j)-1);
			}
		}
	}

	print_matrix( A, n, n );


	for (int i = 0; i < n; ++i)
		delete [] A[i];
	delete [] A;
}

void simpson_method_3_8( float(*f)(float), float a, float b, int n ) {
	float h = (b-a)/(n);
	float sum = 0.;
	for (int i = 1; i <= (n/3); ++i) {
		sum += f( h*(i*3-2) + a);
	}
	sum *= 3;
	float tmp = 0.;
	for (int i = 1; i <= (n/3); ++i) {
		tmp += f( h*(3*i-1) + a );
	}
	tmp *= 3;
	float tmp_2 = 0.;
	for (int i = 1; i <= ((n/3)-1); ++i) {
		tmp_2 += f( h*(3*i) + a );
	}
	tmp_2 *= 2;
	sum += f(a) + f(b) + tmp + tmp_2;
	sum *= ((3*h)/8.);
	cout << "Integral with Simpson 3/8: " << sum << endl;
}

int main() {

	int n;
	float a,b;
	cout << "Enter the range from a to b" << endl;
	cin >> a >> b;
	cout << "Enter the number of partitions N " << endl;
	cin >> n;
	// trapeze_method( function_2, a, b, n );
	// simpson_method( function_2, a, b, n );
	// simpson_method_3_8( function_2, a, b, n );
	float pi = 3.141592653589793238;
	romberg_method( function_3, 0, pi/2., 6 );

}

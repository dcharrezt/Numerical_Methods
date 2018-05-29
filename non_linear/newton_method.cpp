#include <iostream>
#include <cmath>

using namespace std;

typedef float FF;
typedef double DD;

double function_1( x_1, x_2, x_3 );
double function_2( x_1, x_2, x_3 );

void newton_method();


int main() {

	int n_ecutations, n_variables;
	cin >> n_ecutations >> n_variables;

	double** A = new double*[n_ecutations];
	for( int i = 0; i < n_ecutations; i++ )
		A[i] = new double[n_variables];





	for (int i = 0; i < n_ecutations; ++i)
		delete [] A[i];
	delete [] A;

	return 0;
}
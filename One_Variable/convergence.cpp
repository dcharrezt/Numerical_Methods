#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <limits>
using namespace std;

#define TOL 1e-6

typedef int II;
typedef double DD;
typedef double FF;

FF function_1( FF x) {
	return 1/(pow(x, 3));
}

FF function_2(FF x) {
	return 2/( pow(3, pow(2, x) ) );
}

FF function_3(FF x) {
	return 1/(pow(x, 2));
}

FF function_4(FF x) {
	return 0.5*x + 1 / x;
}

FF function_5(FF x) {
	return pow(x, 3) + 4 * pow(x, 2) - 10;
}

FF function_6(FF x) {
	return 0.5*pow(x, 2)+ x + 1 - pow(M_E, x);
}

FF aprox_alpha_v1( FF(*f)(FF), FF x , FF n) {
	return ( log( abs(f(n+1) - x) ) - log( abs( f(n) - x) ) ) / 
				( log( abs(f(n) - x) ) - log( abs( f(n-1) - x) ) );
}

FF aprox_alpha_v2( FF(*f)(FF), FF x , FF n) {
	return  log( abs(f(n+1) - f(n)) / abs(f(n) -   f(n-1)) ) / 
		    log( abs(f(n) - f(n-1)) / abs(f(n-1) - f(n-2)) );
}

FF convergence( FF(*f)(FF), FF x) {

	FF alpha = 0.;
	FF n = 0.;
	FF err = aprox_alpha_v2(f, x ,n);
	n++;
	while(1) {
		alpha = aprox_alpha_v2(f, x, n);
		if( abs(alpha - err) <= TOL) {
			cout << "Iterations: " << n+1 << endl;
			cout << "alpha: " << alpha << "\terr: " << err << endl;

			return alpha;
		}
		err = alpha;
		n++;
	}
}


int main(int argc, char const *argv[])
{
	cout<< "ALPHA function 1\t" << convergence(function_1, 0.) << endl;
	cout<< "ALPHA function 2\t" << convergence(function_2, 0.) << endl;
	cout<< "ALPHA function 3\t" << convergence(function_3, 0.) << endl;
	cout<< "ALPHA function 4\t" << convergence(function_4, 0.) << endl;
	cout<< "ALPHA function 5\t" << convergence(function_5, 0.) << endl;
	cout<< "ALPHA function 6\t" << convergence(function_6, 0.) << endl;

	return 0;
}
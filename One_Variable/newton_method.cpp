#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef int II;
typedef double DD;
typedef double FF;

// functions to eval
FF function_1 ( FF x );
FF function_2 ( FF x ); 
FF function_3 ( FF x ); 
// file handler
void save_text(string filename, string text);
void save_data(string filename,II iteration, FF p, FF fp);

void newton_method(FF p_0, FF(*f)(FF), FF tol, II iters);
FF deriv(FF(*f)(FF), FF x, FF h);

int main() {

	system("gnuplot -p 'newton_f3'");
	// system("gnuplot -p 'newton_f3'");

	FF x0 = 0.5;
	FF tol = 10e-4;


	newton_method(x0, function_2, tol, 20);
	// newton_method(x0, function_3, tol, 20);

	return 0;
}

void newton_method(FF p_0, FF(*f)(FF), FF tol, II iters) {
	FF p;
	FF h = 0.001;
	save_text("newton_method_2.csv","i,r_i,f(r_i)\n");
	for (int i = 0; i < iters; ++i) {
		FF fp = f(p_0);
		p = p_0 - fp / deriv(f, p_0, h);
		save_data("newton_method_2.csv", i, p_0, p);
		if( abs(p - p_0) < tol)
			break;
		p_0 = p;
	}
}

FF deriv(FF(*f)(FF), FF x, FF h) {
	return (f(x+h) - f(x)) / h;
}

// FF function_1 ( FF x ) {
// 	return cos(x) - x;
// }

FF function_1 ( FF x ) {
	return pow(x, 4)-3*x*x-3;
}

FF function_2 (FF x ) {
	return pow(x, 3) + 4 * pow(x, 2) - 10;
}

FF function_3 ( FF x ) {
	return 0.5* pow(x,2) + x + 1 - exp(x);
} 

void save_text(string filename, string text) {
	ofstream my_file(filename.c_str());
	if(my_file.is_open()) {
		my_file << text;
		my_file.close();
	}
	else
		cout << "Unable to open file";
}

void save_data(string filename,II iteration, FF p, FF fp) {
	ofstream my_file(filename.c_str(), ios_base::app);
	if(my_file.is_open()) {
		my_file << iteration<<','<<p<<','<<fp<<",\n";
		my_file.close();
	}
	else
		cout << "Unable to open file";
}

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

FILE *fi;

typedef int II;
typedef double DD;
typedef float FF;

// functions to eval
FF function_1 ( FF x );

FF function_2 ( FF x );

// file handlers
void save_text(string filename, string text);
void save_data(string filename,II iteration, FF p, FF fp);
void save_data(string filename,II iteration, FF p_0, FF p_1, FF p, FF q_0, FF q_1);
void save_data(string filename,II iteration, FF p_0, FF p_1, FF p, FF q_0);

void secant_method(FF p_0, FF p_1, FF(*f)(FF), FF tol, II iters);
FF deriv(FF(*f)(FF), FF x, FF h);

int main() {

	system("gnuplot -p 'secant_f1'");
	secant_method(-1, 1, function_2, 10e-3, 100);

	return 0;
}

void secant_method(FF p_0, FF p_1, FF(*f)(FF), FF tol, II iters) {
	FF q_0 = f(p_0);
	FF q_1 = f(p_1);
	FF p;
	save_text("secant_method_2.csv","i,x(i-1),x(i),|x(i)-x(i-1)|,f(xi)\n");
	for (int i = 0; i < iters; ++i) {
		p = p_1 - q_1 * (p_1 - p_0) / ( q_1 - q_0);
		save_data("secant_method_2.csv", i+1, p_1, p, abs(p-p_1), q_1);
		if( abs(p - p_1) < tol)
			break;
		p_0 = p_1;
		q_0 = q_1;
		p_1 = p;
		q_1 = f(p);
	}
}

FF deriv(FF(*f)(FF), FF x, FF h) {
	return (f(x+h) - f(x)) / h;
}

FF function_1 ( FF x ) {
	return cos(x) - x;
}

FF function_2 ( FF x ) {
	return x*x*x + 3*x*x*cos(x)-1;
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

void save_data(string filename,II iteration, FF p_0, FF p_1, FF p, FF q_0, FF q_1){
	ofstream my_file(filename.c_str(), ios_base::app);
	if(my_file.is_open()) {
		my_file << iteration<<','<<p_0<<','<<p_1<<','<<p<<','<<q_0<<
							','<<q_1<<",\n";
		my_file.close();
	}
	else
		cout << "Unable to open file";
}

void save_data(string filename,II iteration, FF p_0, FF p_1, FF p, FF q_0) {
	ofstream my_file(filename.c_str(), ios_base::app);
	if(my_file.is_open()) {
		my_file << iteration<<','<<p_0<<','<<p_1<<','<<p<<','<<q_0<<",\n";
		my_file.close();
	}
	else
		cout << "Unable to open file";
}
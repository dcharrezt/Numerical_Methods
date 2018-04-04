#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std:

typedef float FF;
typedef int II;
typedef double DD;


void write_text(string filename, iteration, a_i, b_i, r_i, f_i) {
	ofstream my_file(filename);
	if(my_file.is_open()) {
		my_file << "i, a_i, b_i, r_i, f(r_i)\n";
		my_file.close();
	}
	else
		cout << "Unable to open file";
}

FF function_1(FF x) {
	return 10*pow(x, 3) + x*pow(tan(x+2*M_PI),-1) + 5;
}

FF function_2(FF x) {
	return pow(x,2)*cos(2*x+1) + pow(M_E,x-2)-x;
}

void false_pos(FF a, FF b, FF (*f)(FF), II n);
void false_pos(FF a, FF b, FF (*f)(FF), FF tol);
void false_pos(FF a, FF b, FF (*f)(FF), FF tol);

int main() {





}
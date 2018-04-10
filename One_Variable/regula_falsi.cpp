#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef float FF;
typedef int II;
typedef double DD;


void save_text(string filename, string text);
void save_data(string filename,II iteration, FF a_i, FF b_i, FF r_i, FF f_i);
FF function_1(FF x);
FF function_2(FF x);

void false_pos_1(FF a, FF b, FF (*f)(FF), II n);
void false_pos_2(FF a, FF b, FF (*f)(FF), FF tol);
void false_pos_3(FF a, FF b, FF (*f)(FF), FF tol);

int main() {

system("gnuplot -p 'plot_false_1'");
system("gnuplot -p 'plot_false_2'");

false_pos_1(-3, 3, function_2, 30);
false_pos_2(-3, 3, function_2, 0.0001);
false_pos_3(-3, 3, function_2, 0.0001);

}

void false_pos_1(FF a, FF b, FF (*f)(FF), II n) {
	II k = 0;
	FF fp, p;
	FF FA = f(a);

	save_text("false_pos_1.csv","i,a_i,b_i,p_i,fp\n");

	while(k <= n) {
		p = b - f(b)*((b-a)/(f(b) - f(a)));
		fp = f(p);
		k++;
		save_data("false_pos_1.csv", k, a, b, p, fp);

		if((FA*fp) > 0) {
			a = p;
			FA = fp;
		} else {
			b = p;
		}
	}
}

void false_pos_2(FF a, FF b, FF (*f)(FF), FF tol) {
	II k = 0;
	FF fp, p;
	FF FA = f(a);

	save_text("false_pos_2.csv","i,a_i,b_i,r_i,|f_i|\n");

	while(1) {
		p = b - f(b)*((b-a)/(f(b) - f(a)));
		fp = f(p);
		if(abs(fp) <= tol) {
			break;
		}
		k++;
		save_data("false_pos_2.csv", k, a, b, p, abs(fp));
		if((FA*fp) > 0) {
			a = p;
			FA = fp;
		} else {
			b = p;
		}
	}
}

void false_pos_3(FF a, FF b, FF (*f)(FF), FF tol) {
	II k = 0;
	FF fp, p_2, p_1;
	FF FA = f(a);

	save_text("false_pos_3.csv","a_i,b_i,r_i,|r_i-r_i-1|,(f_r_i)\n");
	while(1) {
		p_2 = b - f(b)*((b-a)/(f(b) - f(a)));
		fp = f(p_2);

		k++;

		if((FA*fp) > 0) {
			a = p_2;
			FA = fp;
		} else {
			b = p_2;
		}

		if(k > 1 && abs(p_2-p_1) <= tol) {
			save_data("false_pos_3.csv", a, b, p_2, abs(p_2-p_1),fp);
			break;
		}
		if(k > 1) {
			save_data("false_pos_3.csv", a, b, p_2, abs(p_2-p_1),fp);
		}

		p_1 = p_2;

	}
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

void save_data(string filename,II iteration, FF a_i, FF b_i, FF r_i, FF f_i) {
	ofstream my_file(filename.c_str(), ios_base::app);
	if(my_file.is_open()) {
		my_file << iteration<<','<<a_i<<','<<b_i<<','<<r_i<<','<<f_i<<",\n";
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
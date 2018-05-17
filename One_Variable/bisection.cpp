#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

FILE *fi;

typedef int II;
typedef double DD;
typedef float FF;

void GuardarDatos(FF k, FF a, FF b, FF p, FF f, char* fileName);
void GuardarTexto(char* texto,char* fileName);
void bisection_1(FF a, FF b, FF f, II n);
void bisection_2(FF a, FF b, FF f, FF tol);
void bisection_3(FF a, FF b, FF f, FF tol);
void regula_falsi(FF a, FF b, FF (*f)(FF), FF tol);

FF function_1(FF x) {
	return 3*pow(x,5) + 2*x*pow(M_E,-x) + 5*cos(x) - 4;
}

FF function_2(FF x) {
	return atan(4*x-5) + pow(M_E, -2*x+1)*sin(x+M_PI) - x*x;
}


int main() {

	regula_falsi(-2, 2, function_2, 0.0001);

    // system("gnuplot -p 'plot'");
    // system("gnuplot -p 'plot2'");
    // bisection_1(-2, 2, 0, 100);
    // bisection_2(-2, 2, 0, 0.0001);
    // bisection_3(-2, 2, 0, 0.0001);

    return 0;


}


void GuardarDatos(FF k, FF a, FF b, FF p, FF f, char* fileName){

    fi = fopen(fileName, "a");
    if (fi == NULL)
    {
        exit(1);
    }
    fprintf(fi, "%f %f %f %f %f\n", k, a, b, p, f);
    fclose(fi);
}

void GuardarTexto(char* texto, char* fileName){
    fi = fopen(fileName, "a");
    if (fi == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(fi, "%s", texto);

    fclose(fi);
}


void bisection_1(FF a, FF b, FF f, II n) {
	II k = 0;
	FF fp, p;
	FF FA = function_2(a);

	GuardarTexto("k a_k b_k p_k fp\n", "bisection_1.csv");

	while(k <= n) {
		p = a + (b - a)/2;
		fp = function_2(p);
		//if(fp == 0)
		k++;
		GuardarDatos(k, a, b, p, fp, "bisection_1.csv");

		if((FA*fp) > 0) {
			a = p;
			FA = fp;
		} else {
			b = p;
		}
	}
}
void bisection_2(FF a, FF b, FF f, FF tol) {
	II k = 0;
	FF fp, p;
	FF FA = function_2(a);

	GuardarTexto("k a_k b_k p_k fp\n", "bisection_2.csv");

	while(1) {
		p = a + (b - a)/2;
		fp = function_2(p);
		if(abs(fp) <= tol) {
			break;
		}
		k++;
		GuardarDatos(k, a, b, p, fp, "bisection_2.csv");

		if((FA*fp) > 0) {
			a = p;
			FA = fp;
		} else {
			b = p;
		}
	}

}
void bisection_3(FF a, FF b, FF f, FF tol) {
	II k = 0;
	FF fp, p;
	FF FA = function_2(a);

	GuardarTexto("k a_k b_k p_k fp\n", "bisection_3.csv");

	while(1) {
		p = a + (b - a)/2;
		fp = function_2(p);
		if( (b-a)/2 < tol){
			break;
		}
		k++;
		GuardarDatos(k, a, b, p, fp, "bisection_3.csv");

		if((FA*fp) > 0) {
			a = p;
			FA = fp;
		} else {
			b = p;
		}
	}
}

void regula_falsi(FF a, FF b, FF (*f)(FF), FF tol) {
	II k = 0;
	FF fp, p;
	FF FA = f(a);

	while(1) {
		p = b - f(b)*((b-a)/(f(b) - f(a)));
		fp = f(p);

		if(abs(fp) <= tol) {
			break;
		}
		k++;
		GuardarDatos(k, a, b, p, fp, "regula_falsi_2.csv");

		if((FA*fp) > 0) {
			a = p;
			FA = fp;
		} else {
			b = p;
		}
	}
}
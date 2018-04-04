#include <stdio>
#include <stdlib>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

FILE *fi;

typedef int II;
typedef double DD;
typedef float FF;

void func ( float (*f)(int) );

void func ( float (*f)(int) ) {
	float s = 0;
	for ( int ctr = 0 ; ctr < 5 ; ctr++ ) {
		s += (*f)(ctr);
	}
  	cout << "ss -- " << s << endl;
}


float function_1 ( int x ) {
	cout << "ms :3" << endl;
  return x;
}


int main()
{
	func(function_1);

	return 0;
}
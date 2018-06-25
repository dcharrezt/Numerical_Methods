#include <bits/stdc++.h>

using namespace std;

float function( float x){
	return x;
}

float function_2 ( float x ) {
	return x * x;
}

void trapeze_method(float(*f)(float), float a, float b, int n) {
	float h = ( b - a ) / (n);
	float sum = 0.;
	for (int i = 1; i <= n-1; ++i) {
		sum += f(  h*i + a );
	}
	sum *= 2;
	sum += f(a) + f(b);
	sum *= (h/2.);
	cout << "Integral with Trapeze " << sum << endl;
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

int main() {

	int n;
	float a,b;
	cout << "Enter the range from a to b" << endl;
	cin >> a >> b;
	cout << "Enter the number of partitions N " << endl;
	cin >> n;
	trapeze_method( function_2, a, b, n );
	simpson_method( function_2, a, b, n );

}
#include <bits/stdc++.h>

using namespace std;

float function( float x){
	return x;
}

void trapeze_method(float a, float b, int n) {
	float h = ( b - a ) / (2.*n);
	float sum = 0.;
	float interval = float((b-a)/ n);
	for (int i = 1; i < n-1; ++i) {
		sum += function(  interval*i + a );
	}
	sum *= 2;
	sum += function(a) + function(b);
	sum *= (h);
	cout << "Integral " << sum << endl;
}

int main() {

	int n;
	float a,b;
	cout << "Enter the range from a to b" << endl;
	cin >> a >> b;
	cout << "Enter the number of partitions N " << endl;
	cin >> n;
	trapeze_method( a, b, n );

}
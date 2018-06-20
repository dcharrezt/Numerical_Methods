#include <iostream>
#include <vector>

using namespace std;

typedef vector< pair<float, float> > coords;

float function( float x ) {
	return 1 / x; 
}

coords read_input() {
	int n_dots;
	float x_tmp, y_tmp;
	coords dots;
	
	cin >> n_dots;
	for(int i = 0; i < n_dots; i++) {
		cin >> x_tmp >> y_tmp;
		dots.push_back( make_pair( x_tmp, y_tmp) );
	}
	return dots;
}

void newton_method( coords dots, float p_x) {
	float L = 0.; 
 	float L_tmp;
	for (int i = 0; i < dots.size(); ++i) {
		L_tmp = 1;
		for (int j = 0; j < dots.size(); ++j) {
			if( i != j )
				L_tmp *= ((p_x - dots[j].first) / (dots[i].first - dots[j].first));
		}
		L_tmp *= dots[i].second;
		L+=L_tmp;
	}
	cout << p_x << " " << L << endl;
}

int main() {

	coords dots;
	dots = read_input();

	float p_x;
	cin >> p_x;

	for (int i = 0; i < dots.size(); ++i) {
		cout << dots[i].first << ' ' << dots[i].second << endl;
	}

	// newton_method( dots, p_x);

	return 0;
}

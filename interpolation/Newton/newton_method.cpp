#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

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
	float b = dots[0].second;
	float tmp, div_dif;
	vector<float> p;
	int k = 1;
	for (int i = 0; i < dots.size() - 1; ++i) {
		for (int j = 0; j < (dots.size()-i-1); ++j) {
			div_dif = ( dots[j+1].second - dots[j].second)/
								(dots[i+j+1].first - dots[j].first);
			dots[j].second = div_dif;
		}
		tmp = 1.;
		for (int i = 0; i < k; ++i) {
			tmp*=( p_x - dots[i].first );
		}
		b+=( dots[0].second*tmp );
		k++;
	}
	cout << p_x << ' ' << b << endl;
 
}

int main() {
	coords dots;
	dots = read_input();

	float p_x;
	cin >> p_x;

	for (int i = 0; i < dots.size(); ++i) {
		cout << dots[i].first << ' ' << dots[i].second << endl;
	}

	newton_method( dots, p_x);


	return 0;
}

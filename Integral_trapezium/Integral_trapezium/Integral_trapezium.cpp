/*Program calculate integral from a to b f(x)dx 
using three methods
1) Left point
2) Right point
3) Middle point
*/
#include "pch.h"
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

double f(double x) {
	return /*Func you want*/ 5 * pow(x,4) - 3 * pow(x,2) + 1;
}

int main(){
	
	cout << "n=";
	int n,a,b;
	cin >> n;
	cout << "[a, b]\na= ";
	cin >> a;
	cout << "b= ";
	cin >> b;
	double result[3] = { 0, 0, 0 };
	double step = (b - a) / (double)n;
	for (int i = 0; i < n ; i++ ) {
		double x = a + i * step; // longer but more precisely 
		result[0] += f(x);
		result[1] += f(x + step);
		result[2] += f(x + step / (double)2);
	}
	cout << "results: \n";
	string text[3] = { "Left point", "Right point", "Center point" };
	for (int i = 0; i < 3; i++) {
		result[i] *= step ;
		cout << text[i] << ' ' << result[i] << '\n';
	}
		
}

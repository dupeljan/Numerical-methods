#include "pch.h"
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

double f(double x) {
	return /*Func you want*/ x*x ;
}
int main(){
	
	cout << "n=";
	int n,a,b;
	cin >> n;
	cout << "[a, b]\na= ";
	cin >> a;
	cout << "b=";
	cin >> b;
	double result[3] = {0, 0, 0}, step = (b - a) / (double) n;
	for (double i = a; (a < b)? i < b : i > b; i += step) {
		result[0] += f(i);
		result[1] += f(i + step);
		result[2] += f(i + step / (double)2);
	}
	cout << "results: \n";
	string text[3] = { "Left point", "Right point", "Center point" };
	for (int i = 0; i < 3; i++) {
		result[i] *= step ;
		cout << text[i] << ' ' << result[i] << '\n';
	}
		

}

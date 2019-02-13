#include "pch.h"
#include <math.h>
#include <iostream>
using namespace std;

double f(double x) {
	return /*Func you want*/ x*x ;
}
int main(){
	
	cout << "n=";
	int n,method,a,b;
	cin >> n;
	cout << "[a, b]";
	cin >> a >> b;
	do {
		cout << "Select method: \n1)Left point\n2)Right point\n3)Centre point";
		cin >> method;
	} while (!(0 < method && method < 4));
	double result = 0, step = abs(a - b) / (double) n ;
	for( double i = a; i < b; i+= step)
			switch (method){
			case 1:
				result += f(i);
				break;
			case 2:
				result += f(i + step);
				break;
			case 3:
				result += f(i + step / (double)2);
				break;
			}
		cout << "result: " << result * step ;

}

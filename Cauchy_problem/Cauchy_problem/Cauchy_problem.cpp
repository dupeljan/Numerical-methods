#include "pch.h"
#include "Adams_Cauchy_problem.h"
#include <iostream>
#include <math.h>


int main(){
	func_pointer f = [](double x, double y) { return 3 * y / x + pow(x, 3) + x; };
	auto result = Runge_Kutta_Cauchy_solution(1, 2, 0, f, 20);
	for (auto &x : result)
		cout << "x " << x.x << " y " << x.y << endl;
}

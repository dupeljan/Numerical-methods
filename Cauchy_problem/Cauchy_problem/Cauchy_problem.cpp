/*Program solve Cauchy problem
using Adams method accuracy order 4 
*/
#include "pch.h"
#include "Adams_Cauchy_problem.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

#define EX_N 1
#define FILE_OUTPUT_PATCH "output.txt"

struct parametrs {
	func_pointer f;
	function<double(double)> solution;
	double a, b, y0;
	int steps;
};

parametrs get_example() {
	/*put your example here*/
	parametrs example;
#if EX_N == 0
	example.f = [](double x, double y) { return 3 * y / x + pow(x, 3) + x; };
	example.solution = [](double x) { return pow(x, 4) - pow(x, 2); };
	example.a  = 1;
	example.b  = 2;
	example.steps = 20;
#elif EX_N == 1
	example.f = [](double x, double y) { return y + x * exp(x); };
	example.solution = [](double x) { return exp(x) * pow(x, 2) / (double)2; };
	example.a = -4;
	example.b = 1;
	example.steps = 50;
#elif EX_N == 2
	example.f = [](double x, double y) { return  y + exp(x); };
	example.solution = [](double x) { return (x+1)*exp(x); };
	example.a = -3;
	example.b = 1;
	example.steps = 50;
#elif EX_N == 3
	example.f = [](double x, double y) { return pow(y, 2) * exp(x) - 2 * y; };
	example.solution = [](double x) { return 1 / (double)(exp(x) - 2 * exp(2 * x) / (double)3 ); };
	example.a = -3;
	example.b = 0;
	example.steps = 70;
#endif
	example.y0 = example.solution(example.a);

	return example;
}

string replace_dot_to_comma(point x);

int main(){
	auto ex = get_example();
	auto result = Adams_method_Cauchy_solution(ex.a, ex.b, ex.y0, ex.f, ex.steps);
	fstream out;
	out.open(FILE_OUTPUT_PATCH, fstream::out);
	for (auto &x : result)
		out << replace_dot_to_comma(x) << endl;
	cout << "Error " << error(ex.solution, result);
	
}
// Usefull for exel output
string replace_dot_to_comma(point x) {
	ostringstream strs;
	strs << x.x << ' ' << x.y;
	string str = strs.str();
	size_t cur;
	while ((cur = str.find(".")) != string::npos)
		str.replace(cur, 1, ",");
	return str;
}

/*Program solve Cauchy problem
using Adams method accuracy order 4 
*/
#include "pch.h"
#include "Adams_Cauchy_problem.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

#define EX_N 0
#define FILE_OUTPUT_PATCH "output.txt"

struct parametrs {
	func_pointer f;
	double a, b, y0;
	int steps;
};

parametrs get_example() {
	/*put your example here*/
	parametrs example;
#if EX_N == 0
	example.a  = 1;
	example.b  = 2;
	example.y0 = 0;
	example.steps = 20;
	example.f  = [](double x, double y) { return 3 * y / x + pow(x, 3) + x; };
#endif
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

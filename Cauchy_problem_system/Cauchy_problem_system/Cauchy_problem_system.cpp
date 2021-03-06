/*Program solve Cauchy problem system
using Adams method accuracy order 4
*/
#include "pch.h"
#include "Adams_Cauchy_problem_system.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

#define EX_N 3
#define FILE_OUTPUT_NAME "output"
#define FILE_DESK ".txt"

struct parametrs {
	func_pointer f;
	function<vector<double>(double)> solution;
	vector<double> y0;
	double a, b;
	int steps;
};

parametrs get_example() {
	/*put your example here*/
	parametrs example;
#if EX_N == 0
	/*Filipov #94*/
	example.f = [](double x, vector<double> y)->vector<double> { return {  -5 * y[1],
																		   2 * y[0] + 2 * y[1]}; };

	example.solution = [](double x) ->vector<double> { return { exp(x) * ( 3 * cos(3 * x) - sin(3 * x) ),
																exp(x) * 2 * sin(3 * x) }; };
	example.a = -7;
	example.b = 0.5;
	example.steps = 50;
#elif EX_N == 1
	example.f = [](double x, vector<double> y) -> vector<double> { return { y[0] + x * exp(x),  y[1] + exp(x) }; };
	example.solution = [](double x) -> vector<double> { return { exp(x) * pow(x, 2) / (double)2,  (x + 1)*exp(x) }; };
	example.a = -7;
	example.b = 0;
	example.steps = 50;
#elif EX_N == 2
	/*Filipov #95*/
	example.f = [](double x, vector<double> y) -> vector<double> { return { y[2] - y[0] - y[1],
																			y[0] - y[1] - y[2],
																			-y[1]}; };
	example.solution = [](double x) -> vector<double> { return { -1 + (2 + x) * exp(-x),
																x * exp( -x),
																-1 + (1 + x) * exp(-x)}; };
	example.a = -5;
	example.b = 5;
	example.steps = 30;
#elif EX_N == 3
	/*Filipov #826*/
	example.f = [](double x, vector<double> y) -> vector<double> { return { y[1] + 2 * exp(x),
																			y[0] + x*x }; };
	example.solution = [](double x) -> vector<double> { return { exp(x) + 2 * exp(-x) + x * exp(x) - x*x - 2,
																 exp(x) - 2 * exp(-x) + (x - 1) * exp(x) - 2 * x }; };
	example.a = 2;
	example.b = 5;
	example.steps = 30;
#endif
	example.y0 = example.solution(example.a);

	return example;
}

string replace_dot_to_comma(double x, double y);

int main() {
	auto ex = get_example();
	auto result = Adams_method_Cauchy_solution(ex.a, ex.b, ex.y0, ex.f, ex.steps);
	vector<fstream> out(result[0].y.size());
	for (int i = 0; i < out.size(); i++)
		out[i].open(FILE_OUTPUT_NAME + to_string(i) + FILE_DESK, fstream::out);
	for (auto &x : result)
		for (int i = 0; i < x.y.size(); i++) 
			out[i] << x.x << " " << x.y[i] << endl;
		
		
	cout << "Error " << error(ex.solution, result);

}
// Usefull for exel output
string replace_dot_to_comma(double x, double y) {
	ostringstream strs;
	strs << x << ' ' << y;
	string str = strs.str();
	size_t cur;
	while ((cur = str.find(".")) != string::npos)
		str.replace(cur, 1, ",");
	return str;
}

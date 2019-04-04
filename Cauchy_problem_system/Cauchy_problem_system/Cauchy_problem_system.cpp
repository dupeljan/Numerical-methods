/*Program solve Cauchy problem system
using Adams method accuracy order 4
*/
#include "pch.h"
#include "Adams_Cauchy_problem_system.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

#define EX_N 1
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
	example.f = [](double x, vector<double> y)->vector<double> { return {  y[1] - y[0] - 4,
														   3 * y[1] - y[0] }; };

	example.solution = [](double x) ->vector<double> { return { ( -3 + 2 * x) * exp(2 * x) + 3,
												(-3 + 2 * ( 1 + x ) ) * exp(2 * x) + 1 }; };
	example.a = -5;
	example.b = -1;
	example.steps = 40;
#elif EX_N == 1
	example.f = [](double x, vector<double> y) -> vector<double> { return { y[0] + x * exp(x),  y[1] + exp(x) }; };
	example.solution = [](double x) -> vector<double> { return { exp(x) * pow(x, 2) / (double)2,  (x + 1)*exp(x) }; };
	example.a = -7;
	example.b = 0;
	example.steps = 50;
#elif EX_N == 2
	example.f = [](double x, double y) { return  y + exp(x); };
	example.solution = [](double x) { return (x + 1)*exp(x); };
	example.a = -3;
	example.b = 1;
	example.steps = 50;
#elif EX_N == 3
	example.f = [](double x, double y) { return pow(y, 2) * exp(x) - 2 * y; };
	example.solution = [](double x) { return 1 / (double)(exp(x) - 2 * exp(2 * x) / (double)3); };
	example.a = -3;
	example.b = 0;
	example.steps = 70;
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

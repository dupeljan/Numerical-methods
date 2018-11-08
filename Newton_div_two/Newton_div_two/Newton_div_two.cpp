#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


#define INP_PATH "input.txt"
#define OUT_PATH "output.txt"
#define DELTA    1e-10 
using namespace std;

class Solution {
	Solution();
};

Solution::Solution(){
}
template <typename T>
exprtk::expression<T> getExpression(string expression_string, string var, T &x) { // T must be global	
	
	typedef exprtk::symbol_table<T> symbol_table_t;
	typedef exprtk::expression<T>     expression_t;
	typedef exprtk::parser<T>             parser_t;

	//std::string expression_string = "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";


	symbol_table_t symbol_table;
	symbol_table.add_variable(var, x);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);
	return expression;
}

template <typename T>
double derivarive(exprtk::expression<T> expr, int &x) {

}
int main()
{
	// input function and range
	ifstream in(INP_PATH);
	if (!in)
		return 1;

	string str_expression;
	getline(in, str_expression);
	double x;
	exprtk::expression<double> f = getExpression<double>(str_expression,"x", x);
	string range;
	getline(in, range);
	stringstream ss(range);
	double a, b;
	ss >> a >> b;

	// Method 
	// 
	x = a;
	double pred = f.value();
	for( ; x <= b; x += DELTA){
		if (pred * f.value() < 0) {
			// find zero point here
			double x_seq = pred;

		}
		pred = f.value();
	}
	system("pause");

}


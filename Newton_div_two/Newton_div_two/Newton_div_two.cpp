#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


#define INP_PATH "input.txt"
#define OUT_PATH "output.txt"
#define DELTA    1e-1 
#define EPS	     1e-5 
using namespace std;

template <typename T>
class Solution {
	T X_ARG;
	exprtk::expression<T> func;
	vector<T> result;
	void getExpression(string expression_string, string x);
	double derivative(T point);
	double local_zero(T localL, T localR);
	T f(T x);
public:
	Solution(string var );
	vector<T> get_result() { return result; }
	
};

template <typename T>
T Solution<T>::f(T x) {
	X_ARG = x;
	return func.value();
}

template <typename T>
Solution<T>::Solution(string var){
	// input function and range
	ifstream in(INP_PATH);
	if (in) {
		string str_expression;
		getline(in, str_expression);
		getExpression(str_expression, var);
		string range;
		getline(in, range);
		stringstream ss(range);
		int L, R;
		ss >> L >> R;
		
		// Method 
		for (T x = L + DELTA; x < R; x += DELTA) 
			if ( f(x-DELTA) * f(x) < 0) 
				// find zero point here": [x-DELTA,x]
				result.push_back(local_zero(x - DELTA, x));	
	}
}

template <typename T>
double Solution<T>::derivative(T point) {
	/*T delta = f(point);
	return f(point + delta) / T(delta) - 1; */
	return  (f(point + EPS) - f(point)) / T(EPS);
}

template <typename T>
double Solution<T>::local_zero(T localL, T localR) {
	T x_seq, x_seq_new(localL);
	do{
		x_seq = x_seq_new;
		x_seq_new = x_seq - f(x_seq) / T(derivative(x_seq));
		cout << x_seq << ' ' << x_seq_new << endl;
		while (abs(f(x_seq_new)) > abs(f(x_seq)))
		{
			x_seq_new = (x_seq + x_seq_new) / T(2);
		}
		
	} while (abs(x_seq - x_seq_new)>EPS || abs(f(x_seq)-f(x_seq_new))>EPS);// abs( x_seq_new - x_seq ) < EPS && abs( f(x_seq_new) - f(x _seq) ) <
	return x_seq_new;
}

int main()
{
	fstream out(OUT_PATH, fstream::out);
	Solution<double> s("x");
	vector<double> res = s.get_result();
	for (auto i : res)
		out << i << ' ';
	out << endl;
	out.close();
	system("pause");

}

template <typename T>
void Solution<T>::getExpression(string expression_string, string x) { // T must be global	

	typedef exprtk::symbol_table<T> symbol_table_t;
	typedef exprtk::expression<T>     expression_t;
	typedef exprtk::parser<T>             parser_t;


	symbol_table_t symbol_table;
	symbol_table.add_variable(x, Solution::X_ARG);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);
	Solution::func = expression;
}


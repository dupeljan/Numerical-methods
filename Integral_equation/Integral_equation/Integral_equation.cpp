/*Program calculate solution of the equation
 integral from a to x f(x) dx = b
 using Simpson's rule for integral calculating and
 Newton method to solve equation;
 Proofs, ex
 1)From handbook
 2)https://www.wolframalpha.com/input/?i=solve+int+(5x%5E4+-+3x%5E2+%2B+1)dx+from+0+to+x+equal+1
 3)https://www.wolframalpha.com/input/?i=solve+int+(exp(x))dx+from+0+to+x+equal+pi
*/
#include "pch.h"
#include <iostream>
#include <limits>
#include <functional>
#include <math.h>

#define EPS 1e-15
#define ITERATION 1e4
#define PI 3.14159265359

#define EX_N 0

using namespace std;

typedef function<double(double)> func_pointer;

struct parametrs{
	func_pointer f;
	double a, b, correct_answer;
};

parametrs get_example() {
	/*put your example here*/
	parametrs example;
	#if EX_N == 0
		example.a = 0;
		example.b = PI;
		example.f = [](double x) { return  4 / (double)(x * x + 1);  };
		example.correct_answer = 1;
	#elif EX_N == 1
		example.a = 0;
		example.b = 1;
		example.f = [](double x) { return 5 * pow(x, 4) - 3 * pow(x, 2) + 1; };
		example.correct_answer = 1;
	#elif EX_N == 2
		example.a = 0;
		example.b = PI;
		example.f = [](double x) { return exp(x);  };
		example.correct_answer = 1.42108;
	#endif
	return example;
}

double solve(double a, double b, func_pointer f, int iterations);
double Simpson_integral_solution(double a, double b, func_pointer f, int n);
double Newton_solution(func_pointer f, func_pointer der_f, double approximation);


int main(){
	cout.precision(numeric_limits< double >::max_digits10);
	parametrs ex = get_example();
	double result = solve(ex.a, ex.b, ex.f, ITERATION);
	cout << "\nResult " << result << endl;
	cout << "Correct answer " << ex.correct_answer << endl;
	cout << "Error " << abs(ex.correct_answer - result) << endl;
}

double solve(double a, double b, func_pointer f, int iterations){
	func_pointer g = [a,b,f,iterations](double x) { return Simpson_integral_solution(a, x, f, iterations) - b; };
	return Newton_solution(g, f, a);
}

double Simpson_integral_solution(double a, double b, func_pointer f, int n ) {

	double step =	(b - a) / (double) (2 * n);
	double sum[2] = { 0, 0 };
	double x = a;
	for (int i = 1; i < 2 * n; i++) {
		x += step;
		sum[ i % 2 ] += f(x);
	}

	return ( (b - a) / (double) (6 * n) ) * ( f(a) + f(b) + 2 * sum[0] + 4 * sum[1] );

}

double Newton_solution(func_pointer f, func_pointer der_f, double approximation){
	double x_seq, x_seq_new(approximation);
	int i = 1;
	do {
		x_seq = x_seq_new;
		x_seq_new = x_seq - f(x_seq) / der_f(x_seq);
		cout << "Iteration " << i << endl;
		cout << "   delta(x) " << abs(x_seq - x_seq_new) << endl;
		cout << "delta(f(x)) " << abs(f(x_seq) - f(x_seq_new)) << endl;
		i++;
		while (abs(f(x_seq_new)) > abs(f(x_seq)))
		{
			x_seq_new = (x_seq + x_seq_new) / (double)2;
		}

	} while (abs(x_seq - x_seq_new) > EPS || abs(f(x_seq) - f(x_seq_new)) > EPS);
	return x_seq_new;

}

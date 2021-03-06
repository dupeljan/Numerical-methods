// boundary_value_problem_shooting.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Solve boundary problem
//  _
// |y'' + p(x)*y'+q(x)*y=f(x)
// |y'(a) - alpha1 * y(a) = alpha2
// |y'(b) - betta1 * y(b) = betta2
// |_
// using shooting method
//

#include "pch.h"
#include "Adams_Cauchy_problem_system.h"
#include "shooting_method.h"

#include <iostream>
#include <functional>
#include <fstream>
#include <array>
#include <map>

#define EPS 1e-10
#define EX_N 3

#define FILE_OUTPUT_NAME "output"
#define FILE_DESK ".txt"

using namespace std;

/*
struct Parametrs {
	double t0;
	double a, b;
	array<double,2> alpha, betta;
	function<double(double)> f, q, p;
	int steps;
};
*/

Parametrs get_example() {
	/*put your example here*/
	Parametrs example;
#if EX_N == 0
	/*Filipov #767*/
	example.p = [](double x)->double { return 0; };
	example.q = [](double x)->double { return -1;  };
	example.f = [](double x)->double { return exp(x); };
	example.alpha = { 0,0 };
	example.betta = { 1,0 };
	example.a = 0;
	example.b = 2;
	example.steps = 70;
	example.t0 = 0.5;
#elif EX_N == 1
	example.p = [](double x)->double { return  x; };
	example.q = [](double x)->double { return cos(x);  };
	example.f = [](double x)->double { return sin(x); };
	example.alpha = { 0,0 };
	example.betta = { 0,0 };
	example.a = 1;
	example.b = 2;
	example.steps = 70;
	example.t0 = 0.5;
#elif EX_N == 2
	/*Filipov #770*/
	example.p = [](double x)->double { return  x; };
	example.q = [](double x)->double { return cos(x);  };
	example.f = [](double x)->double { return sin(x); };
	example.alpha = { 0,2 };
	example.betta = { 0,0 };
	example.a = -1;
	example.b = 2;
	example.steps = 70;
	example.t0 = 0.5;
#elif EX_N == 3
	/*Filipov #681*/
	example.p = [](double x)->double { return  4*x / (double) ( 2 * x + 1); };
	example.q = [](double x)->double { return  - 4 / (double)(2 * x + 1);  };
	example.f = [](double x)->double { return 0; };
	example.a = -4;
	example.b = -1;
	example.alpha = { -1,1 + example.a - exp(-2 * example.a) };
	example.betta = { -1,1 + example.b - exp(-2 * example.b) };
	example.steps = 70;
	example.t0 = 0.5;
#endif

	return example;
}

int main(){
	Shooting_method solver(get_example());
	solver.Newton_zero_of_target_function();
	auto result = solver.get_solution();
	cout << solver.get_iteration() << " iterations" << endl;
	
	fstream out;
	out.open(FILE_OUTPUT_NAME + string(FILE_DESK), fstream::out);
	for (auto & p : result)
		out << p.x << ' ' << p.y[0] << endl;
}
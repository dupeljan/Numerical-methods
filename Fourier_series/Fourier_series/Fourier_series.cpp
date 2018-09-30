// Fourier_series.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>

#define FILE_INPUT_PATCH "input.txt"
#define FILE_OUTPUT_PATCH "output.txt"
#define EPS 1e-12
using namespace std;

//
double T(double x, vector < double > v_x, vector < double > v_y);
//

int main()
{
	ifstream in;
	in.open(FILE_INPUT_PATCH);
	if (!in)
		return 1;

	//Ввод данных
	vector < double > x, y;
	int n = 0; // кол-во точек
	while (in) {
		double x_coord, y_coord;
		in >> x_coord >> y_coord;
		
		if (!in) {
			cout << "Input error";
			return 2;
		}
		
		if (find(x.begin(),x.end(),x_coord) != x.end() ) {  // If x isn't unique
			cout << "Function isn't single-valued";
			return 1;
		}
		x_coord = y_coord;

		x.push_back(x_coord);
		y.push_back(y_coord);
		n++;
	}

}

double T(double x, vector < double > v_x, vector < double > v_y) {
	double value(0); // Значение функции
	int n = v_x.size();
	for (int m = 0; m < n; m++) {
		double numerator(1), denominator(1); // Числитель, Знаменатель
		for (int k = 0; k < n; k++)
			if (k != m) {
				numerator *= sin((double)(x - v_x[k]) / 2);
				denominator *= sin((double)(v_x[m] - v_x[k]) / 2);
			}
		
		value += v_y[m] * (double)(numerator / denominator);
	}
	return value;
}
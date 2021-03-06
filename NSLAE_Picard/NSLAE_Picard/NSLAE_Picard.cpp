#include "pch.h"
#include "matrixproc.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <cmath>

#define INP_PATH "input.txt"
#define OUT_PATH "output.txt"
#define EPS 1e-8
#define SUP 1e5
#define TEST 1
using namespace std;
//
double norm(vector<double> x); // return absolute max value
vector < double > operator-(const vector<double>& v1);
vector < double > operator+(const vector<double>& v1, const vector<double>& v2);
vector < double > operator-(const vector<double>& v1, const vector<double>& v2);
//

class LUSolver {
	vector < vector < double > > L; //  Нижнетреугольная матрица с единич диагональю
	vector < vector < double > > U; //Верхнетреугольная матрица
public:	
	LUSolver(vector < vector < double > > a);
	vector<double> Solve( vector < double > b);
};

vector < double > g(vector< double > x) {
	vector < double > result;
	result.resize(x.size());
	// Add not linear part here
#if TEST == 1
	// Matrix
	// 1  1
	// 1 -1
	// F1
	result[0] = -1;
	// F2
	result[1] = -2;
#elif TEST == 2
	// Matrix
	// 1  1
	// 1 -1
	// F1
	result[0] = x[0] * x[0];
	// F2
	result[1] = -2;
#elif TEST == 3 
	// DIVERGES
	// Matrix
	// 1  0
	// 0  1
	// F1
	result[0] = x[1] * x[1] - 3;
	// F2
	result[1] = x[0] * x[0] - 3;

#elif TEST == 4 
	// Matrix
	// 1  1
	// 1 -1
	// F1
	result[0] = pow(x[0],4) ;
	// F2
	result[1] = -2;
#elif TEST == 5
	// Matrix
	// E
	// F1
	result[0] = (x[0] - 1)*(x[0] - 1) + cos(5 * x[0] * x[1]) - 1        /*Image->*/ - x[0];
	// F2
	result[1] = 2 * exp(x[2] - 1) + sin(x[0] + 1 - 2 * x[2] * x[2]) - 2 /*Image->*/ - x[1];  
	// F3
	result[2] = x[0] * x[0] + x[1] * x[1] - x[2]					    /*Image->*/ - x[2]; 
#elif TEST == 6
	// Matrix
	// E
	// F1
	result[0] = (x[0] - 1)*(x[0] - 1) + x[1] - 1 /*Image->*/ - x[0];
	// F2
	result[1] = x[0] - x[1] * x[1]			     /*Image->*/ - x[1];

#endif
	return result;
}

vector < double > get_aproach() {
	return { 0, 0};
}
/* for internal a input 
vector< vector < double > > get_a() {
	return { { },
			 { },
			 { }, };

}
*/
int main() {
	ifstream in; 
	in.open(INP_PATH, fstream::in);
	vector<double> data;
	
	// Read linear part of equation in one vector
		while (in) {
		double x;
		in >> x;
		data.push_back(x);
	}
	int n = sqrt(data.size());

	vector < vector < double > > a;
	// Rewrite in matrix
	a.resize(n);
	for (int i = 0; i < n; i++) {
		a[i].resize(n);
		for (int j = 0; j < n; j++)
			a[i][j] = data[i*n + j];
	}
	
	// Method
	LUSolver solver(a);
	vector < double > x, x_next;
	x = get_aproach();
	x_next = x;
	
	int i = 0;
	while ( ( norm(x - x_next) >= EPS || norm(composition<double>(a, x) + g(x)) >= EPS  ) && i < SUP ) {
		x = x_next;
		x_next = solver.Solve(-g(x));
		i++;
	}		
	
	// Output
	fstream out;
	out.open(OUT_PATH, fstream::out);
	out << ( (i == SUP)? "Diverge" :"Solution:" ) << endl;
	for (int i = 0; i < x_next.size(); i++ )
		out <<"x["<< i << "]= "<< x_next[i] << '\n';
	out << "Iteration count: " << i;

}

// return absolute max value
double norm(vector<double> x) {
	for (int i = 0; i < x.size(); i++)
		x[i] = abs(x[i]);
	return *max_element(x.begin(), x.end());
}



vector < double > operator+(const vector<double>& v1, const vector<double>& v2) {
	vector < double > result;
	result.resize(v1.size());
	for (int i = 0; i < v1.size(); i++)
		result[i] = v1[i] + v2[i];
	return result;
}

vector < double > operator-(const vector<double>& v1, const vector<double>& v2) {
	vector < double > result;
	result.resize(v1.size());
	for (int i = 0; i < v1.size(); i++)
		result[i] = v1[i] - v2[i];
	return result;
}

vector < double > operator-(const vector<double>& v1) {
	vector < double > result;
	result.resize(v1.size());
	for (int i = 0; i < v1.size(); i++)
		result[i] = -v1[i];
	return result;
}


vector<double> LUSolver::Solve(vector < double > b) {
	/*
	vector < vector < double > > a = file.getA(); //Матрица A
	vector < double > b(file.getB()), x(file.getX());		//Вектора x,b
	int n = file.getN();						//Размерность
	*/
	int n = b.size();
	vector < double > x;
	
	//Инициализация
	x.resize(n);
	
	// Ly = b
	vector < double > y;
	y.resize(n);
	//Найдем y
	for (int i = 0; i < n; i++) { // Выбираем y
		y[i] = b[i];
		for (int k = 0; k < i; k++)
			y[i] -= L[i][k] * y[k];
	}

	//Ux = y
	for (int i = n - 1; i >= 0; i--) {
		x[i] = y[i];
		for (int k = i + 1; k < n; k++)
			x[i] -= U[i][k] * x[k];
		if (abs(U[i][i]) > EPS)
			x[i] /= U[i][i];
		else {
			cout << "error" << '\n';
			return {};
		}
	}

	return x;
}

LUSolver::LUSolver(vector<vector<double>> a){
	int n = a.size();
	// Инициализация
	L.resize(n);
	U.resize(n);

	for (int i = 0; i < n; i++) {
		L[i].resize(n);
		U[i].resize(n);
		L[i][i] = 1; //В L единичная диагональ
	}

	//Вычисление матриц L и U
	for (int i = 0; i < n; i++) {
		//Вычисляем строку U[i][...]
		for (int j = i; j < n; j++) { //Выбираем элемент строки U[i][...]
			U[i][j] = a[i][j];		  //Вычисляем его (2.9)
			for (int k = 0; k < i; k++)
				U[i][j] -= L[i][k] * U[k][j];
		}
		//Вычисляем столбец L[...][i]
		//Замена: i столбцов и j строк 
		for (int j = i + 1; j < n; j++) { //Выбираем элемент столбца L[...][i]
			L[j][i] = a[j][i];			  //Вычисляем его (2.10)
			for (int k = 0; k < i; k++)
				L[j][i] -= L[j][k] * U[k][i];
			if (abs(U[i][i]) > EPS)
				L[j][i] /= U[i][i];
			else {
				cout << "Error";
			}
		}

	}
}

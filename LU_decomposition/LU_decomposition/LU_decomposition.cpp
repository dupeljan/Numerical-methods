// LU_decomposition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "SLE_input.h"
#include "vectorProc.h"

#define FILE_INPUT_PATCH "input.txt"
#define FILE_OUTPUT_PATCH "output.txt"
#define EPS 1e-12
using namespace std;


int main()
{
	SLE_input file(FILE_INPUT_PATCH);
	vector < vector < double > > a = file.getA(); //Матрица A
	vector < double > b ( file.getB()), x( file.getX() );		//Вектора x,b
	int n = file.getN();						//Размерность
	vector < vector < double > > L; //  Нижнетреугольная матрица с единич диагональю
	vector < vector < double > > U; //Верхнетреугольная матрица
	

	//Инициализация
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
			if ( abs(U[i][i]) > EPS )
				L[j][i] /= U[i][i];
			else {
				cout << "Error";
				return 1;
			}
		}
		
	}

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
		if ( abs(U[i][i]) > EPS )
			x[i] /= U[i][i];
		else {
			cout << "error" << '\n';
			return 1;
		}
	}

	ofstream out;
	out.open(FILE_OUTPUT_PATCH, fstream::out);
	/*out << "input" << '\n';
	output(a, out);
	output(b, out);
	*/
	out << "L" << '\n';
	output(L,out);
	out <<'\n'<< "U" << '\n';
	output(U,out);
	//out << '\n' << "res" << '\n';
	//output( composition(L, U) , out );
	out << '\n' << "x:" << '\n'; 
	output(x,out);
	
	cout << "success!" << '\n';
	system("pause");
    
}


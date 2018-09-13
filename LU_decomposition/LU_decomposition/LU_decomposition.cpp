// LU_decomposition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "SLE_input.h"
#include "vectorProc.h"
using namespace std;


int main()
{
	SLE_input file("input.txt");
	vector < vector < float > > a = file.getA(); //Матрица A
	vector < float > b ( file.getB_X()[0]), x(file.getB_X()[1]);		//Вектора x,b
	int n = file.getN();						//Размерность
	vector < vector < float > > L; //  Нижнетреугольная матрица с единич диагональю
	vector < vector < float > > U; //Верхнетреугольная матрица
	
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
			L[j][i] /= U[i][i];
		}
		
	}

	

	cout << "L" << '\n';
	output(L);
	cout << "U" << '\n';
	output(U);
	cout << "res" << '\n';
	output( composition(L, U) );
	

	system("pause");
    
}


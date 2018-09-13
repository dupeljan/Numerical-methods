// Number_method.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Ax=B
#include "pch.h"
#include "SLE_input.h"
#include <iostream>
#include <vector>

using namespace std;
int main()
{
	SLE_input file("input.txt");
	vector < vector < float > > a = file.getA(); //Матрица A
	vector < float > b(file.getB_X()[0]), x(file.getB_X()[1]);		//Вектора x,b
	int n = file.getN();						//Размерность
		
	//Прямой ход метода Гауса
	for ( int k = 0; k < n - 1; k++ )				
		for (int i = k + 1; i < n; i++) {
			float div = (float) a[i][k] / a[k][k];		
			b[i] -= div * b[k];
			for (int j = k; j < n; j++)
				a[i][j] -= div * a[k][j];
		}
	
	//Обратный ход метода Гауса
	x[n - 1] = (float) b[n - 1] / a[n - 1][n - 1];   // Вычисляем x[n]
	for (int i = n - 2; i >= 0; i--) {
		int sum = b[i];					//Сумма переноса вправо для очередной строки
		for (int j = i + 1; j < n; j++)
			sum -= a[i][j] * x[j];      
		x[i] = (float)sum / a[i][i];

	}
		
	for ( int i = 0; i < n; i++)
		cout << "x[" << i << "]= " << x[i] << '\n' ;

	system("pause");
}

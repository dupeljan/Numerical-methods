// Number_method.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Ax=B
#include "pch.h"
#include "SLE_input.h"
#include "vectorProc.h"
#include <iostream>
#include <vector>

#define EPS 1e-10
#define PATCH "input.txt"

using namespace std;
int main()
{
	SLE_input file(PATCH);
	vector < vector < double > > a = file.getA(); //Матрица A
	vector < double > b(file.getB_X()[0]), x(file.getB_X()[1]);		//Вектора x,b
	int n = file.getN();						//Размерность
		
	//Прямой ход метода Гауса
	for ( int k = 0; k < n - 1; k++ )				
		for (int i = k + 1; i < n; i++) {
			//double div = (double) a[i][k] / a[k][k];		
			double div;
			if (abs(a[k][k]) > EPS)
				div = (double) a[i][k] / a[k][k];		
			else {
				cout << "System linear depended";
				return 1;
			}
			
			b[i] -= div * b[k];
			for (int j = k; j < n; j++)
				a[i][j] -= div * a[k][j];
		}
	//Вывод диагональной матрицы
	output(a);
	//Проверка на вырожденность
	for( int i = 0; i < n; i++)
		if (a[i][i] == 0) {
			cout << "|A|=0 ";
			return 1;
		}
	
	//Обратный ход метода Гауса
	x[n - 1] = (double) b[n - 1] / a[n - 1][n - 1];   // Вычисляем x[n]
	for (int i = n - 2; i >= 0; i--) {
		int sum = b[i];					//Сумма переноса вправо для очередной строки
		for (int j = i + 1; j < n; j++)
			sum -= a[i][j] * x[j];  
		
		if ( abs ( a[i][i] ) > EPS )
			x[i] = (double)sum / a[i][i];
		else {
			cout << "Method not work ";
			return 1;
		}
		
		

	}
		
	for ( int i = 0; i < n; i++)
		cout << "x[" << i << "]= " << x[i] << '\n' ;

	system("pause");
}

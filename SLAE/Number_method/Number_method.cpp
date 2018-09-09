// Number_method.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Ax=B
#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;
int main()
{
	vector < vector < float > > a; //Матрица A
	vector < float > x, b;		//Вектора x,b
	int n;						//Размерность
	cout << "n= ";
	cin >> n;
	
	//Заполнение матрицы
	a.resize(n); 
	for (int i = 0; i < n; i++) {
		a[i].resize(n);
		for (int j = 0; j < n; j++) {
			cout << "a[" << i << ',' << j << "]= ";
			cin >> a[i][j];
		}
	}

	//Заполнение столбца свободных членов
	b.resize(n);
	for (int i = 0; i < n; i++) {
		cout << "b[" << i << "]= ";
		cin >> b[i];
	}

	//Инициализация вектора x

	x.resize(n);
		
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

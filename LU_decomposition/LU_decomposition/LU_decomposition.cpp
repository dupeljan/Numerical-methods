// LU_decomposition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "SLE_input.h"
using namespace std;

int main()
{
	SLE_input file("input.txt");
	vector < vector < float > > a = file.getA(); //Матрица A
	vector < float > b ( file.getB_X()[0]), x(file.getB_X()[1]);		//Вектора x,b
	int n = file.getN();						//Размерность
	
	a[0][0] = 0;

	
    
}


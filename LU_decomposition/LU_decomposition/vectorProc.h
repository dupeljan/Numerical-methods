#pragma once
#ifndef _vectorProc_H_
#define _vectorProc_H_
#include <vector>
#include <iostream>
using namespace std;

void output(vector< vector < float > > v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			cout << v[i][j] << ' ';
		}
		cout << '\n';
	}
}

//Умножение квадратных матриц
vector < vector < float > > composition(vector < vector < float > > a, vector < vector < float > > b) {
	int n = a.size();
	vector < vector < float > > res;
	res.resize(n);
	for (int i = 0; i < n; i++){
		res[i].resize(n);
		for (int j = 0; j < n; j++)  // Выбираем элемент res
			for (int k = 0; k < n; k++) //суммируем произведения
				res[i][j] += a[i][k] * b[k][j];
	}
	return res;
}

#endif;
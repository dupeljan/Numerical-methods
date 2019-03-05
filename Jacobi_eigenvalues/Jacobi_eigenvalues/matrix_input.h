#ifndef MATRIX_INP
#define MATRIX_INP
#include "pch.h"
#include <vector>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

template<class T>
vector<vector<T>> input_matrix(string patch) {
	ifstream file;
	file.open(patch);
	vector <T> data;
	//Читаем все в x
	T x;
	while (file) {
		file >> x;
		data.push_back(x);
	}
	//Вычисляем n

	int n = sqrt(data.size());

	vector<vector<T>> result;
	result.resize(n);

	for (int i = 0; i < n; i++) {
		result[i].resize(n);
		for (int j = 0; j < n; j++)
			result[i][j] = data[ i*n + j];		
	}

	return result;
}


#endif
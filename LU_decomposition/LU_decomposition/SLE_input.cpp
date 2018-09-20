#include "pch.h"
#include "SLE_input.h"
#include <iostream>
#include <string>
#include <sstream>

SLE_input::SLE_input(const char* patch){
	
	file.open(patch);
	std::vector < double > data;
	//Читаем все в x
	double x;
	while (file) {
		file >> x;
		data.push_back(x);
	}
	//Вычисляем n

	n = ( sqrt(1 + 4 * data.size()) - 1 ) / 2;
	
	int point = 0;
	
	a.resize(n);
	b.resize(n);
	
	for (int i = 0; i < n; i++) {
		a[i].resize(n);
		for (int j = 0; j < n; j++)
			a[i][j] = data[point + j];
		point += n;
		b[i] = data[point];
		point++;
	}
}




#include "pch.h"
#include "SLE_input.h"


SLE_input::SLE_input(const char* patch){
	
	file.open(patch);

	file >> n;

	//Заполнение матрицы
	a.resize(n);
	for (int i = 0; i < n; i++) {
		a[i].resize(n);
		for (int j = 0; j < n; j++) {
			file >> a[i][j];
		}
	}

	//Заполнение столбца свободных членов
	b.resize(n);
	for (int i = 0; i < n; i++) {
		file >> b[i];
	}

	//Инициализация вектора x

	x.resize(n);
}

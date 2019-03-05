#include "pch.h"
#include <iostream>
#include <vector>
#include "matrix_input.h"
#include "Jacobi_eig_method.h"

#define INPUT_PATCH "input.txt"

using namespace std;

int main(){
	Jacobi_eig_method<double> solver(input_matrix<double>(INPUT_PATCH));
	solver.solve();
	vector<vector<double>> solution = solver.solution();
	for (int i = 0; i < solution.size(); i++) {
		for (int j = 0; j < solution.size(); j++)
			cout << solution[i][j] << ' ';
		cout << endl;
	}
}


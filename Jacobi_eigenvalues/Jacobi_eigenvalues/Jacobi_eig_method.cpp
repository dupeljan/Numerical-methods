#include "pch.h"
/*
#include "Jacobi_eig_method.h"


template<class T>
Jacobi_eig_method<T>::Jacobi_eig_method(vector<vector<T>> A) {
	this->A = A;
	this->n = A.size();
	this->eps = EPS;
}

template<class T>
pair<int, int> Jacobi_eig_method<T>::key_elem(){
	//Just find lagest element a[i][j], i != j
	T max_ = A[0][1];
	pair<int, int> result = make_pair(0,1);
	for( int i = 0; i < n; i++)
		for( int j = 0; j < n; j++)
			if (i != j) 
				if (max_ < A[i][j]) {
					max_ = A[i][j];
					result.first = i;
					result.second = j;
				}

	return result;
}

template<class T>
vector<vector<T>> Jacobi_eig_method<T>::solution() {
	return B;
}

template<class T>
int Jacobi_eig_method<T>::sign(T val){
	return (eps < val) - (val < eps);
}

template<class T>
T Jacobi_eig_method<T>::Frobenius_norm(vector<vector<T>> m){
	T sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j)
				sum += abs(m[i][j]);
	return sum;
}

template<class T>
bool Jacobi_eig_method<T>::breaking_criterion(){
	return (Frobenius_norm(B) < eps);
}

template<class T>
void Jacobi_eig_method<T>::solve(){
	// Вержбитский, p 165
	T p, q, d, r, s, c;
	vector<vector<T>> A = this->A; // Local matrix
	do {
		//Iteraton body
		pair<int, int> key = key_elem();
		int i = key.first, j = key.second;
		//Compute auxiliary coefficients
		p = 2 * A[i][j];
		q = A[i][i] - A[j][j];
		d = sqrt(p*p + q*q);
		if (q > eps) {
			r = abs(q) / T(2 * d);
			c = sqrt(0.5 + r);
			if (abs(p / T(q)) < eps)
				s = abs(p) * sign(p * q) / T(2 * c * d);
			else
				s = sqrt(0.5 - r) * sign(p * q);
		}
		else
			c = s = sqrt(2) / T(2);
		//compute new matrix
		B = A;
		B[i][i] = c * c * A[i][i] + s * s * A[j][j] + 2 * c * s * A[i][j];
		B[j][j] = c * c * A[i][i] + s * s * A[j][j] - 2 * c * s * A[i][j];
		B[i][j] = B[j][i] = 0;
		for (int m = 0; m < n; m++) 
			if ( m != i && m != j){
				B[i][m] = B[m][i] = c * A[m][i] + s * A[m][j];
				B[j][m] = B[m][j] =-s * A[m][i] + c * A[m][j];
			}
		//Prepare to new iteration
		A = B;

	} while (!breaking_criterion());
}

*/




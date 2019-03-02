#ifndef JACOBI_EIG_METHOD
#define JACOBI_EIG_METHOD
#include <vector>
#include <math.h>
#include <utility>

#define EPS 1e-15

using namespace std;

//implement of Jacobi eigenvalues alg
template<class T>
class Jacobi_eig_method
{
	int n
	vector < vector<T> > A, B;
	double eps;
	//Methods
	pair<int, int> key_elem();
	int sign(T val);
	T Frobenius_norm(vector<vector<T>> m);
	bool breaking_criterion();
public:
	Jacobi_eig_method(vector<vector<T>> A);
	void solve();

};



#endif
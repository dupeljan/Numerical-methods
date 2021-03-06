#ifndef MATRIXPROC_H
#define MATRIXPROC_H
#include <vector>
using namespace std;
//��������� ���������� ������
template <class T>
vector < vector < T > > composition(vector < vector < T > > a, vector < vector < T > > b) {
	int n = a.size();
	vector < vector < T > > res;
	res.resize(n);
	for (int i = 0; i < n; i++) {
		res[i].resize(n);
		for (int j = 0; j < n; j++)  // �������� ������� res
			for (int k = 0; k < n; k++) //��������� ������������
				res[i][j] += a[i][k] * b[k][j];
	}
	return res;
}

template <class T>                                    // ������� �� �������
vector < T > composition(vector < vector < T > > a, vector < T > b) {
	int n = a.size();
	vector < T > res;
	res.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i] += a[i][j] * b[j];
	return res;
}

template <class T>// ������ �� �������
vector < T > composition(vector < T > a, vector < vector < T > > b) {
	int n = a.size();
	vector < T > res;
	res.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)  // �������� ������� res
			res[i] += a[j] * b[j][i];

	return res;
}

template <class T>
T composition(vector < T > a, vector < T > b) {
	T result = 0;
	for (int i = 0; i < a.size(); i++)
		result += a[i] * b[i];
	return result;
}
#endif // MATRIXPROC_H
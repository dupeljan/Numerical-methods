#ifndef ADAMS_CAUCHY_PROBLEM_SYSTEM
#define ADAMS_CAUCHY_PROBLEM_SYSTEM
#include <functional>
#include <vector>
#include <array>

#define EPS 1e-10
#define ACCURACY_ORDER 4

using namespace std;

typedef function<vector<double>(double, vector<double>)> func_pointer;
struct point {
	double x;
	vector<double> y;
	point(double x = 0, vector<double> y = {}) { this->x = x; this->y = y; }
};
//
vector<point> Adams_method_Cauchy_solution(double a, double b, vector<double> y0, func_pointer f, int steps);
vector<double> fixed_point_iteration(vector<double> x, function<vector<double>(vector<double>)> f, double eps);
vector<point> Runge_Kutta_Cauchy_solution(double a, double b, vector<double> y0, func_pointer f, int steps);
vector<double> Simpson_integral_solution(point a, point b, func_pointer f);
double error(function<double(double)> f, vector<point> res);
double norm(vector<double>x);
//
vector<double> operator+(vector<double> lhs, const vector<double>& rhs) {
	int size = min(lhs.size(), rhs.size());
	vector<double> result(size);
	for (int i = 0; i < size; i++)
		result[i] = lhs[i] + rhs[i];
	return result;
}

vector<double> operator-(vector<double> lhs, const vector<double>& rhs) {
	int size = min(lhs.size(), rhs.size());
	vector<double> result(size);
	for (int i = 0; i < size; i++)
		result[i] = lhs[i] - rhs[i];
	return result;
}

vector<double> operator*(double lhs,vector<double> rhs) {
	vector<double> result(rhs.size());
	for (int i = 0; i < rhs.size(); i++)
		result[i] = lhs * rhs[i];
	return result;
}

vector<double> operator*(vector<double> lhs,double rhs) {
	return rhs * lhs;
}

vector<double> operator/(vector<double> lhs,double rhs) {
	vector<double> result(lhs.size());
	for (int i = 0; i < lhs.size(); i++)
		result[i] = lhs[i] / rhs;
	return result;
}


vector<double> Simpson_integral_solution(point a, point b, func_pointer f) {
	array<vector<double>, 4> k;
	double h = abs(b.x - a.x);
	k[0] = f(a.x, a.y);
	k[1] = f(a.x + h / (double)2, a.y + h * k[0] / (double)2);
	k[2] = f(a.x + h / (double)2, a.y + h * k[1] / (double)2);
	k[3] = f(a.x + h, a.y + h * k[2]);
	return (k[0] + 2 * k[1] + 2 * k[2] + k[3]) * h / (double)6;
}

vector<point> Runge_Kutta_Cauchy_solution(double a, double b, vector<double> y0, func_pointer f, int steps) {
	vector<point> result(steps + 1);

	result[0].x = a;
	result[0].y = y0;

	double h = abs(b - a) / double(steps);

	for (int i = 1; i <= steps; i++) {
		result[i].x = a + i * h;
		result[i].y = result[i - 1].y + Simpson_integral_solution(result[i - 1], result[i], f);
	}

	return result;
}

vector<point> Adams_method_Cauchy_solution(double a, double b, vector<double> y0, func_pointer f, int steps) {
	steps = max(ACCURACY_ORDER, steps);
	vector<point> result(steps + 1);

	double h = abs(b - a) / double(steps);

	function<vector<double>(vector<point>)> Adams_poly = [f, h](vector<point> p) {
		array<double, 5> c = { 251, 646, -264, 106, -19 };
		for_each(c.begin(), c.end(), [](double &n) { n /= (double)720; });
		vector<double> res(p[0].y.size());
		for (int i = 0; i < p.size(); i++)
			res = res + c[i] * f(p[i].x, p[i].y);
		return h * res;
	};

	auto p = Runge_Kutta_Cauchy_solution(a, a + (ACCURACY_ORDER - 1) * h, y0, f, (ACCURACY_ORDER - 1));
	copy(p.begin(), p.end(), result.begin());

	for (int i = ACCURACY_ORDER; i <= steps; i++) {
		result[i].x = a + i * h;
		vector<double> y_pred = result[i - 1].y;
		function<vector<double>(vector<double>)> iter_func = [Adams_poly, result, a, h, i, y_pred](vector<double> y) {
			return y_pred + Adams_poly({ point(a + i * h,y),result[i - 1],result[i - 2],result[i - 3],result[i - 4] });
		};
		result[i].y = fixed_point_iteration(y_pred, iter_func, EPS);
	}

	return result;
}

vector<double> fixed_point_iteration(vector<double> x, function<vector<double>(vector<double>)> f, double eps) {
	vector<double> next = f(x);
	return (norm(next - x) < eps) ? next : fixed_point_iteration(next, f, eps);
}

double norm(vector<double>x) {
	double result(0);
	for (auto &i : x)
		result += abs(i);
	return result;
}
double error(function<vector<double>(double)> f, vector<point> res) {
	double result = 0;
	for (auto &x : res)
		result = max(result, norm(f(x.x) - x.y));
	return result;
}
#endif // ADAMS_CAUCHY_PROBLEM_SYSTEM

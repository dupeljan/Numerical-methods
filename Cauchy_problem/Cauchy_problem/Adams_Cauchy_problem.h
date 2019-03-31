#ifndef ADAMS_CAUCHY_PROBLEM
#define ADAMS_CAUCHY_PROBLEM
#include <functional>
#include <vector>
#include <array>

using namespace std;

typedef function<double(double,double)> func_pointer;
struct point{
	double x, y;
	point(double x = 0, double y = 0) { this->x = x; this->y = y; }
};

double Simpson_integral_solution(point a, point b, func_pointer f) {
	array<double, 4> k;
	double h = abs(b.x - a.x);
	k[0] = f(a.x, a.y);
	k[1] = f(a.x + h / (double)2, a.y + h * k[0] / (double)2);
	k[2] = f(a.x + h / (double)2, a.y + h * k[1] / (double)2);
	k[3] = f(a.x + h, a.y + h * k[2]);
	return (k[0] + 2 * k[1] + 2 * k[2] + k[3]) * h / (double)6;
}

vector<point> Runge_Kutta_Cauchy_solution(double a, double b, double y0, func_pointer f, int steps) {
	vector<point> result(steps+1);

	result[0].x = a;
	result[0].y = y0;

	double h = abs(b - a) / double(steps);

	for (int i = 1; i <= steps; i++) {
		result[i].x = a + i * h;
		result[i].y = result[i - 1].y + Simpson_integral_solution(result[i-1], result[i], f);
	}

	return result;
}

#endif // ADAMS_CAUCHY_PROBLEM

#ifndef SHOOTING_METHOD
#define SHOOTING_METHOD

#include <iostream>
#include <vector>
#include <functional>
#include <array>
#include <map>

using namespace std;

struct Parametrs {
	double t0;
	double a, b;
	array<double, 2> alpha, betta;
	function<double(double)> f, q, p;
	int steps;
};

class Shooting_method {
	map<double, double> buffer;
	double a, b;
	array<double, 2> alpha, betta;
	double t0;
	function<double(double)>f, q, p;
	int steps;
	int iteration;

	double target(double x);
	vector<point> get_local_Cauchy_solution(double x);
public:
	Shooting_method(Parametrs p) {
		a = p.a;
		b = p.b;
		alpha = p.alpha;
		betta = p.betta;
		this->f = p.f;
		this->p = p.p;
		this->q = p.q;
		steps = p.steps;
		t0 = p.t0;
	};

	void Newton_zero_of_target_function();
	vector<point> get_solution() {
		return get_local_Cauchy_solution(t0);
	};

	int get_iteration() {
		return iteration;
	};


};


double Shooting_method::target(double x) {
	{
		auto _ = buffer.find(x);
		if (_ != buffer.end())
			return _->second;
	}

	auto solut = get_local_Cauchy_solution(x);

	// buff result
	auto y = find_if(solut.begin(), solut.end(), [this](point i) {return i.x == b; });
	auto result = y->y[1] - betta[0] * y->y[0] - betta[1];
	buffer.insert(make_pair(x, result));
	return result;

};

vector<point> Shooting_method::get_local_Cauchy_solution(double x) {

	auto g = [this](double x, vector<double> y) -> vector<double> {
		return { y[1],
				 f(x) - q(x) * y[0] - p(x) * y[1] };
	};
	return Adams_method_Cauchy_solution(a, b, \
	{x, alpha[0] * x + alpha[1]}, g, steps);
}

void Shooting_method::Newton_zero_of_target_function() {
	function<double(double)> derivative = [this](double x) {
		return (target(x + EPS) - target(x)) / double(EPS);
	};
	double x_seq, x_seq_new(t0);
	iteration = 0;
	do {
		x_seq = x_seq_new;
		x_seq_new = x_seq - target(x_seq) / double(derivative(x_seq));
		while (abs(target(x_seq_new)) > abs(target(x_seq)))
		{
			x_seq_new = (x_seq + x_seq_new) / double(2);
		}
		iteration++;
	} while (abs(x_seq - x_seq_new) > EPS || abs(target(x_seq) - target(x_seq_new)) > EPS);
	//return x_seq_new;
	t0 = x_seq_new;
};


#endif //SHOOTING_METHOD

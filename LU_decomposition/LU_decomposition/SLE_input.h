#pragma once
#include <fstream>
#include <vector>

class SLE_input
{
	std::ifstream file;
	int n;
	std::vector < std::vector <double> > a;
	std::vector < double > b;
public:
	SLE_input(const char* );
	std::vector < std::vector <double> > getA() { return a; }
	std::vector <double>  getB() { return b; }
	std::vector <double>  getX() { 
		std::vector<double> x;
		x.resize(n);
		return x;
	}
	int getN() { return n; }
	
};


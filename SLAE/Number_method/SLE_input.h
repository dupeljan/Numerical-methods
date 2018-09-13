#pragma once
#include <fstream>
#include <vector>

class SLE_input
{
	std::ifstream file;
	int n;
	std::vector < std::vector <double> > a;
	std::vector < double > b, x;
public:
	SLE_input(const char* );
	std::vector < std::vector <double> > getA() { return a; }
	std::vector < std::vector <double> > getB_X() { return { b, x }; }
	double getN() { return n; }
	
};


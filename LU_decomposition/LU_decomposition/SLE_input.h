#pragma once
#include <fstream>
#include <vector>

class SLE_input
{
	std::ifstream file;
	int n;
	std::vector < std::vector <float> > a;
	std::vector < float > b, x;
public:
	SLE_input(const char* );
	std::vector < std::vector <float> > getA() { return a; }
	std::vector < std::vector <float> > getB_X() { return { b, x }; }
	float getN() { return n; }
	
};


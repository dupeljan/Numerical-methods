#ifndef EXPANSION_H
#define EXPANSION_H

#define FILE_INPUT_PATCH "/home/dupeljan/qt/Fourier\ series/Fourier_series/input.txt"
#define FILE_OUTPUT_PATCH "/home/dupeljan/qt/Fourier\ series/output.txt"
#define EPS 1e-12
#define DELTA 1e-2


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

class expansion
{
    vector < double > x, y; //Заданные точки

public:
    expansion();
    double T(double x);
} ;

#endif // EXPANSION_H

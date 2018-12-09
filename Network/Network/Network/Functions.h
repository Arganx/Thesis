#pragma once
#include <vector> 
class Functions
{
public:
	Functions();
	~Functions();
	void normalise(std::vector <std::vector<std::vector<double>>> &values,double max);
	double f(double x, double y);
	double fRand(double fMin, double fMax);
};


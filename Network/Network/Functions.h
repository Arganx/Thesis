#pragma once
#include <vector> 
class Functions
{
public:
	Functions();
	~Functions();
	void normalise(std::vector <std::vector<std::vector<double>>> &values,double max);
};


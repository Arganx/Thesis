#include "Functions.h"



Functions::Functions()
{
}


Functions::~Functions()
{
}

void Functions::normalise(std::vector<std::vector<std::vector<double>>>& values, double max)
{
	for (int i = 0; i < values.size(); i++)
	{
		for (int j = 0; j < values[i].size(); j++)
		{
			for (int k = 0; k < values[i][j].size(); k++)
			{
				values[i][j][k] = values[i][j][k] / max;
			}
		}
	}
}

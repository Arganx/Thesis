#include "ProbabilityNeuron.h"
#include <math.h>



ProbabilityNeuron::ProbabilityNeuron(int numberOfInputs, std::vector<double> values, double sigma)
{
	this->numberOfInputs = numberOfInputs;
	this->values = values;
	this->sigma = sigma;
}

ProbabilityNeuron::ProbabilityNeuron()
{
}



double ProbabilityNeuron::calculateSimilarityRate(std::vector<double> input)
{
	if (input.size() != numberOfInputs)
	{
		return -1;
	}
	double result = 0;
	for (int i = 0; i<numberOfInputs; i++)
	{
		result += pow(input[i] - values[i], 2);
	}
	result = result*-1;
	result = result / (2 * sigma*sigma);
	result = exp(result);
	return result;
}

ProbabilityNeuron::~ProbabilityNeuron()
{
	
}

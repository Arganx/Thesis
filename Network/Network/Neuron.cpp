#include "Neuron.h"
#include <time.h> 
#include <stdlib.h> 
#include <iostream>
#include <iostream>


double Neuron::activationFunction(double number)
{
	//return number;
	return(2 / (1 + pow(exp(1), -2 * number))) - 1;
	//if (number >= 0.0)
	//{
	//	return number;
	//}
	//else
	//{
	//	return 0.01*number;
	//}
}

double Neuron::activationDerrivative(double number)
{
	//return 1.0;
	return 1 - pow(activationFunction(number), 2);
	//if (number >= 0.0)
	//{
	//	return 1;
	//}
	//else
	//{
	//	return 0.01;
	//}
}

double Neuron::sum(std::vector<double> inputs)
{
	if (inputs.size() != this->numberOfInputs)
	{
		std::cout << "Wrong input" << std::endl;
		return -1;
	}
	double sum = 0;
	for (int i = 0; i < numberOfInputs; i++)
	{
		sum += inputs[i] * weights[i];
	}
	sum += biasWeight;
	return sum;
}

double fRand(double fMin, double fMax)
{

	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

Neuron::Neuron()
{
	numberOfInputs = 0;
}

Neuron::Neuron(int numberOfInputs, double lr)
{

	this->numberOfInputs = numberOfInputs;
	this->lr = lr;

	for (int i = 0; i < numberOfInputs; i++)
	{
		weights.push_back(fRand(-1.0,1.0));
	}
	biasWeight = fRand(-1.0, 1.0);
	error = 0.0;
}

Neuron::~Neuron()
{
	
}

double Neuron::guess(std::vector<double> inputs)
{
	if (inputs.size() != this->numberOfInputs)
	{
		std::cout << "Wrong input" << std::endl;
		return -1;
	}
	double sum = 0;
	for (int i = 0; i < numberOfInputs; i++)
	{
		sum += inputs[i] * weights[i];
	}
	sum += biasWeight;
	return activationFunction(sum);
	
}

void Neuron::train(std::vector<double> inputs, double expected)
{
	if (this->numberOfInputs != inputs.size())
	{
		std::cout << "Can not train" << std::endl;
		return;
	}
	double result = guess(inputs);
	double error = expected - result;
	for (int i = 0; i < numberOfInputs; i++)
	{
		weights[i] += error*lr*inputs[i];
	}
	biasWeight += error*lr;
}


void Neuron::show()
{
	std::cout << "Wagi: " << std::endl;
	for (int i = 0; i < numberOfInputs; i++)
	{
		std::cout << weights[i] << std::endl;
	}
	std::cout << "Waga biasu:" << std::endl << biasWeight << std::endl;
}

void Neuron::setNumberOfInputs(int number)
{
	if (numberOfInputs == 0)
	{
		this->numberOfInputs = number;
		for (int i = 0; i < numberOfInputs; i++)
		{
			weights.push_back(fRand(-1.0, 1.0));
		}
	}
}

void Neuron::setBiasWeight()
{
	biasWeight = fRand(-1.0, 1.0);
}

void Neuron::setWeights(std::vector<double> weights)
{
	if (this->weights.size() != weights.size())
	{
		std::cout << "Error assigning weights" << std::endl;
		return;
	}
	this->weights = weights;
}

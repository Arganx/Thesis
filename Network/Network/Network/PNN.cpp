#include "PNN.h"
#include <iostream>
#include "ProbabilityNeuron.h"
#include <iostream>




int PNN::max(std::vector<double> input)
{
	double max = input[0];
	int result = 0;
	for (int i = 1; i<pointsInEachClass.size(); i++)
	{
		if (max<input[i])
		{
			max = input[i];
			result = i;
		}
	}
	return result + 1;
}

PNN::PNN(int numberOfInputs, std::vector <std::vector<std::vector<double>>> pointsInEachClass)
{
	this->numberOfInputs = numberOfInputs;
	this->pointsInEachClass = pointsInEachClass;
	neurons = new ProbabilityNeuron*[pointsInEachClass.size()];
	std::cout << "Size 1: " << pointsInEachClass.size() << std::endl;
	for (int i = 0; i<pointsInEachClass.size(); i++)
	{
		neurons[i] =new ProbabilityNeuron[pointsInEachClass[i].size()];
		std::cout << "Size 2: " << pointsInEachClass[i].size() << std::endl;
		for (int j = 0; j<pointsInEachClass[i].size(); j++)
		{
			neurons[i][j].setNumberOfInputs(numberOfInputs);
			neurons[i][j].setSigma(0.1);
			neurons[i][j].setValues(pointsInEachClass[i][j]);
			std::cout << neurons[i][j].getNumberOfInputs() << std::endl;
		}
	}

}


PNN::~PNN()
{
	for (int i = 0; i<pointsInEachClass.size(); i++)
	{
		delete[] neurons[i];
	}
	delete[] neurons;
}

void PNN::SchowNeuronValues()
{
	for (int i = 0; i<pointsInEachClass.size(); i++)
	{
		for (int j = 0; j<pointsInEachClass[i].size(); j++)
		{
			for (int k = 0; k < pointsInEachClass[i][j].size(); k++)
			{
				std::cout << neurons[i][j].getValues()[k] << std::endl;
			}
			std::cout << std::endl;
		}
	}
}

int PNN::classify(std::vector<double> inputs)//TODO memory
{
	if (inputs.size() != numberOfInputs)
	{
		return -1;
	}
	std::vector<double> probability;
	for (int i = 0; i<pointsInEachClass.size(); i++)
	{
		probability.push_back(0);
		for (int j = 0; j<pointsInEachClass[i].size(); j++)
		{
			probability[i] += neurons[i][j].calculateSimilarityRate(inputs);
		}
	}
	return this->max(probability);
}

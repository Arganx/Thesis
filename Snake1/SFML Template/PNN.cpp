#include "PNN.h"
#include <iostream>
#include "ProbabilityNeuron.h"
#include <fstream>
#include <string>




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
	//std::cout << "Size 1: " << pointsInEachClass.size() << std::endl;
	for (int i = 0; i<pointsInEachClass.size(); i++)
	{
		std::vector<ProbabilityNeuron> tmp1;
		tmp1.clear();
		neurons.push_back(tmp1);
		//std::cout << "Size 2: " << pointsInEachClass[i].size() << std::endl;
		for (int j = 0; j<pointsInEachClass[i].size(); j++)
		{
			ProbabilityNeuron tmp2 = ProbabilityNeuron();
			tmp2.setNumberOfInputs(numberOfInputs);
			tmp2.setSigma(0.1);
			tmp2.setValues(pointsInEachClass[i][j]);
			neurons[i].push_back(tmp2);
			//std::cout << neurons[i][j].getNumberOfInputs() << std::endl;
		}
	}
}


PNN::~PNN()
{
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

void PNN::saveClasses(std::string fileName)
{
	std::ofstream weights;
	weights.open(fileName + ".csv");

	weights << pointsInEachClass.size() << '\n';
	for (int i = 0; i<pointsInEachClass.size(); i++)
	{
		weights << pointsInEachClass[i].size() << '\n';
		for (int j = 0; j<pointsInEachClass[i].size(); j++)
		{
			weights << neurons[i][j].getValues().size() << '\n';
			for (int k = 0; k < neurons[i][j].getValues().size(); k++)
			{
				weights << neurons[i][j].getValues()[k] << ",";
			}
			weights << '\n';
		}
	}

	weights.close();
}

void PNN::loadClasses(std::string fileName)
{
	std::ifstream weights(fileName + ".csv");
	if (!weights.is_open())
	{
		std::cout << "Error could not load PNN classes" << std::endl;
		return;
	}



	std::vector <std::vector<std::vector<double>>> pointsInEachClass;

	std::string value;
	int dim1, dim2, dim3;
	std::getline(weights, value, '\n');//2
	//std::cout << value << std::endl;
	dim1 = std::stoi(value);

	for (int i = 0; i < dim1; i++)
	{
		std::vector<std::vector<double>> cla;
		cla.clear();
		pointsInEachClass.push_back(cla);
		std::getline(weights, value, '\n');//3
		//std::cout << value << std::endl;
		dim2 = std::stoi(value);
		for (int j = 0; j < dim2; j++)
		{
			std::getline(weights, value, '\n');//2
			//std::cout << value << std::endl;
			dim3 = std::stoi(value);
			std::vector<double> values;
			values.clear();
			for (int k = 0; k < dim3; k++)
			{
				std::getline(weights, value, ',');
				//std::cout << value << std::endl;
				values.push_back(std::stod(value));
			}
			pointsInEachClass[i].push_back(values);
			std::getline(weights, value, '\n');
		}
	}
	weights.close();
	this->pointsInEachClass = pointsInEachClass;

	//constructor
	neurons.clear();
	for (int i = 0; i<pointsInEachClass.size(); i++)
	{
		std::vector<ProbabilityNeuron> tmp1;
		tmp1.clear();
		neurons.push_back(tmp1);
		//std::cout << "Size 2: " << pointsInEachClass[i].size() << std::endl;
		for (int j = 0; j<pointsInEachClass[i].size(); j++)
		{
			ProbabilityNeuron tmp2 = ProbabilityNeuron();
			tmp2.setNumberOfInputs(numberOfInputs);
			tmp2.setSigma(0.1);
			tmp2.setValues(pointsInEachClass[i][j]);
			neurons[i].push_back(tmp2);
			//std::cout << neurons[i][j].getNumberOfInputs() << std::endl;
		}
	}


}


#include "MLP.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
MLP::MLP()
{
}


MLP::MLP(int numberOfInputs, int numberOfOutputs, int numberOfHiddenLayers, std::vector<int> neuronsInEachLayers,std::string fileName)
{

	if (numberOfHiddenLayers != neuronsInEachLayers.size())
	{
		return;
	}
	this->fileName = fileName;
	this->numberOfInputs = numberOfInputs;
	this->numberOfOutputs = numberOfOutputs;
	this->numberOfHiddenLayers = numberOfHiddenLayers;
	this->neuronsInEachLayers = neuronsInEachLayers;
	//first hidden layer
	std::vector<Neuron> tmp;
	neurons.push_back(tmp);
	for (int j = 0; j < neuronsInEachLayers[0]; j++)
	{
		Neuron* a = new Neuron(numberOfInputs, 0.1);
		neurons[0].push_back(*a);
	}
	//Other hidden layers
	for (int i = 1; i < neuronsInEachLayers.size(); i++)
	{
		std::vector<Neuron> tmp;
		neurons.push_back(tmp);
		for (int j = 0; j < neuronsInEachLayers[i]; j++)
		{
			Neuron* a = new Neuron(neurons[i-1].size(), 0.1);
			neurons[i].push_back(*a);
		}
	}
	//Output layer
	std::vector<Neuron> tmp2;
	neurons.push_back(tmp2);
	for (int j = 0; j < numberOfOutputs; j++)
	{
		Neuron* a = new Neuron(neurons[neurons.size()-2].size(), 0.1);
		neurons[neurons.size() - 1].push_back(*a);
	}
}

MLP::~MLP()
{
}

std::vector<double> MLP::guess(std::vector<double> inputs)
{
	std::vector<double> neuronResults;
	std::vector<double> tmp;
	//First hidden layer
	//std::cout << "Layer 1" << std::endl;
	for (int j = 0; j < neurons[0].size(); j++)
	{
		neuronResults.push_back(neurons[0][j].guess(inputs));
		//std::cout << "Neuron " << j + 1 << " " << neurons[0][j].guess(inputs) << std::endl;
	}


	for (int i = 1; i < neurons.size(); i++)
	{
		//std::cout << "Layer " << i+1 << std::endl;
		for (int j = 0; j < neurons[i].size(); j++)
		{
			tmp.push_back(neurons[i][j].guess(neuronResults));
			//std::cout << "Neuron " << j + 1 << " " << neurons[i][j].guess(neuronResults) << std::endl;
		}
		neuronResults.clear();
		neuronResults = tmp;	//TODO Czy trace obiekt POSSIBLE ERROR
		tmp.clear();
	}
	return neuronResults;
}

int MLP::train(std::vector<double> inputs, std::vector<double> targets)
{
	if (numberOfOutputs != targets.size())
	{
		std::cout << "Error during training" << std::endl;
		return -1;
	}
	//Calculating error
	std::vector<double> result = this->guess(inputs);
	std::vector<double> errors;
	bool end = true;
	for (int i = 0; i < targets.size(); i++)
	{
		errors.push_back(targets[i]- result[i]);
		if (abs(errors[i]) > 0.0005)
		{
			end = false;
		}
	}
	//Print error
	//for (int i = 0; i < errors.size();i++)
	//{
	//	std::cout << errors[i] << std::endl;
	//}



	//Out if error acceptable
	if (end)
	{
		return 1;
	}

	//Setting errors of each neuron
	for (int j = 0; j < neurons[neurons.size()-1].size(); j++)
	{
		neurons[neurons.size() - 1][j].setError(errors[j]);
	}

	for (int i = neurons.size() - 2; i > -1; i--)
	{
		for (int j = 0; j < neurons[i].size(); j++)
		{
			for (int k = 0; k < neurons[i + 1].size(); k++)
			{
				neurons[i][j].setError(neurons[i][j].getError() + neurons[i + 1][k].getWeights()[j] * neurons[i + 1][k].getError());
			}
		}
	}

	//Weights modyfication

	std::vector<double> vectorInput;	//this layer results
	std::vector<double> tmp;			//pervious layer results

	double sum = 0;
	//First layer
	for (int j = 0; j < neurons[0].size(); j++)
	{
		sum = neurons[0][j].sum(inputs);
		std::vector<double> w = neurons[0][j].getWeights();
		for (int k = 0; k < neurons[0][j].getWeights().size(); k++)
		{
			w[k] += neurons[0][j].getLr() * neurons[0][j].getError() *  neurons[0][j].activationDerrivative(sum) * inputs[k];
		}
		neurons[0][j].setWeights(w);
		vectorInput.push_back(neurons[0][j].guess(inputs));
		//bias
		neurons[0][j].setValueToBiastWeight(neurons[0][j].getBiasWeight()+ neurons[0][j].getLr() * neurons[0][j].getError() *  neurons[0][j].activationDerrivative(sum));
	}



	for (int i = 1; i < neurons.size(); i++)
	{
		tmp = vectorInput;
		vectorInput.clear();
		for (int a = 0; a < neurons[i].size(); a++)
		{
			vectorInput.push_back(neurons[i][a].guess(tmp));
		}
		for (int j = 0; j < neurons[i].size(); j++)
		{
			sum = neurons[i][j].sum(tmp);
			std::vector<double> w = neurons[i][j].getWeights();
			for (int k = 0; k < neurons[i][j].getWeights().size(); k++)
			{
				w[k] += neurons[i][j].getLr() * neurons[i][j].getError() *  neurons[i][j].activationDerrivative(sum) * tmp[k];
				neurons[i][j].setWeights(w);
			}
			neurons[i][j].setValueToBiastWeight(neurons[i][j].getBiasWeight() + neurons[i][j].getLr() * neurons[i][j].getError() *  neurons[i][j].activationDerrivative(sum));
		}
	}

	//Zeroing errors
	for (int i = 0; i < neurons.size(); i++)
	{
		for (int j = 0; j < neurons[i].size(); j++)
		{
			neurons[i][j].setError(0);
		}
	}
}

void MLP::saveWeights()
{
	std::ofstream weights;
	weights.open(fileName+".csv");
	for (int i = 0; i < neurons.size(); i++)
	{
		for (int j = 0; j < neurons[i].size(); j++)
		{
			for (int k = 0; k < neurons[i][j].getWeights().size(); k++)
			{
				weights << neurons[i][j].getWeights()[k] << ",";
			}
			weights << neurons[i][j].getBiasWeight();
			weights << "\n";
		}
	}
	weights.close();
}

void MLP::loadWeights()
{
	std::ifstream weights(fileName + ".csv");
	if (!weights.is_open())
	{
		std::cout << "Error could not load weights" << std::endl;
		return;
	}
	int i = 0, j = 0, k = 0;
	std::vector<double> tmp;
	std::string value;
	std::string token;
	std::string splitter = ",";
	size_t pos = 0;
	double number;
	while (weights.good())
	{
		std::getline(weights, value,'\n');
		value = value + ',';
		//number = std::stod(value);
		while ((pos = value.find(splitter)) != std::string::npos) {
			token = value.substr(0, pos);
			//std::cout << token << std::endl;
			
			if (token != "")
			{
				number = std::stod(token);
				if (k < neurons[i][j].getWeights().size())
				{
					tmp.push_back(number);
					k++;
				}
				else if (k== neurons[i][j].getWeights().size())
				{
					k++;
					neurons[i][j].setValueToBiastWeight(number);
					neurons[i][j].setWeights(tmp);
					tmp.clear();
				}
				else
				{
					k = 0;
					tmp.push_back(number);
					k++;
					j++;
					if (j >= neurons[i].size())
					{
						i++;
						j = 0;
					}
				}
				
				//std::cout << number << std::endl;

			}
			
			value.erase(0, pos + splitter.length());
		}
		//std::cout << value << std::endl;
	}

	weights.close();
}

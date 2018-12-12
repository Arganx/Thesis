#pragma once
#include <vector> 
#include "Neuron.h"
class MLP
{
private:
	int numberOfInputs;
	int numberOfOutputs;
	int numberOfHiddenLayers;
	std::vector<int> neuronsInEachLayers;
	std::vector<std::vector<Neuron>> neurons;
	std::string fileName;
public:
	MLP(int numberOfInputs,int numberOfOutputs,int numberOfHiddenLayers,std::vector<int> neuronsInEachLayers,std::string fileName);
	MLP();
	~MLP();
	void setNumberOfInputs(int value) { numberOfInputs = value; };
	void setNumberOfOutputs(int value) { numberOfOutputs = value; };
	void setNeuronsInEachLayers(std::vector<std::vector<Neuron>> value) { neurons = value; };
	std::vector<double> guess(std::vector<double> inputs);
	int train(std::vector<double> inputs, std::vector<double> targets);//1-no more training, 0 - more training, -1 - error
	void saveWeights();
	void loadWeights();
};


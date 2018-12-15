#pragma once
#include "ProbabilityNeuron.h"
#include <vector> 
class PNN
{
private:
	int numberOfInputs;
	std::vector <std::vector<std::vector<double>>> pointsInEachClass;
	//double*** pointsInEachClass;// 1- numberOfClasses, 2-number of objects in each class, 3-objects
	//ProbabilityNeuron** neurons;
	std::vector<std::vector<ProbabilityNeuron>> neurons;
	int max(std::vector<double> input);

public:
	PNN(int numberOfInputs, std::vector <std::vector<std::vector<double>>> pointsInEachClass);
	~PNN();
	void SchowNeuronValues();
	int classify(std::vector<double> inputs);
	void saveClasses(std::string fileName);
	void loadClasses(std::string fileName);
	
};


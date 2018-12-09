#pragma once
#include <vector> 
class Neuron
{
private:
	int numberOfInputs;
	std::vector<double> weights;
	double biasWeight;
	
	double lr;
	double error;
public:
	Neuron();
	Neuron(int numberOfInputs,double lr);
	~Neuron();
	double activationFunction(double number);
	double activationDerrivative(double number);
	double sum(std::vector<double> inputs);
	double guess(std::vector<double> inputs);
	void train(std::vector<double> inputs, double result);
	
	void show();
	//Getters and setters
	double getLr() { return lr; };
	void setLr(double lr) { this->lr = lr; };
	void setNumberOfInputs(int number);
	void setBiasWeight();
	double getError() { return error; };
	void setError(double error) { this->error = error; };
	std::vector<double> getWeights() { return weights; };
	void setWeights(std::vector<double> weights);
};


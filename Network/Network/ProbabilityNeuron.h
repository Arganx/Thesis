#pragma once
#include <vector> 
class ProbabilityNeuron
{

private:
	int numberOfInputs;
	std::vector<double> values;
	double sigma;
public:
	ProbabilityNeuron(int numberOfInputs, std::vector<double> values, double sigma);
	ProbabilityNeuron();
	double calculateSimilarityRate(std::vector<double> input);
	~ProbabilityNeuron();
	void setSigma(double sigma) { this->sigma = sigma; };
	void setNumberOfInputs(int numberOfInputs) { this->numberOfInputs = numberOfInputs; };
	void setValues(std::vector<double> values) { this->values = values; };
	double getSigma() { return sigma; };
	int getNumberOfInputs() { return numberOfInputs; };
	std::vector<double> getValues() { return values; };

};


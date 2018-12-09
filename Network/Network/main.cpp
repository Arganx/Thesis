#include<iostream>
#include "Neuron.h"
#include <time.h> 
#include <stdlib.h> 
#include "PNN.h"
#include <array>
#include "Functions.h"
#include "MLP.h"
int main()
{
	srand((unsigned)time(NULL));
	//PNN
	/*
	std::vector <std::vector<std::vector<double>>> classes;

	std::vector<std::vector<double>> nobjects1;
	std::vector<double> obj1;
	obj1.push_back(1.0);
	obj1.push_back(3.0);

	std::vector<double> obj2;
	obj2.push_back(5.5);
	obj2.push_back(5.0);

	std::vector<double> obj3;
	obj3.push_back(3.0);
	obj3.push_back(3.2);

	nobjects1.push_back(obj1);
	nobjects1.push_back(obj2);
	nobjects1.push_back(obj3);

	std::vector<std::vector<double>> nobjects2;
	std::vector<double> obj4;
	obj4.push_back(50.0);
	obj4.push_back(46.0);

	std::vector<double> obj5;
	obj5.push_back(58.8);
	obj5.push_back(4.9);

	std::vector<double> obj6;
	obj6.push_back(45.7);
	obj6.push_back(70);

	nobjects2.push_back(obj4);
	nobjects2.push_back(obj5);
	nobjects2.push_back(obj6);

	classes.push_back(nobjects1);
	classes.push_back(nobjects2);
	Functions functions;
	functions.normalise(classes,150);
	

	PNN pnn = PNN(2, classes);
	pnn.SchowNeuronValues();
	std::vector<double> input;
	input.push_back(30.0/150.0);
	input.push_back(30.0/150.0);
	std::cout << pnn.classify(input) << std::endl;
	*/
	//MLP
	Neuron* neuron = new Neuron(2,0.1);
	std::vector<int> neuronsInEachLayer;
	neuronsInEachLayer.push_back(2);
	neuronsInEachLayer.push_back(3);
	MLP mlp = MLP(2,1,2, neuronsInEachLayer);
	std::vector<double> input;
	input.push_back(0.5);
	input.push_back(0.8);
	std::vector<double> target;
	target.push_back(0.2);
	//std::cout << mlp.guess(input)[0] << std::endl;
	double tmp = 0;
	while (tmp!=1)
	{
		tmp = mlp.train(input, target);
	}
	std::cout << mlp.guess(input)[0] << std::endl;
	system("pause");
}
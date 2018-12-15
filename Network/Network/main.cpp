#include<iostream>
#include "Neuron.h"
#include <time.h> 
#include <stdlib.h> 
#include "PNN.h"
#include <array>
#include "Functions.h"
#include "MLP.h"
#include "Item.h"
#include <fstream>
int main()
{
	srand((unsigned)time(NULL));
	//PNN
	
	std::vector <std::vector<std::vector<double>>> classes;

	//std::vector<std::vector<double>> nobjects1;
	//std::vector<double> obj1;
	//obj1.push_back(1.0);
	//obj1.push_back(3.0);

	//std::vector<double> obj2;
	//obj2.push_back(5.5);
	//obj2.push_back(5.0);

	//std::vector<double> obj3;
	//obj3.push_back(3.0);
	//obj3.push_back(3.2);

	//nobjects1.push_back(obj1);
	//nobjects1.push_back(obj2);
	//nobjects1.push_back(obj3);

	//std::vector<std::vector<double>> nobjects2;
	//std::vector<double> obj4;
	//obj4.push_back(50.0);
	//obj4.push_back(46.0);

	//std::vector<double> obj5;
	//obj5.push_back(58.8);
	//obj5.push_back(4.9);

	//std::vector<double> obj6;
	//obj6.push_back(45.7);
	//obj6.push_back(70);

	//nobjects2.push_back(obj4);
	//nobjects2.push_back(obj5);
	//nobjects2.push_back(obj6);

	//classes.push_back(nobjects1);
	//classes.push_back(nobjects2);
	//Functions functions;
	//functions.normalise(classes,150);
	

	PNN pnn = PNN(5, classes);
	//pnn.saveClasses("Values");
	//pnn.SchowNeuronValues();
	std::vector<double> input;
	/*input.push_back(30.0/150.0);
	input.push_back(30.0/150.0);*/
	input.push_back(6.0 );
	input.push_back(2.0 );
	input.push_back(6.0 );
	input.push_back(2.0 );
	input.push_back(6.0);

	pnn.loadClasses("pnnStrength");

	std::cout << pnn.classify(input) << std::endl;
	
	
	/*
	//MLP
	Neuron* neuron = new Neuron(2,0.1);
	std::vector<int> neuronsInEachLayer;
	neuronsInEachLayer.push_back(20);
	neuronsInEachLayer.push_back(10);
	MLP mlp = MLP(5,1,2, neuronsInEachLayer,"mlpWeights");
	//Tests
	
	//std::vector<double> input;
	//input.push_back(0.5);
	//input.push_back(0.8);
	//std::vector<double> target;
	//target.push_back(2.2);
	////std::cout << mlp.guess(input)[0] << std::endl;
	//double tmp = 0;
	//while (tmp!=1)
	//{
	//	tmp = mlp.train(input, target);
	//}
	//std::cout << mlp.guess(input)[0] << std::endl;
	


	Functions functions;
	std::vector<Item> inputs;
	//Insert input
	inputs.push_back(Item(5, 4, 0, 1, 1));
	inputs.push_back(Item(3, 3, 5, 3, 5));
	inputs.push_back(Item(2, 0, 3, 3, 1));
	inputs.push_back(Item(3, 0, 6, 3, 2));
	inputs.push_back(Item(4, 3, 1, 1, 2));
	inputs.push_back(Item(4, 0, 3, 1, 0));
	inputs.push_back(Item(6, 2, 5, 2, 6));
	inputs.push_back(Item(4, 0, 3, 2, 2));
	inputs.push_back(Item(4, 1, 0, 1, 2));
	inputs.push_back(Item(5, 0, 4, 0, 4));
	inputs.push_back(Item(4, 1, 1, 0, 1));
	inputs.push_back(Item(1, 3, 0, 2, 1));
	inputs.push_back(Item(1, 4, 6, 1, 1));
	inputs.push_back(Item(1, 5, 0, 2, 1));
	inputs.push_back(Item(1, 1, 2, 2, 1));
	inputs.push_back(Item(3, 0, 3, 3, 2));
	inputs.push_back(Item(4, 6, 5, 1, 3));
	inputs.push_back(Item(3, 4, 3, 3, 2));
	inputs.push_back(Item(2, 6, 3, 1, 3));
	inputs.push_back(Item(3, 2, 0, 1, 2));
	inputs.push_back(Item(2, 6, 0, 2, 2));
	inputs.push_back(Item(3, 4, 1, 0, 3));
	inputs.push_back(Item(2, 1, 0, 0, 4));
	inputs.push_back(Item(4, 3, 0, 0, 0));
	inputs.push_back(Item(2, 4, 0, 2, 5));
	inputs.push_back(Item(4, 6, 2, 2, 3));
	inputs.push_back(Item(4, 3, 2, 2, 3));
	inputs.push_back(Item(4, 4, 2, 2, 3));
	inputs.push_back(Item(4, 5, 2, 2, 3));
	inputs.push_back(Item(4, 1, 6, 2, 3));
	inputs.push_back(Item(4, 2, 2, 2, 3));
	inputs.push_back(Item(0, 6, 0, 0, 1));
	inputs.push_back(Item(0, 3, 0, 0, 1));
	inputs.push_back(Item(0, 4, 0, 0, 1));
	inputs.push_back(Item(0, 5, 0, 0, 1));
	inputs.push_back(Item(0, 1, 0, 0, 1));
	inputs.push_back(Item(0, 2, 0, 0, 1));
	int a;

	for (int i = 0; i < 100000; i++)
	{
		a = rand() % 37;
		mlp.train(inputs[a].getInput(), inputs[a].getResult());
	}

	//std::vector<double> testInputs;
	//testInputs.push_back(0.203);
	//testInputs.push_back(0.5);
	mlp.saveWeights();
	std::ofstream res;
	res.open("Results.csv");
	res << "Guess,Real\n";
	for (int i = 0; i < 37; i++)
	{
		
		res << 12.*mlp.guess(inputs[i].getInput())[0] << "," << inputs[i].getDexterity() << "\n";
		
	}
	res.close();
	//std::cout << mlp.guess(inputs[1].getInput())[0] << std::endl;
	*/
	system("pause");
}
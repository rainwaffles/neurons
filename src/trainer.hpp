#ifndef TRAINER_H__
#define TRAINER_H__

#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.hpp"
#include "geneticalgorithm.hpp"

class Trainer
{
public:
	Trainer();
	Trainer(FILE* conf);
	~Trainer();
	
	void train();
	
	void gentofile();
	
private:
	int nnums[4]; //num in, num out, num hidden, num per hidden layer
	int numex;
	std::vector<double> trainin, trainout;
	NeuralNet *brain; GenAlg *pool;
	int getfit(Genome &gen);

};

#endif

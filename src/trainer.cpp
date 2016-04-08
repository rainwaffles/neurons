#include "trainer.hpp"

Trainer::Trainer()
{
	Trainer(stdin);
}

Trainer::Trainer(FILE* conf)
{
	for(int i = 0; i < 4; i++)
	{
		fscanf(conf, "%i ", &nnums[i]);
	}
	int popsize;
	double mutationrate, crossrate;
	fscanf(conf, "%i ", &popsize);
	fscanf(conf, "%lf ", &mutationrate);
	fscanf(conf, "%lf ", &crossrate);
	fscanf(conf, "%i ", &numex);
	for(int i = 0; i < numex; i++)
	{
		for(int j = 0; j < nnums[0]; j++)
		{
			double input;
			fscanf(conf, "%lf ", &input);
			trainin.push_back(input);
		}
		for(int j = 0; j < nnums[1]; j++)
		{
			double input;
			fscanf(conf, "%lf ", &input);
			trainout.push_back(input);
		}
	}
	brain = new NeuralNet(nnums[0], nnums[1], nnums[2], nnums[3]);
	int weights = brain->getnumweights();
	pool = new GenAlg(popsize, mutationrate, crossrate, weights);
}

Trainer::~Trainer()
{
	delete brain; delete pool;
}

void Trainer::train()
{
	std::vector<Genome> chroms = pool->getchromos();
	for(int i = 0; i < chroms.size(); i++)
	{
		chroms[i].fitness = numex*nnums[1]*100 - getfit(chroms[i]);
	}
	pool->epoch(chroms);
}

int Trainer::getfit(Genome &gen)
{
	brain->setweights(gen.weights);
	double dev = 0;
	for(int i = 0; i < numex; i++)
	{
		std::vector<double> subin;
		std::vector<double> subout;
		for(int j = 0; j < nnums[0]; j++)
		{
			subin.push_back(trainin[i*nnums[0]+j]);
		}
		for(int j = 0; j < nnums[1]; j++)
		{
			subout.push_back(trainout[i*nnums[1]+j]);
		}
		std::vector<double> out = brain->update(subin);
		for(int j = 0; j < nnums[1]; j++)
		{
			dev += (out[j] - subout[j] < 0)? -(out[j] - subout[j]) : (out[j] - subout[j]);
		}
	}
	return 100*dev;
}

void Trainer::gentofile()
{
	std::vector<Genome> chroms = pool->getchromos();
	int big = -999999;
	for(int i = 0; i < chroms.size(); i++)
	{
		chroms[i].fitness = getfit(chroms[i]);
		if(chroms[i].fitness < big){big = chroms[i].fitness;}
	}
	for(int i = 0; i < chroms.size(); i++)
	{
		chroms[i].fitness -= big;
	}
	pool->calcstats();
	Genome b = chroms[pool->getfittest()];
	FILE* out = fopen("best.gene", "w");
	fprintf(out, "%i %i %i %i\n", nnums[0], nnums[1], nnums[2], nnums[3]);
	for(int i = 0; i < b.weights.size(); i++)
	{
		fprintf(out, "%lf\n", b.weights[i]);
	}
}

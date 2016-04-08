#ifndef GENETICALGORITHM_H__
#define GENETICALGORITHM_H__

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

struct Genome
{
	std::vector<double> weights;
	double fitness;
	
	Genome():fitness(0){}
	Genome(std::vector<double> weights_, double fitness_):weights(weights_), fitness(fitness_){}
	
	void fillrand(int numweights);
	
	friend bool operator<(const Genome& l, const Genome& r)
	{
		return(l.fitness < r.fitness);
	}
	friend bool operator>(const Genome& l, const Genome& r)
	{
		return(l.fitness > r.fitness);
	}
};

class GenAlg
{
public:
	GenAlg(int popsize_, double mutationrate_, double crossrate_, int chromolen_);

	std::vector<Genome> epoch(std::vector<Genome> &pop_);

	void calcstats();
	
	std::vector<Genome> getchromos()const{return pop;}
	double getaveragefit()const{return averagefit;}
	double getbestfit()const{return highestfit;}

	double getfittest()const{return fittest;}

private:
	int chromolen;
	int popsize;
	std::vector<Genome> pop;
	
	double totalfit;
	double highestfit;
	double averagefit;
	double lowestfit;
	
	int fittest;
	
	double mutationrate;
	double crossrate;
	
	int generation;
	
	void mutate(std::vector<double> chromo);
	void crossover(const std::vector<double> &p1, const std::vector<double> &p2,
				std::vector<double> &b1, std::vector<double> &b2);
	Genome getchromo();
	void best(int n, const int copies, std::vector<Genome> &pop_);
	void reset();
};

#endif

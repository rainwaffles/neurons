#include "geneticalgorithm.hpp"

void Genome::fillrand(int numweights)
{
	for(int i = 0; i < numweights; i++)
	{
		weights.push_back((rand()/(RAND_MAX + 1.0))*2 - 1);
	}
}

GenAlg::GenAlg(int popsize_, double mutationrate_, double crossrate_, int chromolen_)
	: popsize(popsize_), mutationrate(mutationrate_), crossrate(crossrate_), chromolen(chromolen_),
		totalfit(0), highestfit(0), averagefit(0), lowestfit(999999), fittest(0), generation(0)
{
	srand(time(NULL));
	for(int i = 0; i < popsize; i++)
	{
		pop.push_back(Genome());
		pop[i].fillrand(chromolen);
	}
}

std::vector<Genome> GenAlg::epoch(std::vector<Genome> &pop_)
{
	pop = pop_;
	reset();
	std::sort(pop.begin(), pop.end());
	calcstats();
	
	std::vector<Genome> newpop;
	best(4, 1, newpop);
	
	while(newpop.size() < popsize)
	{
		Genome p1 = getchromo();
		Genome p2 = getchromo();
		std::vector<double> b1, b2;
		crossover(p1.weights, p2.weights, b1, b2);
		mutate(b1); mutate(b2);
		newpop.push_back(Genome(b1, 0));
		newpop.push_back(Genome(b2, 0));
	}
	pop = newpop;
	return pop;
}

void GenAlg::mutate(std::vector<double> chromo)
{
	for(int i = 0; i < chromo.size(); i++)
	{
		if(rand()/(RAND_MAX + 1.0) < mutationrate)
		{
			chromo[i] += rand()/(RAND_MAX + 1.0)*0.3;
		}
	}
}

void GenAlg::crossover(const std::vector<double> &p1, const std::vector<double> &p2,
			std::vector<double> &b1, std::vector<double> &b2)
{
	if(rand()/(RAND_MAX + 1.0) > crossrate || p1 == p2)
	{
		b1 = p1; b2 = p2;
		return;
	}
	int cp = rand()%chromolen;
	for(int i = 0; i < chromolen; i++)
	{
		b1.push_back((i < cp)? p1[i] : p2[i]);
		b2.push_back((i < cp)? p2[i] : p1[i]);
	}
	return;
}

Genome GenAlg::getchromo()
{
	double fitn = rand()/(RAND_MAX + 1.0)*totalfit;
	double cumfit = 0;
	
	for(int i = 0; i < popsize; i++)
	{
		cumfit += pop[i].fitness;
		if(cumfit >= fitn){return pop[i];}
	}
	return pop[popsize-1];
}

void GenAlg::best(int n, const int copies, std::vector<Genome> &pop_)
{
	while(n--)
	{
		for(int i = 0; i < copies; i++)
		{
			pop_.push_back(pop[popsize - 1 - n]);
		}
	}
}

void GenAlg::calcstats()
{
	totalfit = 0;
	double curhigh = 0, curlow = 999999;
	
	for(int i = 0; i < popsize; i++)
	{
		if(pop[i].fitness > curhigh)
		{
			curhigh = pop[i].fitness;
			fittest = i; highestfit = curhigh;
		}
		if(pop[i].fitness < curlow)
		{
			curlow = pop[i].fitness;
			lowestfit = curlow;
		}
		totalfit += pop[i].fitness;
	}
	averagefit = totalfit / popsize;
}

void GenAlg::reset()
{
	totalfit = highestfit = averagefit = 0;
	lowestfit = 999999;
}

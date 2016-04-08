#include <stdio.h>
#include <vector>

#include "neuralnetwork.hpp"

int main(int argc, char* argv[])
{
	FILE* gene;
	if(argc < 2){gene = fopen("./best.gene", "r");}
	else{gene = fopen(argv[1], "r");}
	int nnums[4];	
	for(int i = 0; i < 4; i++)
	{
		fscanf(gene, "%i ", &nnums[i]);
	}
	NeuralNet brain(nnums[0], nnums[1], nnums[2], nnums[3]);
	std::vector<double> w;
	for(int i = 0; i < brain.getnumweights(); i++)
	{
		double get;
		fscanf(gene, "%lf ", &get);
		w.push_back(get);
	}
	brain.setweights(w);
	std::vector<double> in, out;
	while(true)
	{
		in.clear(); out.clear();
		for(int i = 0; i < nnums[0]; i++)
		{
			double input;
			fscanf(stdin, "%lf ", &input);
			in.push_back(input);
		}
		out = brain.update(in);
		for(int i = 0; i < nnums[1]; i++)
		{
			fprintf(stdout, "%lf ", out[i]);
		}
		fprintf(stdout, "\n");
	}
	return 0;
}

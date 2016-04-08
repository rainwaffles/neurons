#include <stdio.h>

#include "neuralnetwork.hpp"
#include "geneticalgorithm.hpp"
#include "trainer.hpp"

int main(int argc, char* argv[])
{
	FILE* conf = fopen("./default.conf", "r"); 
	Trainer test(conf);
	int runtime; fscanf(conf, "%i ", &runtime);
	for(int i = 0; i < runtime; i++)
	{
		test.train();
	}
	test.gentofile();
	return 0;
}

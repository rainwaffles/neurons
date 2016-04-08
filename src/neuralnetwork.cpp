#include "neuralnetwork.hpp"

Neuron::Neuron(int in_): in(in_)
{
	//in is in_ + 1 because of bias
	for(int i = 0; i < in; i++)
	{
		//set each weight with a rand number -1 - 1
		weights.push_back((rand()/(RAND_MAX + 1.0))*2 - 1);
	}
}

double Neuron::update(std::vector<double> &inputs)
{
	double sum = 0;
	for(int i = 0; i < in; i++)
	{
		sum += weights[i]*inputs[i];
	}
	//sum += weights[in-1]*BIAS;
	return sum;
}

NeuronLayer::NeuronLayer(int num_, int in_): num(num_)
{
	for(int i = 0; i < num; i++)
	{
		neurons.push_back(Neuron(num_));
	}
}

NeuralNet::NeuralNet(int in_, int out_, int numhidden_, int nperlayer_):
	in(in_), out(out_), numhidden(numhidden_), nperlayer(nperlayer_)
{
	srand(time(NULL));
	createnet();
	updatenumweights();
}

void NeuralNet::createnet()
{
	if(numhidden > 0)
	{
		layers.push_back(NeuronLayer(nperlayer, in));
		for(int i = 0; i < numhidden-1; i++)
		{
			layers.push_back(NeuronLayer(nperlayer, nperlayer));
		}
		layers.push_back(NeuronLayer(out, nperlayer));
	}
	else {layers.push_back(NeuronLayer(out, in));}
}

void NeuralNet::updatenumweights()
{
	numweights = 0;
	for(int i = 0; i < numhidden+1; i++)
	{
		for(int j = 0; j < layers[i].num; j++)
		{
			for(int k = 0; k < layers[i].neurons[j].in; k++)
			{
				numweights++;
			}
		}
	}
}

std::vector<double> NeuralNet::getweights()const
{
	std::vector<double> weights;
	for(int i = 0; i < numhidden+1; i++)
	{
		for(int j = 0; j < layers[i].num; j++)
		{
			for(int k = 0; k < layers[i].neurons[j].in; k++)
			{
				weights.push_back(layers[i].neurons[j].weights[k]);
			}
		}
	}
	return weights;
}

int NeuralNet::getnumweights()const
{
	return numweights;
}

void NeuralNet::setweights(std::vector<double> &weights)
{
	int n = 0;
	for(int i = 0; i < numhidden+1; i++)
	{
		for(int j = 0; j < layers[i].num; j++)
		{
			for(int k = 0; k < layers[i].neurons[j].in; k++)
			{
				layers[i].neurons[j].weights[k] = weights[n++];
			}
		}
	}
}

std::vector<double> NeuralNet::update(std::vector<double> &inputs)
{
	std::vector<double> outputs;
	
	if(inputs.size() != in) {return outputs;}
	
	for(int i = 0; i < numhidden+1; i++)
	{
		if(i > 0) {inputs = outputs;}
		outputs.clear();
		
		for(int j = 0; j < layers[i].num; j++)
		{
			outputs.push_back(sigmoid(layers[i].neurons[j].update(inputs),ACTIVATION));
		}
	}
	return outputs;
}

inline double NeuralNet::sigmoid(double act, double resp)
{
	return (1/(1 + exp(-act/resp)));
}

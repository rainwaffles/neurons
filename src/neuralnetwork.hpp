#ifndef NEURALNETWORK_H__
#define NEURALNETWORK_H__

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//#define BIAS -1
#define ACTIVATION 1

struct Neuron
{
	//constructor
        Neuron(int in_);
	
	//number of inputs the neuron takes
        int in; 
    
        //weights of each input
        std::vector<double> weights;
	
	//returns sum of inputs*weights
	double update(std::vector<double> &inputs);
};

struct NeuronLayer
{
	//constructor
	NeuronLayer(int num_, int in_);
	
	//number of neurons in this layer
	int num;
	
	//layer of neurons
	std::vector<Neuron> neurons;
};

class NeuralNet
{
public:
	//constructor
	NeuralNet(int in_, int out_, int numhidden_, int nperlayer_);
	
	//init net
	void createnet();
	
	//gets weights
	std::vector<double> getweights()const;
	
	//returns number of weights
	int getnumweights()const;
	
	//replaces weights with new weights
	void setweights(std::vector<double> &weights);
	
	//calculate the output
	std::vector<double> update(std::vector<double> &inputs);
	
	//sigmoid response curve
	inline double sigmoid(double act /*activation*/, double resp /*response*/);

private:
	//number of inputs, for first layer
	int in;
	
	//number of outputs, for last layer
	int out;
	
	//hidden = layers that are not input/output
	int numhidden;
	
	//neurons per layer, layers have same number atm
	int nperlayer;
	
	//number of weights, updated if NN changes
	int numweights;
	void updatenumweights();
	
	//storing each layer
	std::vector<NeuronLayer> layers;

};

#endif

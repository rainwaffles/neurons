#Version 2016.2.14

all: test run

clean:
	rm -f ./test ./run ./best.gene

run: 
	g++ -std=c++11 -ggdb ./src/neuralnetwork.cpp ./src/run.cpp -o run

test:
	g++ -std=c++11 -ggdb ./src/trainer.cpp ./src/geneticalgorithm.cpp ./src/neuralnetwork.cpp ./src/test.cpp -o test

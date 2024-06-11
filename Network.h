#pragma once
#include "Node.h"
#include <vector>
#include <iostream>

// TODO consider making the layeIntializers take a function variable so its more universal 

class Network
{
public:

	enum GradientDescentType {
		Stochastic,
		MiniBatch,
		FullBatch
	};

	enum ActivationFunctionType {
		Sigmoid,
		ReLU,
		LeakyReLU,
		Tanh,
		Xcube,
		AbsoluteValue,
	};

	Network();

	bool displayOutput = false;

	void runNetworkWithTrainingData(bool displayOutput);

	void runNetworkWithTrainingData(bool displayOutput, std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData);
	
	void passTrainingData(std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData);

	void runNetworkTraining(GradientDescentType, ActivationFunctionType);

	ActivationFunctionType currentActivationFunction = Sigmoid; // defualt is sigmoid but can be changed

	GradientDescentType currentGradientDescentType = Stochastic; // defualt is stochastic but can be changed


private:

	// maybe figure out a better way to do this or check that Netowrk size and the array match
	static const int NETWORK_SIZE = 3;
	int networkLayers[NETWORK_SIZE] = {784, 100, 10};

	std::vector<std::vector<Node>> nodeContainer;

	std::vector<std::pair<std::vector<double>, std::vector<double>>> networkTrainingData;

	//---------------------Vars------------------------------------------------
	
	static const float LEARNING_RATE;

	//-----------------------Initialization--------------------------------------------

	void establishNodes(); // dormant function for now

	void inputLayerIntialize();

	void outputLayerInitialize();

	void hiddenLayersIntialize();

	//---------------------Connections------------------------------------------------

	void initializeAllNodeConnections();

	void connectInputLayer();

	void connectHiddenLayers();

	//---------------------Network Value Calculations------------------------------------------------

	bool calculateNetworkOutput(std::pair<std::vector<double>, std::vector<double>> trainingDataPair);

	double networkActivationFunction(double value);

	//---------------------Training Data--------------------------------------------

	void verifyTrainingData();

	bool compareFirstLayerToTrainingData();

	//---------------------Gradient Descent------------------------------------------------


	void outputLayerGradientDescentStoch(std::vector<double>);

	void hiddenLayerGradientDescentStoch();

	void outputLayerGradientDescentBatch(std::vector<double>);

	void hiddenLayerGradientDescentStochBatch();

	void loopAllLayers(std::vector<double>);

	void stochasticGradientDescent();

	void miniBatchGradientDescent();

	void fullBatchGradientDescent();

	double networkActivationFunctionDerivative(Node);

	//---------------------Activation Functions------------------------------------------------

	double sigmoidActivation(double);

	double sigmoidActivationDerivative(Node);

	double ReLUActivation(double);

	double ReLUActivationDerivative(double);

	double LeakyReLUActivation(double);

	double LeakyReLUActivationDerivative(double);

	double TanhActivation(double);

	double TanhActivationDerivative(double);

	double XcubeActivation(double);

	double XcubeActivationDerivative(double);

	double AbsoluteValueActivation(double);

	double AbsoluteValueActivationDerivative(double);
};
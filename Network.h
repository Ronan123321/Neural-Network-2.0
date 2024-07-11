#pragma once
#include "Node.h"
#include <vector>
#include <iostream>

//TODO : Add an option for different cost functions

class Network
{
public:

	enum ActivationFunctionType {
		Sigmoid, 
		ReLU,	
		LeakyReLU,
		Tanh,
		AbsoluteValue,
		SeLu
	};

	enum CostFunctionType {
		DifferenceSquared,
		MeanSquaredError,
		CrossEntropy
	};

	Network();

	int batchSize = 1; // this makes default stochastic

	int totalEpoch = 1;

	bool displayOutput = false;

	void runNetworkWithTrainingData(bool displayOutput);

	void runNetworkWithTrainingData(bool displayOutput, std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData);
	
	void passTrainingData(std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData);

	void passTestingData(std::vector<std::pair<std::vector<double>, std::vector<double>>> testingData);

	void runStochDescent(ActivationFunctionType); // run stochastic descent

	void runMiniBatchDescent(ActivationFunctionType, int batchSize); // run mini batch with a specific batch size

	void runFullBatchDescent(ActivationFunctionType, int epochTotal); // run full batch descent

	ActivationFunctionType currentActivationFunction = Sigmoid; // defualt is sigmoid but can be changed

	CostFunctionType currentCostFunction = DifferenceSquared; // default is difference squared but can be changed


private:

	// maybe figure out a better way to do this or check that Netowrk size and the array match
	static const int NETWORK_SIZE = 3;
	int networkLayers[NETWORK_SIZE] = {784, 300, 10};

	std::vector<std::vector<Node>> nodeContainer;

	std::vector<std::pair<std::vector<double>, std::vector<double>>> networkTrainingData;

	std::vector<std::pair<std::vector<double>, std::vector<double>>> networkTestingData;

	//---------------------Vars------------------------------------------------
	
	static const double LEARNING_RATE;

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

	double networkCostFunction(double output, double expectedOutput);

	//---------------------Training Data--------------------------------------------

	void verifyTrainingData();

	bool compareFirstLayerToTrainingData();

	//---------------------Gradient Descent------------------------------------------------


	void outputLayerGradientDescentStoch(std::vector<double>);

	void hiddenLayerGradientDescentStoch();

	void outputLayerGradientDescentBatch(std::vector<double>);

	void hiddenLayerGradientDescentBatch();

	void batchCalcGradients(std::vector<double>);

	void batchApplyGradients();
	
	void stochApplyGradients(std::vector<double>);

	void stochasticGradientDescent();

	void miniBatchGradientDescent();

	void fullBatchGradientDescent();

	double networkActivationFunctionDerivative(Node);

	double networkCostFunctionDerivative(Node, double);

	//---------------------Activation Functions------------------------------------------------

	double sigmoidActivation(double);

	double sigmoidActivationDerivative(Node);

	double ReLUActivation(double);

	double ReLUActivationDerivative(Node);

	double LeakyReLUActivation(double);

	double LeakyReLUActivationDerivative(Node);

	double TanhActivation(double);

	double TanhActivationDerivative(Node);

	double AbsoluteValueActivation(double);

	double AbsoluteValueActivationDerivative(Node);

	double SeLuActivation(double);

	double SeLuActivationDerivative(Node);

	// ---------------------Cost Functions------------------------------------------------

	double difSqrd(double, double);

	double difSqrdDerivative(Node, double);

	double meanSqrdError(double, double);

	double meanSqrdErrorDerivative(Node, double);

	double crossEntropy(double, double);

	double crossEntropyDerivative(Node, double);
};
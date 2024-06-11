#include "Network.h"
#include <cmath>
#include <tgmath.h>

const float Network::LEARNING_RATE = 0.1f;

//---------------------Constructors------------------------------------------------

Network::Network() {
	if (NETWORK_SIZE < 2) {
		std::cout << "Error: Netowrk must be at least 2 layers large.\n";
	}
	else {

		inputLayerIntialize();

		if (NETWORK_SIZE > 2) {
			hiddenLayersIntialize();
		}

		outputLayerInitialize();

		initializeAllNodeConnections();
	}
}

//---------------------Public------------------------------------------------

void Network::establishNodes() {
	if (NETWORK_SIZE < 2) {
		std::cout << "Error: Netowrk must be at least 2 layers large.\n";
	}
	else {

		inputLayerIntialize();

		if (NETWORK_SIZE > 2) {
			hiddenLayersIntialize();
		}

		outputLayerInitialize();

		initializeAllNodeConnections();
	}
}

void Network::passTrainingData(std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData) {
	networkTrainingData = trainingData;
}

void Network::runNetworkWithTrainingData(bool displayOutput) {
	this->displayOutput = displayOutput;
	verifyTrainingData();

	// maybe make it so use can specify what % of the training data to use

	// iterate through the training data
	for (int trainingDataIt = 0; trainingDataIt < networkTrainingData.size(); trainingDataIt++) {
		this->calculateNetworkOutput(networkTrainingData.at(trainingDataIt));
	}

}

void Network::runNetworkWithTrainingData(bool displayOutput, std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData) {
	this->displayOutput = displayOutput;
	passTrainingData(trainingData);
	runNetworkWithTrainingData(displayOutput);
}

//-----------------------Initialization--------------------------------------------

void Network::inputLayerIntialize() {
	std::vector<Node> pushBackNodeContainer;

	for (int inputLayerIt = 0; inputLayerIt < networkLayers[0]; inputLayerIt++) {
		Node pushBackNode(false);
		pushBackNodeContainer.push_back(pushBackNode);
	}
	nodeContainer.push_back(pushBackNodeContainer);
}

void Network::outputLayerInitialize() {
	int networkLastLayer = (NETWORK_SIZE - 1);
	std::vector<Node> pushBackNodeContainer;

	for (int outputLayerIt = 0; outputLayerIt < networkLayers[networkLastLayer]; outputLayerIt++) {
		Node pushBackNode;
		pushBackNodeContainer.push_back(pushBackNode);
	}
	nodeContainer.push_back(pushBackNodeContainer);
}

void Network::hiddenLayersIntialize() {
	int amountHiddenLayers = NETWORK_SIZE - 2;
	std::vector<Node> pushBackNodeContainer;

	for (int networkHiddenLayerIt = 0; networkHiddenLayerIt < amountHiddenLayers; networkHiddenLayerIt++) {

		for (int hiddenLayerIt = 0; hiddenLayerIt < networkLayers[networkHiddenLayerIt + 1]; hiddenLayerIt++) { // skips intial layer 
			Node pushBackNode;
			pushBackNodeContainer.push_back(pushBackNode);
		}

		nodeContainer.push_back(pushBackNodeContainer);
		pushBackNodeContainer.clear();
	}
}

//---------------------Connections------------------------------------------------

void Network::initializeAllNodeConnections() {
	
	this->connectInputLayer();

	this->connectHiddenLayers();

	// Not needed because 
	//this->connectOutputLayer();

}

void Network::connectInputLayer() {
	const int previousLayer = NULL;
	const int currentLayer = 0;
	const int nextLayer = 1;
	//iterate through the first layer connecting to the next layer using the front and back connections of node

	for (int inputLayerIt = 0; inputLayerIt < networkLayers[currentLayer]; inputLayerIt++) {
		for (int nextLayerIt = 0; nextLayerIt < networkLayers[nextLayer]; nextLayerIt++) {
			// create a connection between the current layer and the next layer

			std::shared_ptr<Node> frontNode(&nodeContainer[nextLayer][nextLayerIt]);
			std::shared_ptr<Node> backNode(&nodeContainer[currentLayer][inputLayerIt]);

			Connection* temporaryConnection = new Connection(frontNode, backNode);

			nodeContainer[currentLayer][inputLayerIt].frontConnection.push_back(temporaryConnection);

			//std::swap(frontNode, backNode); they dont need to be swapped because the connection is bidirectional
			std::shared_ptr<double> weight = temporaryConnection->weight;
			std::shared_ptr<double> averageWeightGradient = temporaryConnection->averageWeightGradient;

			temporaryConnection = new Connection(frontNode, backNode, weight, averageWeightGradient);

	        nodeContainer[nextLayer][nextLayerIt].backConnection.push_back(temporaryConnection);
		}
	}

}

/*
void Network::connectOutputLayer() {
	const int previousLayer = NETWORK_SIZE - 2;
	const int currentLayer = NETWORK_SIZE - 1;
	const int nextLayer = NULL;

	for (int inputLayerIt = 0; inputLayerIt < networkLayers[currentLayer]; inputLayerIt++) {
		for (int previousLayerIt = 0; previousLayerIt < networkLayers[previousLayer]; previousLayerIt++) {
			// create a connection between the current layer and the previous layer

			std::shared_ptr<Node> frontNode(&nodeContainer[currentLayer][inputLayerIt]);
			std::shared_ptr<Node> backNode(&nodeContainer[previousLayer][previousLayerIt]);

			Connection* temporaryConnection = new Connection(frontNode, backNode);

			nodeContainer[currentLayer][inputLayerIt].backConnection.push_back(temporaryConnection);
		}
	}

}
*/

void Network::connectHiddenLayers() {
	for (int hiddenLayerIt = 1; hiddenLayerIt < NETWORK_SIZE - 1; hiddenLayerIt++) {
		const int currentLayer = hiddenLayerIt;
		const int nextLayer = hiddenLayerIt + 1;
		const int previousLayer = hiddenLayerIt - 1;

		for (int currentLayerIt = 0; currentLayerIt < networkLayers[currentLayer]; currentLayerIt++) {
			for (int nextLayerIt = 0; nextLayerIt < networkLayers[nextLayer]; nextLayerIt++) {
				// create a connection between the current layer and the next layer

				std::shared_ptr<Node> frontNode(&nodeContainer[nextLayer][nextLayerIt]);
				std::shared_ptr<Node> backNode(&nodeContainer[currentLayer][currentLayerIt]);

				Connection* temporaryConnection = new Connection(frontNode, backNode); 

				nodeContainer[currentLayer][currentLayerIt].frontConnection.push_back(temporaryConnection);

				std::shared_ptr<double> weight = temporaryConnection->weight;
				std::shared_ptr<double> averageWeightGradient = temporaryConnection->averageWeightGradient;

				temporaryConnection = new Connection(frontNode, backNode, weight, averageWeightGradient);

				nodeContainer[nextLayer][nextLayerIt].backConnection.push_back(temporaryConnection);
			}

			/*
			for (int previousLayerIt = 0; previousLayerIt < networkLayers[previousLayer]; previousLayerIt++) {
				// create a connection between the current layer and the previous layer

				std::shared_ptr<Node> frontNode(&nodeContainer[currentLayer][currentLayerIt]);
				std::shared_ptr<Node> backNode(&nodeContainer[previousLayer][previousLayerIt]);
				nodeContainer[previousLayer][previousLayerIt]

				Connection* temporaryConnection = new Connection(frontNode, backNode, );

				nodeContainer[currentLayer][currentLayerIt].backConnection.push_back(temporaryConnection);
			}
			*/
		}
	}

}

//---------------------Calculations------------------------------------------------

bool Network::calculateNetworkOutput(std::pair<std::vector<double>, std::vector<double>> trainingDataPair) {
	//Each node uses its own bias to calcualte its OWN value

	// Set the input layer values from the trainng data
	for (int inputLayerIt = 0; inputLayerIt < networkLayers[0]; inputLayerIt++) {
		nodeContainer[0][inputLayerIt].value = trainingDataPair.first.at(inputLayerIt);
	}

	// Iterates throught the network calculating output of each node
	for (int networkLayerIt = 1; networkLayerIt < NETWORK_SIZE; networkLayerIt++) {


		for (int nodeIt = 0; nodeIt < networkLayers[networkLayerIt]; nodeIt++) {
			// calculate the output of the node
			double sum = 0;
			for (int connectionIt = 0; connectionIt < nodeContainer[networkLayerIt][nodeIt].backConnection.size(); connectionIt++) {
				sum += *nodeContainer[networkLayerIt][nodeIt].backConnection[connectionIt]->weight * nodeContainer[networkLayerIt][nodeIt].backConnection[connectionIt]->backNode->value; // weight is being dereferenced
			}
			nodeContainer[networkLayerIt][nodeIt].value = this->networkActivationFunction(sum + nodeContainer[networkLayerIt][nodeIt].bias);
		}


	}


	double highestValueCount = 0;
	double highestValue = 0;
	if (this->displayOutput) {
		for (int outputLayerIt = 0; outputLayerIt < networkLayers[NETWORK_SIZE - 1]; outputLayerIt++) {
			if (nodeContainer[NETWORK_SIZE - 1][outputLayerIt].value > highestValue) {
				highestValue = nodeContainer[NETWORK_SIZE - 1][outputLayerIt].value;
				highestValueCount = outputLayerIt;
			}
			std::cout << outputLayerIt << ": " << nodeContainer[NETWORK_SIZE - 1][outputLayerIt].value << std::endl;
		}
	}

	for (int trainingDataLabelIt = 0; trainingDataLabelIt < trainingDataPair.second.size(); trainingDataLabelIt++) {
		if (trainingDataPair.second.at(trainingDataLabelIt) == 1) {
			if (highestValueCount == trainingDataLabelIt) {
				std::cout << "Correct\n";
				return true;
			}
		}
	
	}

	return false;
}

double Network::networkActivationFunction(double value) {

	switch (currentActivationFunction) {

		case Sigmoid:
		return sigmoidActivation(value);
		break;
		case ReLU:
			return this->ReLUActivation(value);
			break;
		case LeakyReLU:
			return this->LeakyReLUActivation(value);
			break;
		case Tanh:
			return this->TanhActivation(value);
			break;
		case Xcube:
			return this->XcubeActivation(value);
			break;
		case AbsoluteValue:
			return this->AbsoluteValueActivation(value);
			break;
	}
}


//---------------------Training Data--------------------------------------------

void Network::verifyTrainingData() {
	if (networkTrainingData.empty()) {
		std::cout << "Error: Training data is empty.\n";
	}
	if (!compareFirstLayerToTrainingData()) {
		std::cout << "Error: Training data does not match the input layer size.\n";
	}
}

bool Network::compareFirstLayerToTrainingData() {
	if (networkTrainingData.at(0).first.size() != networkLayers[0] || networkTrainingData.at(0).second.size() != networkLayers[NETWORK_SIZE - 1]) {
		return false;
	}
	else {
		return true;
	}
}


//---------------------Gradient Descent------------------------------------------------

void Network::runNetworkTraining(GradientDescentType givenDescentMethod, ActivationFunctionType givenActivation) {
	currentActivationFunction = givenActivation;
	currentGradientDescentType = givenDescentMethod;

	switch (currentGradientDescentType) {
		case Stochastic:
			stochasticGradientDescent();
			break;
		case MiniBatch:
			miniBatchGradientDescent();
			break;
		case FullBatch:
			fullBatchGradientDescent();
			break;
	}
}

void Network::outputLayerGradientDescentStoch(std::vector<double> expectedOutput) {
	// calculate the output layer node values

	for (int nodeIt = 0; nodeIt < networkLayers[NETWORK_SIZE - 1]; nodeIt++) {

		// calculate the new node values
		nodeContainer[NETWORK_SIZE - 1][nodeIt].nodeValue = networkActivationFunctionDerivative(nodeContainer[NETWORK_SIZE - 1][nodeIt]) * 2 * (nodeContainer[NETWORK_SIZE - 1][nodeIt].value - expectedOutput[nodeIt]);
		
		for (int connectionIt = 0; connectionIt < nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection.size(); connectionIt++) {
			
			//update the weight
			*(nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection[connectionIt]->weight) = *(nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection[connectionIt]->weight) - Network::LEARNING_RATE *nodeContainer[NETWORK_SIZE - 1][nodeIt].nodeValue* nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection[connectionIt]->backNode->value;
		}

		// Uses the node value from the previous loops and uses it to update the bias
		nodeContainer[NETWORK_SIZE-1][nodeIt].bias = nodeContainer[NETWORK_SIZE - 1][nodeIt].bias - Network::LEARNING_RATE * nodeContainer[NETWORK_SIZE - 1][nodeIt].nodeValue;
	}
}

void Network::hiddenLayerGradientDescentStoch() {

	for (int networkLayerIt = NETWORK_SIZE - 1; networkLayerIt > 0; networkLayerIt--) {


		for (int nodeIt = 0; nodeIt < networkLayers[networkLayerIt]; nodeIt++) {
			//ensures node value is 0
			nodeContainer[networkLayerIt][nodeIt].nodeValue = 0;

			for (int nodeValueIt = 0; nodeValueIt < nodeContainer[networkLayerIt][nodeIt].frontConnection.size(); nodeValueIt++) {
				nodeContainer[networkLayerIt][nodeIt].nodeValue += *(nodeContainer[networkLayerIt][nodeIt].frontConnection[nodeValueIt]->weight) * nodeContainer[networkLayerIt][nodeIt].frontConnection[nodeValueIt]->frontNode->nodeValue;
			}

			// finalizes the node value
			nodeContainer[networkLayerIt][nodeIt].nodeValue = networkActivationFunctionDerivative(nodeContainer[networkLayerIt][nodeIt]) * nodeContainer[networkLayerIt][nodeIt].nodeValue;

			for (int connectionIt = 0; connectionIt < nodeContainer[networkLayerIt][nodeIt].backConnection.size(); connectionIt++) {
				// completes the gradient and updates the weight
				*(nodeContainer[networkLayerIt][nodeIt].backConnection[connectionIt]->weight) = *(nodeContainer[networkLayerIt][nodeIt].backConnection[connectionIt]->weight) - Network::LEARNING_RATE * nodeContainer[networkLayerIt][nodeIt].backConnection[connectionIt]->backNode->value * nodeContainer[networkLayerIt][nodeIt].nodeValue;

			}

			//Uses the node value from the previous loops and uses it to update the bias
			nodeContainer[networkLayerIt][nodeIt].bias = nodeContainer[networkLayerIt][nodeIt].bias - Network::LEARNING_RATE * nodeContainer[networkLayerIt][nodeIt].nodeValue;
		}
	}
}

void Network::outputLayerGradientDescentBatch(std::vector<double> expectedOutput) {
	// calculate the output layer node values

	for (int nodeIt = 0; nodeIt < networkLayers[NETWORK_SIZE - 1]; nodeIt++) {

		// calculate the new node values
		nodeContainer[NETWORK_SIZE - 1][nodeIt].nodeValue = networkActivationFunctionDerivative(nodeContainer[NETWORK_SIZE - 1][nodeIt]) * 2 * (nodeContainer[NETWORK_SIZE - 1][nodeIt].value - expectedOutput[nodeIt]);
	
		for (int connectionIt = 0; connectionIt < nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection.size(); connectionIt++) {

			//update the weight
			*(nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection[connectionIt]->weight) = *(nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection[connectionIt]->weight) - Network::LEARNING_RATE * nodeContainer[NETWORK_SIZE - 1][nodeIt].nodeValue * nodeContainer[NETWORK_SIZE - 1][nodeIt].backConnection[connectionIt]->backNode->value;
		}

		// adds to the average node value to be applied later
		nodeContainer[NETWORK_SIZE - 1][nodeIt].averageBiasGradient += Network::LEARNING_RATE * nodeContainer[NETWORK_SIZE - 1][nodeIt].nodeValue;
	}
}

void Network::hiddenLayerGradientDescentStochBatch() {


}

void Network::loopAllLayers(std::vector<double> expectedOutput) {
	// loop through all the weights
	outputLayerGradientDescentStoch(expectedOutput);
	hiddenLayerGradientDescentStoch();

}

void Network::stochasticGradientDescent() {
	// update the weights and biases using stochastic gradient descent
	float totalCorrect = 0;


	for (int trainingDataIt = 0; trainingDataIt < networkTrainingData.size(); trainingDataIt++) {
		if(this->calculateNetworkOutput(networkTrainingData.at(trainingDataIt)))
			totalCorrect++;
		loopAllLayers(networkTrainingData.at(trainingDataIt).second);
		
		std::cout << "Perc Correct: " << totalCorrect / (trainingDataIt + 1) * 100 << "%" << std::endl;
	}

}

void Network::miniBatchGradientDescent() {
	// update the weights and biases using mini batch gradient descent
}

void Network::fullBatchGradientDescent() {
	// update the weights and biases using full batch gradient descent
}

double Network::networkActivationFunctionDerivative(Node currentNode) {
	switch (currentActivationFunction) {
	case Sigmoid:
		return this->sigmoidActivationDerivative(currentNode);
		break;
	case ReLU:
		return this->ReLUActivationDerivative(currentNode.value);
		break;
	case LeakyReLU:
		return this->LeakyReLUActivationDerivative(currentNode.value);
		break;
	case Tanh:
		return this->TanhActivationDerivative(currentNode.value);
		break;
	case Xcube:
		return this->XcubeActivationDerivative(currentNode.value);
		break;
	case AbsoluteValue:
		return this->AbsoluteValueActivationDerivative(currentNode.value);
		break;
	}

	return 0;
}

//---------------------Activation Functions------------------------------------------------

double Network::sigmoidActivation(double value) {
	return 1 / (1 + exp(-value));
}

double Network::sigmoidActivationDerivative(Node currentNode) {
	// change the activation function to sigmoid derivative
	return  currentNode.value * (1 - currentNode.value);

}

double Network::ReLUActivation(double value) {
	if (value > 0) {
		return value;
	}
	else {
		return 0;
	}
}

double Network::ReLUActivationDerivative(double value) {
	// change the activation function to ReLU derivative
	if (value > 0) {
		return 1;
	}
	else {
		return 0;
	}

}

double Network::LeakyReLUActivation(double value) {
	// change the activation function to Leaky ReLU
	if (value > 0) {
		return value;
	}
	else {
		return 0.01 * value;
	}
}

double Network::LeakyReLUActivationDerivative(double value) {
	// change the activation function to Leaky ReLU derivative
	if (value > 0) {
		return 0;
	}
	else {
		return 0.01;
	}

	return 0;
}

double Network::TanhActivation(double value) {
	// change the activation function to Tanh
	return tanh(value);
}

double Network::TanhActivationDerivative(double value) {
	// derive of tanh
	return (1 - pow(tanh(value), 2));
}

double Network::XcubeActivation(double value) {
	// This one sucks
	// change the activation function to X^3
	return pow(value, 3);
}

double Network::XcubeActivationDerivative(double value) {
	// change the activation function to X^3 derivative
	return 3 * pow(value, 2);
}

double Network::AbsoluteValueActivation(double value) {
	// this one also sucks
	// change the activation function to Absolute Value
	return abs(value);
}

double Network::AbsoluteValueActivationDerivative(double value) {
	// change the activation function to Absolute Value derivative

	return value / abs(value);
}

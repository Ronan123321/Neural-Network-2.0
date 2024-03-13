#include "Network.h"

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

	}
}

//-----------------------Initialization--------------------------------------------

void Network::inputLayerIntialize() {
	std::vector<Node> pushBackNodeContainer;

	for (int inputLayerIt = 0; inputLayerIt < networkLayers[0]; inputLayerIt++) {
		Node pushBackNode;
		pushBackNodeContainer.push_back(pushBackNode);
	}
	nodeContainer.push_back(pushBackNodeContainer);
}

void Network::outputLayerInitialize() {
	int networkLastLayer = (NETWORK_SIZE - 1);
	std::vector<Node> pushBackNodeContainer;

	for (int outputLayerIt = 0; outputLayerIt < networkLastLayer; outputLayerIt++) {
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
	}
}

//---------------------Connections------------------------------------------------

void Network::initializeAllNodeConnections() {
	
	// loop first layer



}

void Network::connectInputLayer() {
	const int currentLayer = 0;
	const int nextLayer = 1;

	for (int inputLayerIt = 0; inputLayerIt < networkLayers[currentLayer]; inputLayerIt++) {
	
	
	}
}

void Network::connectOutputLayer() {
	const int currentLayer = 0;
	const int nextLayer = NULL;

}

void Network::connectHiddenLayers() {


}
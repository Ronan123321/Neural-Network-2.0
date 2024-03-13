#pragma once
#include "Node.h"
#include <vector>
#include <iostream>

// TODO consider making the layeIntializers take a function variable so its more universal 

class Network
{
public:

	void establishNodes(); // maybe make private and make run when network is contructed

private:

	// maybe figure out a better way to do this or check that Netowrk size and the array match
	static const int NETWORK_SIZE = 3;
	int networkLayers[NETWORK_SIZE] = {2, 2, 2};



	std::vector<std::vector<Node>> nodeContainer;


	void inputLayerIntialize();

	void outputLayerInitialize();

	void hiddenLayersIntialize();

	void initializeAllNodeConnections();

	void connectInputLayer();

	void connectOutputLayer();

	void connectHiddenLayers();

};
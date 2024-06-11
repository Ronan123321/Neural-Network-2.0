#pragma once
#include "Connection.h"
#include <vector>



class Node
{
private:
	double bias;
	double value;
	double nodeValue;
	double averageBiasGradient;

	Node();
	Node(bool hasBias);

	std::vector<Connection*> frontConnection;
	std::vector<Connection*> backConnection;

friend Network;
};
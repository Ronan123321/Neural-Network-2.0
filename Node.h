#pragma once
#include "Connection.h"

class Network;

class Node
{
private:
	double bias;

	Node();

	std::vector<Connection*> frontConnection;
	std::vector<Connection*> backConnection;

friend Network;
};
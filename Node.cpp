#include "Node.h"
#include <random>
#include <iostream>

Node::Node() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<double> dist(-0.1, 0.1);

	this->bias = dist(rng);
	std::cout << bias << std::endl;
	frontConnection.push_back(nullptr);
	backConnection.push_back(nullptr);
}
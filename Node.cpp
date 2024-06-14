#include "Node.h"
#include <random>
#include <iostream>

Node::Node(): value(0), nodeValue(0), averageBiasGradient(0) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<double> dist(-0.1, 0.1);

	this->bias = 1; // chabge back to dist(rng)
}

Node::Node(bool hasBias): value(0), nodeValue(0), averageBiasGradient(0) {
	if (hasBias) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_real_distribution<double> dist(-0.1, 0.1);

		this->bias = 1; // chabge back to dist(rng)
	}
	else {
		this->bias = NULL;
	}
}
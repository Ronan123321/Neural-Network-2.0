#include "Connection.h"
#include <random>


Connection::Connection(std::shared_ptr<Node> frontNode, std::shared_ptr<Node> backNode)
	: frontNode(frontNode), backNode(backNode)
{

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<double> dist(-0.1, 0.1);
	
	this->weight = std::make_shared<double>(dist(rng)); // change back to dist(rng)
	this->averageWeightGradient = std::make_shared<double>(0);
}

Connection::Connection(std::shared_ptr<Node> frontNode, std::shared_ptr<Node> backNode, std::shared_ptr<double> weight, std::shared_ptr<double> averageWeightGradient)
	: frontNode(frontNode), backNode(backNode), weight(weight), averageWeightGradient(averageWeightGradient)
{
}
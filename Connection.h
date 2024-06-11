#pragma once
#include <memory>

class Node;
class Network;

class Connection
{
friend Network;

	Connection(std::shared_ptr<Node> frontNode, std::shared_ptr<Node> backNode);

	Connection(std::shared_ptr<Node> frontNode, std::shared_ptr<Node> backNode, std::shared_ptr<double> weight, std::shared_ptr<double> averageWeightGradient);
	
	std::shared_ptr<Node> frontNode;
	std::shared_ptr<Node> backNode;
	std::shared_ptr<double> weight;
	std::shared_ptr<double> averageWeightGradient;
};
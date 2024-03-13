#pragma once


class Node;
class Network;

class Connection
{
friend Node;
friend Network;

	Node* frontNode;
	Node* backNode;
	double weight;

};
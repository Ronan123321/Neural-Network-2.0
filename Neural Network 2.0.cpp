#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Network.h"

std::vector<std::pair<std::vector<double>, std::vector<double>>> createTrainingData() {
    std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData; // for some reason after declaring this it jumps down to the return statement then comes back up
    std::fstream trainingDataFile;

    std::ifstream file("TrainingData/mnist_train.csv");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string field;
        std::vector<double> dataVec;
        std::vector<double> labelVec;

        if (std::getline(ss, field, ',')) {
            int label = std::stoi(field);  // Convert the label to an integer
            labelVec.assign(10, 0); // initialize the vector to 0
            labelVec[label] = 1; // set the label to 1
        }

        while (std::getline(ss, field, ',')) {
            double value = std::stod(field);  // Convert the field to a double

            dataVec.push_back(value);
        }

        trainingData.push_back(std::make_pair(dataVec, labelVec));
    }

    return trainingData;
}



int main()
{
    Network newNetwork;

    std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData;

    trainingData = createTrainingData();

    newNetwork.displayOutput = true;
    newNetwork.passTrainingData(trainingData);
    
    newNetwork.ReluTESTING();
    newNetwork.runStochDescent(Network::ActivationFunctionType::Sigmoid);
	//newNetwork.runMiniBatchDescent(Network::ActivationFunctionType::Sigmoid, 100);
	//newNetwork.runFullBatchDescent(Network::ActivationFunctionType::LeakyReLU, 5);

    std::cin.get();
}
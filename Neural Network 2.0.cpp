#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Network.h"

std::vector<std::pair<std::vector<double>, std::vector<double>>> createTrainingLetters() {
    std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData; // for some reason after declaring this it jumps down to the return statement then comes back up
    std::fstream trainingDataFile;

    std::ifstream file("TrainingData/letter-recognition.csv");
    std::string line;

	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string field;
		std::vector<double> dataVec;
		std::vector<double> labelVec;

		if (std::getline(ss, field, ',')) {
			int label = field[0] - 65;  // Convert the label to an integer
			labelVec.assign(26, 0); // initialize the vector to 0
			labelVec[label] = 1; // set the label to 1
		}

		while (std::getline(ss, field, ',')) {
			double value = std::stod(field);  // Convert the field to a double and make it between 0 and 1

			dataVec.push_back(value);
		}

		trainingData.push_back(std::make_pair(dataVec, labelVec));
	}

    return trainingData;
}

std::vector<std::pair<std::vector<double>, std::vector<double>>> createTrainingDataMNIST() {
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
			double value = std::stod(field) / 255;  // Convert the field to a double and make it between 0 and 1

            dataVec.push_back(value);
        }

        trainingData.push_back(std::make_pair(dataVec, labelVec));
    }

    return trainingData;
}

std::vector<std::pair<std::vector<double>, std::vector<double>>> createTrainingData232() {
    std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData;

    for (int trainingIt = 0; trainingIt < 300; trainingIt++) {
        trainingData.push_back(std::make_pair(std::vector<double>{1, 0}, std::vector<double>{0, 1}));
        trainingData.push_back(std::make_pair(std::vector<double>{0, 1}, std::vector<double>{1, 0}));
    }

	return trainingData;
}

int main()
{
    Network newNetwork;

    std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingData;

    trainingData = createTrainingDataMNIST();
	//trainingData = createTrainingLetters();
	//trainingData = createTrainingData232();

    newNetwork.displayOutput = true;
    newNetwork.passTrainingData(trainingData);

	//newNetwork.currentActivationFunction = Network::ActivationFunctionType::Sigmoid;
	//newNetwork.runNetworkWithTrainingData(true);
    std::cout << "Descent Started\n";
	newNetwork.totalEpoch = 5;
    newNetwork.runStochDescent(Network::ActivationFunctionType::SeLu);
	//newNetwork.runMiniBatchDescent(Network::ActivationFunctionType::AbsoluteValue, 100);
	//newNetwork.runFullBatchDescent(Network::ActivationFunctionType::Sigmoid, 10);


    std::cin.get();
} 

/*

*/
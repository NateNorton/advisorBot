#include "BotMain.h"
#include <iostream>
#include <vector>
#include "CSVReader.h"

BotMain::BotMain() {
}

void BotMain::init() {
	std::string userInput;
	currentTime = orderBook.getEarliestTime();
	wallet.insertCurrency("BTC", 10);
	while (true) {
		userInput = getUserInput();
		parseInput(userInput);
	}
}

std::string BotMain::getUserInput() {
	std::string userInput;
	std::cout << "Please enter a command, or help for a list of commands" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::getline(std::cin, userInput);
	return userInput;
}

void BotMain::printHelp() {
	std::cout << "The available commands are: help, help <cmd>, avg, prod, min, max, predict, step and time" << std::endl;
}

void BotMain::helpCmd(std::string input) {
	if (input == "help") {
		std::cout << "'help: prints a list of commands available to the bot" << std::endl;
	}
	else if (input == "prod") {
		std::cout << "prod: lists all available products" << std::endl;
	}
	else if (input == "min") {
		std::cout << "min product bid/ask: finds the minimum bid or ask for the declared product in the current time step. Example - min ETH/BTC ask" << std::endl;
	}
	else if (input == "max") {
		std::cout << "max product bid/ask: finds the maximum bid or ask for the declared product in the current time step. Example - max ETH/BTC ask" << std::endl;
	}
	else if (input == "avg") {
		std::cout << "avg product ask/bid timesteps: compute average ask or bid for the declared product over the declared number of timesteps. Example - avg ETH/BTC ask 10" << std::endl;
	}
	else if (input == "predict") {
		std::cout << "predict max/min product ask/bid: predict the max or min ask or bid for the declared product for the next time step. Example: predict ETH/BTC bid" << std::endl;
	}
	else if (input == "time") {
		std::cout << "time: state the current time in the dataset, i.e. which timeframe are we currently looking at" << std::endl;
	}
	else if (input == "step") {
		std::cout << "step: move to the next time step" << std::endl;
	}
	else {
		invalidInput();
	}
}

void BotMain::listProd() {
	std::vector<std::string> products
}

void BotMain::printMin(std::string product, OrderBookType type) {
	std::cout << "printing minimum" << std::endl;
}

void BotMain::printMax(std::string product, OrderBookType type) {
	std::cout << "printing maximum" << std::endl;
}

void BotMain::printAvg(std::string product, OrderBookType type, unsigned int timeSteps) {
	std::cout << "printing average" << std::endl;
}

void BotMain::printPredict(std::string maxMin, std::string product, OrderBookType type) {
	std::cout << "printing the prediction" << std::endl;
}

void BotMain::getCurrentTime() {
	std::cout << "Current time is: " << currentTime << std::endl;
}

void BotMain::advanceTime() {
	std::cout << "Going to next time frame. " << std::endl;
	for (std::string p : orderBook.getKnownProducts()) {
		std::cout << "matching " << p << std::endl;
		std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
		std::cout << "Sales: " << sales.size() << std::endl;
		for (OrderBookEntry& sale : sales) {
			std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
			if (sale.username == "simuser") {
				// update the wallet
				wallet.processSale(sale);
			}
		}
	}
	currentTime = orderBook.getNextTime(currentTime);
}

void BotMain::invalidInput() {
	std::cout << "invalid input" << std::endl;
}

void BotMain::parseInput(std::string& input) {
	InputType inputType;
	std::vector<std::string> inputWords = CSVReader::tokenise(input, ' ');
	//if size of vector is 0 no command was entered and therefore invalid
	if (inputWords.size() == 0) {
		invalidInput();
	}
	// if length is 1 then either help, prod, time or step
	if (inputWords.size() == 1) {
		//help
		if (inputWords[0] == "help") {
			printHelp();
		}
		//prod
		else if (inputWords[0] == "prod") {
			listProd();
		}
		//time
		else if (inputWords[0] == "time") {
			getCurrentTime();
		}
		//step
		else if (inputWords[0] == "step") {
			advanceTime();
		}
		else {
			invalidInput();
		}
	}
	//if length is 2 then helpcmd
	if (inputWords.size() == 2) {
		std::string command = inputWords[1];
		helpCmd(command);
	}
	//if length is 3 then min, max
	if (inputWords.size() == 3) {
		std::string product = inputWords[1];
		OrderBookType orderType = OrderBookEntry::stringToOrderBookType(inputWords[2]);
		//min
		if (inputWords[0] == "min") {
			printMin(product, orderType);
		}
		//max
		else if (inputWords[0] == "max") {
			printMax(product, orderType);
		}
		else {
			invalidInput();
		}
	}
	//if length 4 then avg, predict
	if (inputWords.size() == 4) {
		//average
		if (inputWords[0] == "avg") {
			try {
				OrderBookType orderType = OrderBookEntry::stringToOrderBookType(inputWords[2]);
				unsigned int timestepAmount = stoi(inputWords[3]);
				printAvg(inputWords[1], orderType, timestepAmount);
			}
			catch (const std::exception&) {
			}
		}
		//predict
		else if (inputWords[0] == "predict") {
			OrderBookType orderType = OrderBookEntry::stringToOrderBookType(inputWords[3]);
			printPredict(inputWords[1], inputWords[2], orderType);
		}
		else {
			invalidInput();
		}
	}
}
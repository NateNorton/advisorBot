#pragma once
#include <string>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

enum class InputType {
	help, 
	helpcmd, 
	prod, 
	min, 
	max, 
	avg, 
	predict, 
	time,
	step,
	invalid};

class BotMain
{
public:
	BotMain();
	/** call to initialize the advisor bot*/
	void init();
private:
	/** bot will ask for user input */
	std::string getUserInput();
	/** prints the bot commands */
	static void printHelp();
	/** prints more information on the desired command */
	void helpCmd(std::string command);
	/** parse user input and returns InputType*/
	void parseInput(std::string& input);
	/** list available products in current time step */
	void listProd();
	/** compute minimum bid/ask for product in current time step */
	void printMin(std::string product, OrderBookType type);
	/** compute maximum bid/ask for product in current time step*/
	void printMax(std::string product, OrderBookType type);
	/** comput average ask/bid for product over certain amount of time steps*/
	void printAvg(std::string product, OrderBookType type, unsigned int timeSteps);
	/** predict max/min product for ask/bid */
	void printPredict(std::string maxMin, std::string product, OrderBookType type);
	/** states the current time in dataset */
	void getCurrentTime();
	/** call to move to next time step */
	void advanceTime();
	/** notifies of invalid input */
	static void invalidInput();
	std::string currentTime;
	OrderBook orderBook{ "test.csv" };
	Wallet wallet;
};


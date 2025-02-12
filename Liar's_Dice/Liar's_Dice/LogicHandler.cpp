#include "LogicHandler.h"
#include <iostream>
#include <vector>

using std::vector;
using std::string;

// Checks if the new bid has a higher value then the last bid
// Returns true if the new bid is a higher value
//TODO vector<int>* bid from opencv module. This comes directly from OpenCV, so it will be scrapped soon
bool LogicHandler::raise(const vector<int>* lastBid, const vector<int>* newBid)
{
	//check if new bid is not empty
	//check for the max amount of 5 dice per bid
	
	//check if newBid contains out of the same values//check if newBid containts valid numbers
	if (newBid->size() == 0 || newBid->size() > 5 || !validDice(newBid) || !sameValues(newBid)) return false;

	//check if lastBid is empty AKA first bid in game
	//check if the new value of eyes is higher
	if (lastBid == nullptr || lastBid[0] < newBid[0]) return true;

	//check if the eyes value 
	if (lastBid[0] == newBid[0]) 
	{
		if (lastBid->size() < newBid->size()) return true;
	}

	return false;
}

// Checks if the bid is incorrect. 
// Returns true if bid is incorrrect.
//TODO vector<int>* bid from opencv module. This comes directly from OpenCV, so it will be scrapped soon
bool LogicHandler::callBluff(vector<int>* actual, vector<int>* bid)
{
	return !containsElements(*actual, *bid);
}

// Checks if the bid is correct. 
// Returns true if bid is correct.
//TODO vector<int>* bid from opencv module. This comes directly from OpenCV, so it will be scrapped soon
bool LogicHandler::spotOn(vector<int>* actual, vector<int>* bid)
{
	return containsElements(*actual, *bid);
}



// Check if the content of vector 2 are in the content of vector 1
// Returns true if all elements of vector 2 are in vector 1. Therefor if the size of vector 2 is bigger than vector 1 return false
// ex: base[5, 2, 5]; comparison[5,5]; Checks if the two fives from comparison are in base; base contains the elements of comparison so return true
bool LogicHandler::containsElements( vector<int> base, vector<int> comparison) {
	if (comparison.size() == 0)
		std::cout << "Error: Vector comparison has no elements \n\t@LogicHandler.cpp \n\t@vecContainsElements(vector<int>, vector<int>)" << std::endl;

	if (comparison.size() > base.size())
		return false;

	for (int i = comparison.size() -1; i >= 0 ; i--) {
	//for (int i =  0; i < comparison.size(); i++) {
		auto result = find(base.begin(), base.end(), comparison[i]);
		
		if (result != base.end()) {
			base.erase(result);
			comparison.erase(comparison.begin() + i);
		}
		else
			return false;

		if (comparison.size() == 0)
			return true;
	}
	return false;
}

bool LogicHandler::vecContains(vector<int>* vec, int toFind) {
	return (find(vec->begin(), vec->end(), toFind) != vec->end());
}


// Checks if all the values in the given vector are the same
// Return true when all values are the same
// ex:	vector{ 5, 5, 5} returns true
//		vector{ 5, 5, 2} returns false
bool LogicHandler::sameValues(const vector<int>* vec) {
	int number = vec->at(0);
	for (int i = 0; i < vec->size(); i++) {
		if (vec->at(i) != number)
			return false;
	}
	return true;
}

// Check if the vector array filled with numbers are valid 6 sided die numbers
bool LogicHandler::validDice(const vector<int>* dice) {
	for (int i = 0; i < dice->size(); i++) {
		if (!validDie(dice->at(i)))
			return false;
	}
	return true;
}

// Check if the number is a valid 6 sided die number
bool LogicHandler::validDie(int die) {
	if (die < 1 || die > 6)
		return false;
	return true;
}
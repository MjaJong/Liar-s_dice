#pragma once
#include <vector>

using std::vector;
using std::string;

class LogicHandler {
	private:
		bool raise(const std::vector<int>*, const std::vector<int>*);
		bool callBluff(std::vector<int>*, std::vector<int>*);
		bool spotOn(std::vector<int>*, std::vector<int>*);

	public:
		bool containsElements(std::vector<int>, std::vector<int>);
		bool vecContains(std::vector<int>*, int);
		bool sameValues(const std::vector<int>*);
		bool validDice(const std::vector<int>*);
		bool validDie(int);
};

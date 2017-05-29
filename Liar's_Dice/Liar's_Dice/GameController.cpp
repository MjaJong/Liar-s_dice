#include "GameController.h"
#include "Player.h"
#include "LogicHandler.h"
#include "ReadDice.h"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

LogicHandler LH;
ReadDice RD;

int previousPlayer;
vector<int> curBid;

GameController::GameController(vector<Player> list)
{
	players = list;
	LH = LogicHandler();
	RD = ReadDice();
}

GameController::~GameController()
{

}

void GameController::pickFirstPlayer()
{
	//pick random player
	int pick = rand() % players.size() + 1;
	curPlayer = pick - 1;
	
	std::cout << "Player " << players[curPlayer].getName() << " has to begin the game." << std::endl;
	curBid = setBet();
}

void GameController::pickFirstPlayer(int player)
{
	if (player >= players.size()) { curPlayer = 0; }
	else { curPlayer = player; }

	checkPlayers();
	rollDice();

	std::cout << "Player " << players[curPlayer].getName() << " has to begin the game." << std::endl;
	curBid = setBet();
}

void GameController::pickNextPlayer()
{
	int amount = players.size();

	if (amount == (curPlayer + 1))
	{
		previousPlayer = curPlayer;
		curPlayer = 0;
	}
	else
	{
		previousPlayer = curPlayer;
		curPlayer = curPlayer + 1;
	}

	std::cout << "It's " << players[curPlayer].getName() << "'s turn." << std::endl;
}

void GameController::checkPlayers()
{
	for (int i = 0; i < players.size(); i ++)
	{
		if (players[i].getAmountOfDice() == 0)
		{
			deletePlayer(i);
		}
	}
	players.shrink_to_fit();

	if (players.size() == 1)
	{
		std::cout << "Player " << players[0].getName() << " has won the game." << std::endl;
		system("pause");
		exit(0);
	}

	if(players.size() <= 0)
	{
		std::cout << "There are no winners, only losers." << std::endl;
		system("pause");
		exit(0);
	}
}

void GameController::deletePlayer(int index)
{
	std::cout << "Player " << players[index].getName() <<  " is out of dice." << std::endl;
	players.erase(players.begin() + index);
}

void GameController::turn()
{
	int choice;

	std::cout << "Choose an action:" << std::endl;
	std::cout << "*Press 1 to raise current bid" << std::endl;
	std::cout << "*Press 2 to call spot on" << std::endl;
	std::cout << "*Press 3 to call bluff" << std::endl;

	std::cin >> choice;

	switch (choice)
	{
		case 1:
			raise();
			break;
		case 2:
			spotOn();
			break;
		case 3:
			callBluff();
			break;
		default:
			std::cout << "Key not recognized." << std::endl;
			turn();
			break;
	}
}

void GameController::rollDice()
{
	for (int i = 0; i < players.size(); i++)
	{
		//check amount of dice
		int diceAmount = players[i].getAmountOfDice();
		std::cout << players[i].getName() << " has to throw " << diceAmount << " dice." << std::endl;

		//set new dice vector
		std::cout << "Throw your dice and press enter." << std::endl;
		system("pause");
		vector<int> diceList = RD.CheckDice();

		if (diceList.size() == diceAmount)
		{
			players[i].setDice(diceList);
		}
		else
		{
			std::cout << "Please throw the correct amount of dice." << std::endl;
			i--;
		}
	}
}

void GameController::raise()
{
	bool check;

	//TODO check if the raise is possible anyway
	vector<int> newBid = RD.CheckDice();
	check = LH.raise(&curBid, &newBid);

	if (check)
	{
		//set new current bid
		std::cout << "New bid accepted." << std::endl;
		curBid = newBid;
	}
	else
	{
		//let the user bid again if last bid is incorrect
		std::cout << "Make sure your new bid is higher than the last bid" << std::endl;
		raise();
	}
}

//Method called when callBluff is selected. This removes a dice from either the previous player(true) or the current player(false).
void GameController::callBluff()
{
	vector<int> playerDice = players[previousPlayer].getDice();

	if(LH.callBluff(&playerDice, &curBid))
	{
		players[previousPlayer].reduceDice();
		pickFirstPlayer(previousPlayer);
	}
	else
	{
		players[curPlayer].reduceDice();
		pickFirstPlayer(curPlayer);
	}
}

//Method called when callBluff is selected. This removes a dice from either the whole table(true) or the current player(false).
void GameController::spotOn()
{
	vector<int> playerDice = players[previousPlayer].getDice();

	if(LH.spotOn(&playerDice, &curBid))
	{
		for (int i = 0; i < players.size(); i++) { if (i != curPlayer) players[i].reduceDice(); }
		pickFirstPlayer(curPlayer + 1);
	}
	else
	{
		players[curPlayer].reduceDice();
		pickFirstPlayer(curPlayer);
	}
}


vector<int> GameController::setBet()
{
	return RD.CheckDice();
}
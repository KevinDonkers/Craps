//Craps v4
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the header file that contains all the includes structures and prototypes for the program
//August 15th, 2016

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <windows.h>

using namespace std;

//Structures
struct User {
	string username;
	string fullname;
	int money;
	User(string uName, string fName, int earn){
		username = uName;
		fullname = fName;
		money = earn;
	}
};

struct Bet {
	string name;
	int value;
	bool won;
	Bet() {
		won = false;
	}
};

struct Roll{
	int die1;
	int die2;
	int total;
	Roll(){}
	Roll(int d1, int d2, int tot){
		die1 = d1;
		die2 = d2;
		total = tot;
	}
};

//Prototypes
Roll RollDice();
User checkAccount(string);
void updateUserList(User);
int calculateWinnings(vector<Bet>);
int findBet(string, vector<Bet>);
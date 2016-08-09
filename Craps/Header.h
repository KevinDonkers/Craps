//Craps v4
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the header file that contains all the includes structures and prototypes for the program
//August 15th, 2016

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
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

//Prototypes
int RollDice();
User checkAccount(string);
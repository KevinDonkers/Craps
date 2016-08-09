//Craps v2
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the header file that contains all the includes structures and prototypes for the program
//August 2nd, 2016

#include <string>
#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

//Structures
struct User {
	string username;
	string name;
	int money;
};

//Prototypes
int RollDice();
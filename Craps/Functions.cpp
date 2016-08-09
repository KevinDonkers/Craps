//Craps v1
//By Kevin Donkers, Justin Searle, Richard Estrada
//functions.cpp contains all the functions the main will use
//August 2nd, 2016

#include "Header.h"

//use the std namespace
using namespace std;
  
//compete with the computer rolling random dice
void RollDice(){
	//vars needed
	int die1;
	int die2;
	int total;

	int const MAX = 6;
	int const MIN = 1;

	//set random seed
	srand(time(0));


	//generate user rolls
	die1 = (rand() % (MAX - MIN + 1)) + 1;
	die2 = (rand() % (MAX - MIN + 1)) + 1;
	total = die1 + die2;

	//output rolls
	cout << "\n You rolled " << total << " (" << die1 << " & " << die2 << ")\n";

} //end of function
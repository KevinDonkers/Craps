//Craps v2
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the second version which has the basic game mechanics using 2 types of bets and the 2 roll phases
//August 2nd, 2016

#include "Header.h"

using namespace std;

//main function to execute all the code
int main(){
	string userName;
	int passChoice, roll, point;
	bool roundEnd = false;

	cout << "What is your Name?" << endl;
	while (!(cin >> userName)) {
		cout << "Bad Input" << endl;
	}

	//check the username in the user file

	cout << "Welcome to Craps" << endl;
	cout << "What would you like to bet?" << endl;
	cout << "1. Pass Line" << endl;
	cout << "2. Don't Pass Line" << endl;

	while (!(cin >> passChoice) || passChoice < 1 || passChoice > 2) {
		cout << "Bad Input" << endl;
	}
	roll = RollDice();
	
	//come out roll checks
	if (passChoice == 1) {//bet on pass line
		if (roll == 7 || roll == 11) {
			cout << "You Win!" << endl;
			roundEnd = true;
		}
		else if (roll == 2 || roll == 3 || roll == 12) {
			cout << "You Lose!" << endl;
			roundEnd = true;
		}
	}
	else if (passChoice == 2) {//bet on dont pass line
		if (roll == 7 || roll == 11) {
			cout << "You Lose!" << endl;
			roundEnd = true;
		}
		else if (roll == 2 || roll == 3 || roll == 12) {
			cout << "You Win!" << endl;
			roundEnd = true;
		}
	}

	if (!roundEnd) {//into point rolls
		point = roll;
		cout << "You rolled a point of " << point << endl;
		do {
			cout.flush();
			Sleep(1000);
			roll = RollDice();
			cout << "The point is " << point << endl;
		} while (roll != point && roll != 7);
		if (passChoice == 1) {
			if (roll == point) {
				cout << "You rolled the point, You Win!" << endl;
			}
			else {
				cout << "You rolled a 7 before the point again, You Lose!" << endl;
			}
		}
		else if (passChoice == 2) {
			if (roll == point) {
				cout << "You rolled the point, You Lose!" << endl;
			}
			else {
				cout << "You rolled a 7 before the point again, You Win!" << endl;
			}
		}
	}
	else {//natural rolled end the round
		cout << "Round Over" << endl;
		roundEnd = false;
	}


	cin.ignore();
	cin.get();
	return 0;
}
//Craps v1
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the first version which only rolls 2 dice and tells you the value
//August 2nd, 2016

#include "Header.h"

using namespace std;

//main function to execute all the code
int main(){
	string userName;
	int betChoice;

	cout << "What is your Name?" << endl;
	while (!(cin >> userName)) {
		cout << "Bad Input" << endl;
	}


	cout << "Welcome to Craps" << endl;
	cout << "What would you like to bet?" << endl;
	cout << "1. Pass Line" << endl;
	cout << "2. Don't Pass Line" << endl;

	while ((!(cin >> betChoice))) {
		cout << "Bad Input" << endl;
	}
	
	
	RollDice();
	return 0;
}
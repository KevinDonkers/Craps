//Craps v3
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the fourth version which has the functionality to update a users money in the file after each round
//August 15th, 2016

#include "Header.h"

using namespace std;

//main function to execute all the code
int main(){
	string userName;
	int passChoice, point, betIndex;
	bool roundEnd = false;

	Roll roll;
	vector<Bet> bets;

	cout << "What is your Username?" << endl;
	while (!(cin >> userName)) {
		cout << "Bad Input" << endl;
	}

	//check the username in the user file
	User user = checkAccount(userName);

	cout << user.username << ", " << user.fullname << ", " << user.money << endl;

	cout << "Hello " << user.fullname << ", Welcome to Craps" << endl;
	cout << "What would you like to bet?" << endl;
	cout << "1. Pass Line" << endl;
	cout << "2. Don't Pass Line" << endl;

	while (!(cin >> passChoice) || passChoice < 1 || passChoice > 2) {
		cout << "Bad Input" << endl;
	}
	roll = RollDice();
	
	//come out roll checks
	if (passChoice == 1) {//bet on pass line
		Bet choice1;
		choice1.name = "Pass Line";
		
		cout << "How much would you like to bet on the pass line?" << endl;
		while (!(cin >> choice1.value) || choice1.value < 1 || choice1.value > user.money) {
			cout << "Bad Input" << endl;
		}

		cout << "\nYou rolled " << roll.total << " (" << roll.die1 << " & " << roll.die2 << ")\n";

		if (roll.total == 7 || roll.total == 11) {
			cout << "You Win!" << endl;
			roundEnd = true;
			choice1.won = true;
		}
		else if (roll.total == 2 || roll.total == 3 || roll.total == 12) {
			cout << "You Lose!" << endl;
			roundEnd = true;
			choice1.won = false;
		}
		bets.push_back(choice1);
	}
	else if (passChoice == 2) {//bet on dont pass line
		Bet choice2;
		choice2.name = "Don't Pass Line";

		cout << "How much would you like to bet on the don't pass line?" << endl;
		while (!(cin >> choice2.value) || choice2.value < 1 || choice2.value > user.money) {
			cout << "Bad Input" << endl;
		}

		if (roll.total == 7 || roll.total == 11) {
			cout << "You Lose!" << endl;
			roundEnd = true;
			choice2.won = false;
		}
		else if (roll.total == 2 || roll.total == 3 || roll.total == 12) {
			cout << "You Win!" << endl;
			roundEnd = true;
			choice2.won = true;
		}
		bets.push_back(choice2);
	}

	if (!roundEnd) {//into point rolls

		for (int i = 0; i < bets.size(); i++) {
			bets.at(i).won = false;
		}

		point = roll.total;
		cout << "You rolled a point of " << point << endl;
		do {
			cout.flush();
			Sleep(1000);
			roll = RollDice();
			cout << "The point is " << point << endl;
			cout << "\nYou rolled " << roll.total << " (" << roll.die1 << " & " << roll.die2 << ")\n";
		} while (roll.total != point && roll.total != 7);
		
		//check the point rolls
		if (passChoice == 1) {
			if (roll.total == point) {				
				cout << "You rolled the point, You Win!" << endl;
				if ((betIndex = findBet("Pass Line", bets)) >= 0) {
					bets.at(betIndex).won = true;
				}
			}
			else {
				cout << "You rolled a 7 before the point again, You Lose!" << endl;
				if ((betIndex = findBet("Pass Line", bets)) >= 0) {
					bets.at(betIndex).won = false;
				}
			}
		}
		else if (passChoice == 2) {
			if (roll.total == point) {
				cout << "You rolled the point, You Lose!" << endl;
				if ((betIndex = findBet("Don't Pass Line", bets)) >= 0) {
					bets.at(betIndex).won = false;
				}
			}
			else {
				cout << "You rolled a 7 before the point again, You Win!" << endl;
				if ((betIndex = findBet("Don't Pass Line", bets)) >= 0) {
					bets.at(betIndex).won = true;
				}
			}
		}
	}
	else {//natural rolled end the round
		cout << "Round Over" << endl;
		roundEnd = false;
	}

	cout << "\nwinnings: " << calculateWinnings(bets) << endl;
	cout << "user money: " << user.money << endl;

	user.money += calculateWinnings(bets);

	for (int i = 0; i < bets.size(); i++) {
		cout << endl << bets.at(i).name << ", " << bets.at(i).value << ", " << bets.at(i).won << endl;
	}

	cout << "after user money: " << user.money << endl;

	updateUserList(user);

	cin.ignore();
	cin.get();
	return 0;
}
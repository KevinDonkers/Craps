//Craps v3
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the fourth version which has the functionality to update a users money in the file after each round
//August 15th, 2016

#include "Header.h"

using namespace std;

//main function to execute all the code
int main(){
	string userName, additionalBets;
	int passChoice, point, betIndex, subPassChoice, subPassValue;
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

	//game loop
	while (true) {

		//menu
		cout << "1. Pass Line" << endl;
		cout << "2. Don't Pass Line" << endl;
		cout << "3. Exit" << endl;

		//get valid input
		while (!(cin >> passChoice) || passChoice < 1 || passChoice > 3) {
			cout << "Bad Input" << endl;
		}

		//exit
		if (passChoice == 3) {
			break;
		}

		//more bets?
		cout << "Do you want additional bets? (y/n)";

		while (!(cin >> additionalBets)) {
			cout << "Bad Input" << endl;

		}

		while (additionalBets == "y" || additionalBets == "Y") {

			cout << "1. Aces or box cars" << endl;
			cout << "2. Eleven" << endl;
			cout << "3. Ace Duece" << endl;
			cout << "4. Done Betting." << endl;

			//get valid input
			while (!(cin >> subPassChoice) || subPassChoice < 1 || subPassChoice > 4) {
				cout << "Bad Input" << endl;
			}

			if (subPassChoice == 4) {
				break;
			}

			cout << "How much would you like to bet?" << endl;
			Bet additionalChoice;

			//get valid input
			while (!(cin >> subPassValue) || subPassValue < 1 || subPassValue > user.money) {
				cout << "Bad Input" << endl;
			}

			additionalChoice.value = subPassValue;

			switch (subPassChoice) {

				case 1:
					additionalChoice.name = "aces or box cars";					
					break;

				case 2:
					additionalChoice.name = "eleven";
					break;

				case 3:
					additionalChoice.name = "ace duece";
					break;
			}
			bets.push_back(additionalChoice);
		}

		roll = RollDice();

		//check additional bets
		if (roll.total == 11) {
			if ((betIndex = findBet("eleven", bets)) >= 0) {
				bets.at(betIndex).won = true;
			}
		}
		else {
			if ((betIndex = findBet("eleven", bets)) >= 0) {
				bets.at(betIndex).won = false;
			}
		}

		if (roll.total == 12) {
			if ((betIndex = findBet("aces or box cars", bets)) >= 0) {
				bets.at(betIndex).won = true;
			}
		}
		else {
			if ((betIndex = findBet("aces or box cars", bets)) >= 0) {
				bets.at(betIndex).won = false;
			}
		}

		if (roll.total == 3) {
			if ((betIndex = findBet("ace duece", bets)) >= 0) {
				bets.at(betIndex).won = true;
			}
		}
		else {
			if ((betIndex = findBet("ace duece", bets)) >= 0) {
				bets.at(betIndex).won = false;
			}
		}

		//come out roll checks
		if (passChoice == 1) {//bet on pass line
			Bet choice1;
			choice1.name = "Pass Line";

			// Fetch tab key state.
			//SHORT tabKeyState = GetAsyncKeyState(VK_TAB);
			//bool tab = false;
			// Test high bit - if set, key was down when GetAsyncKeyState was called.
			//if ((1 << 16) & tabKeyState)
			//{
			//	tab = true;
			//}

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

			//if (tab) {
			//	choice1.value = user.money;
			//}
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

		/*
		 *
		 */
		if (!roundEnd) {//into point rolls

			//for (int i = 0; i < bets.size(); i++) {
			//	bets.at(i).won = false;
			//}
		
			point = roll.total;

			//my comment
			while (true) {

				//menu and stuff
				cout << "4. Bet on 4 being rolled." << endl;
				cout << "5. Bet on 5 being rolled." << endl;
				cout << "6. Bet on 6 being rolled." << endl;
				cout << "8. Bet on 8 being rolled." << endl;
				cout << "9. Bet on 9 being rolled." << endl;
				cout << "10. Bet on 10 being rolled." << endl;
				cout << "7. Exit." << endl;

				//get valid input
				while (!(cin >> subPassChoice) || subPassChoice < 4 || subPassChoice > 10) {
					cout << "Bad Input" << endl;
				}

				if (subPassChoice == 7) {
					break;
				}

				cout << "How much would you like to bet?" << endl;
				Bet additionalChoice;

				//get valid input
				while (!(cin >> subPassValue) || subPassValue < 1 || subPassValue > user.money) {
					cout << "Bad Input" << endl;
				}

				additionalChoice.value = subPassValue;
				additionalChoice.name = "bet " + to_string(subPassChoice);
				
				bets.push_back(additionalChoice);
			}


			cout << "You rolled a point of " << point << endl;
			do {
				cout.flush();
				Sleep(1000);
				roll = RollDice();

				cout << "The point is " << point << endl;
				cout << "\nYou rolled " << roll.total << " (" << roll.die1 << " & " << roll.die2 << ")\n";

				//check bets
				if (roll.total == 4) {		
					
					if ((betIndex = findBet("bet 4", bets)) >= 0) {
						cout << " TEST 4\n\n";
						cout << betIndex;
						bets.at(betIndex).won = true;
					}
				}
				else if (roll.total == 5) {
					if ((betIndex = findBet("bet 5", bets)) >= 0) {					
						cout << " TEST 5\n\n";
						cout << betIndex;
						bets.at(betIndex).won = true;
					}
				}
				else if (roll.total == 6) {					
					if ((betIndex = findBet("bet 6", bets)) >= 0) {
						cout << " TEST 6\n\n";
						cout << betIndex;
						bets.at(betIndex).won = true;
					}
				}
				else if (roll.total == 8) {					
					if ((betIndex = findBet("bet 8", bets)) >= 0) {
						cout << " TEST 8\n\n";
						cout << betIndex;
						bets.at(betIndex).won = true;
					}
				}
				else if (roll.total == 9) {					
					if ((betIndex = findBet("bet 9", bets)) >= 0) {
						cout << " TEST 9\n\n";
						cout << betIndex;
						bets.at(betIndex).won = true;
					}
				}
				else if (roll.total == 10) {
					if ((betIndex = findBet("bet 10", bets)) >= 0) {
						bets.at(betIndex).won = true;
					}
				}
				
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

		bets.clear();

	} //end of loop
	
	//cin.ignore();
	//cin.get();
	//return 0;
}
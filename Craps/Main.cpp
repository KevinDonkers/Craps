//Craps v5
//By Kevin Donkers, Justin Searle, Richard Estrada
//This is the fifth version which has the functionality of multiple bets at different times
//August 15th, 2016

#include "Header.h"

using namespace std;

//main function to execute all the code
int main(){
	string userName, additionalBets;
	int passChoice, point, betIndex, subPassChoice, subPassValue, total;
	bool roundEnd = false;

	Roll roll;
	vector<Bet> bets;

	//ask for username
	cout << "What is your Username?" << endl;
	while (!(cin >> userName)) {
		cout << "Bad Input" << endl;
	}

	//check the username in the user file
	User user = checkAccount(userName);	

	//welcome message
	cout << endl << "Hello " << user.fullname << ", Welcome to Craps." << endl;
	cout << "What would you like to bet?" << endl;

	//game loop
	while (true) {

		//menu
		cout << endl << "You have: $" << user.money << " to bet." << endl;
		cout << "1. Pass Line" << endl;
		cout << "2. Don't Pass Line" << endl;
		cout << "3. Exit" << endl;

		//get valid input
		while (!(cin >> passChoice) || passChoice < 1 || passChoice > 3) {
			cout << "Bad Input" << endl;
		}

		//exit game loop
		if (passChoice == 3) {
			break;
		}

		//roll the dice
		roll = RollDice();
		Bet choice;

		//roll checks
		if (passChoice == 1) {//bet on pass line			
			choice.name = "pass line";						
		}
		else if (passChoice == 2) {//bet on dont pass line			
			choice.name = "dont pass line";
		}

		//ask for bet amount
		cout << "How much would you like to bet?" << endl;
		while (!(cin >> choice.value) || choice.value < 1 || choice.value > user.money) {
			cout << "Bad Input" << endl;
		}

		//add bet to the vector of bets
		bets.push_back(choice);

		//more bets?
		cout << "Do you want additional bets? (y/n): ";
		while (!(cin >> additionalBets)) {
			cout << "Bad Input" << endl;

		}

		//only print menu once for additional bets
		if ((additionalBets == "y" || additionalBets == "Y")) {
			cout << "1. Aces or box cars" << endl;
			cout << "2. Eleven" << endl;
			cout << "3. Ace Duece" << endl;
			cout << "4. Done Betting." << endl;
		}
		
		//loop for additional bet menu
		while (additionalBets == "y" || additionalBets == "Y") {

			//get valid input
			while (!(cin >> subPassChoice) || subPassChoice < 1 || subPassChoice > 4) {
				cout << "Bad Input" << endl;
			}

			//break from additional bet loop
			if (subPassChoice == 4) {
				break;
			}

			//get bet amount
			cout << "How much would you like to bet?" << endl;
			Bet additionalChoice;

			//get valid input
			while (!(cin >> subPassValue) || subPassValue < 1 || subPassValue > user.money) {
				cout << "Bad Input" << endl;
			}

			additionalChoice.value = subPassValue;

			//store the bet name based on choice
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

			//check to see if user has already bet on this
			if (betIndex = findBet(additionalChoice.name, bets) >= 0) {
				bets.at(betIndex).value = additionalChoice.value;
			}
			else {
				bets.push_back(additionalChoice);
			}

			cout << "Type another bet, or 4 to exit" << endl;
		} //end of additional bet loop

		//show roll
		cout << "\nYou rolled " << roll.total << " (" << roll.die1 << " & " << roll.die2 << ")\n";

		//roll check
		if (passChoice == 1 && (betIndex = findBet("pass line", bets)) >= 0) { //bet on pass line

			if ((roll.total == 7 || roll.total == 11)) {
				bets.at(betIndex).won = true;
				roundEnd = true;
			}
			else if (roll.total == 2 || roll.total == 3 || roll.total == 12) {
				bets.at(betIndex).won = false;
				roundEnd = true;
			}			

		} else if (passChoice == 2  && (betIndex = findBet("dont pass line", bets)) >= 0) {//bet on dont pass line

			if (roll.total == 7 || roll.total == 11) {
				bets.at(betIndex).won = false;
				roundEnd = true;
			}
			else if (roll.total == 2 || roll.total == 3 || roll.total == 12) {
				bets.at(betIndex).won = true;
				roundEnd = true;
			}			

		}				

		//check additional bets
		if (roll.total == 11 && (betIndex = findBet("eleven", bets)) >= 0) {
			bets.at(betIndex).won = true;			
		}
		else if (roll.total == 12 && (betIndex = findBet("aces or box cars", bets)) >= 0) {
			bets.at(betIndex).won = true;			
		}
		else if (roll.total == 3 && (betIndex = findBet("ace duece", bets)) >= 0) {
			bets.at(betIndex).won = true;			
		}

		/*
		 * second round
		 */
		if (!roundEnd) {//into point rolls

			point = roll.total;

			//menu and stuff
			cout << "4. Bet on 4 being rolled." << endl;
			cout << "5. Bet on 5 being rolled." << endl;
			cout << "6. Bet on 6 being rolled." << endl;
			cout << "8. Bet on 8 being rolled." << endl;
			cout << "9. Bet on 9 being rolled." << endl;
			cout << "10. Bet on 10 being rolled." << endl;
			cout << "7. Exit." << endl;

			//more bets loop
			while (true) {

				//get valid input
				while (!(cin >> subPassChoice) || subPassChoice < 4 || subPassChoice > 10) {
					cout << "Bad Input" << endl;
				}

				//break from more bets loop
				if (subPassChoice == 7) {
					break;
				}

				//get bet amount
				cout << "How much would you like to bet?" << endl;
				Bet additionalChoice;

				//get valid input
				while (!(cin >> subPassValue) || subPassValue < 1 || subPassValue > user.money) {
					cout << "Bad Input" << endl;
				}

				//
				additionalChoice.value = subPassValue;
				additionalChoice.name = "bet " + to_string(subPassChoice);
				
				//check to see if user has already bet on this bet
				if (betIndex = findBet(additionalChoice.name, bets) >= 0) {
					bets.at(betIndex).value = additionalChoice.value;
				}
				else {
					bets.push_back(additionalChoice);
				}

				cout << "Type another bet, or 7 to exit" << endl;
			}

			//show roll
			cout << "You rolled a point of " << point << endl;
			do {
				cout.flush();
				Sleep(1000);
				roll = RollDice();

				cout << "The point is " << point << endl;
				cout << "\nYou rolled " << roll.total << " (" << roll.die1 << " & " << roll.die2 << ")\n";

				//check bets
				if (roll.total == 4 && (betIndex = findBet("bet 4", bets)) >= 0) {						
					bets.at(betIndex).won = true;					
				}
				else if (roll.total == 5 && (betIndex = findBet("bet 5", bets)) >= 0) {					
					bets.at(betIndex).won = true;					
				}
				else if (roll.total == 6 && (betIndex = findBet("bet 6", bets)) >= 0) {
					bets.at(betIndex).won = true;					
				}
				else if (roll.total == 8 && (betIndex = findBet("bet 8", bets)) >= 0) {
					bets.at(betIndex).won = true;					
				}
				else if (roll.total == 9 && (betIndex = findBet("bet 9", bets)) >= 0) {
					bets.at(betIndex).won = true;					
				}
				else if (roll.total == 10 && (betIndex = findBet("bet 10", bets)) >= 0) {
					bets.at(betIndex).won = true;				
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
					if ((betIndex = findBet("Don't Pass Line", bets)) >= 0) {
					cout << "You rolled a 7 before the point again, You Win!" << endl;
						bets.at(betIndex).won = true;
					}
				}
			}
		}
		else {//natural rolled end the round
			cout << "Round Over" << endl;
			roundEnd = false;
		}

		//calculate winnings and display to user		
		user.money += total = calculateWinnings(bets);

		//loop through and show user what they won/lost
		for (int i = 0; i < bets.size(); i++) {

			cout << (bets.at(i).won ? "You won " : "You lost ");
			cout << bets.at(i).name << " for " << bets.at(i).value << endl;// << ", " << bets.at(i).won << endl;
		}
		cout << endl << "Total winnings: " << total << endl;

		//save to file
		updateUserList(user);

		//empty the bet vector
		bets.clear();

	} //end of loop
	
	//cin.ignore();
	//cin.get();
	//return 0;
}
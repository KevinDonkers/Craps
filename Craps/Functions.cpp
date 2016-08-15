//Craps v4
//By Kevin Donkers, Justin Searle, Richard Estrada
//functions.cpp contains all the functions the main will use
//August 15th, 2016

#include "Header.h"

//use the std namespace
using namespace std; 
  
//compete with the computer rolling random dice
Roll RollDice(){
	//vars needed
	int die1;
	int die2;
	int total;

	int const MAX = 6;
	int const MIN = 1;

	//set random seed
	srand(time(NULL));


	//generate user rolls
	die1 = (rand() % (MAX - MIN + 1)) + 1;
	die2 = (rand() % (MAX - MIN + 1)) + 1;
	total = die1 + die2;

	return Roll(die1, die2, total);

} //end of function

//return user that exists as structured.
User checkAccount(string username)
{
	string lineUserName = "", lineName, lineMoney;
	ifstream usersFile;

	string fullname;

	//open file
	usersFile.open("users.txt");

	//check for file and loop through contents
	if (usersFile.is_open()) {
		while (!usersFile.eof()) {
			//get current line values			
			getline(usersFile, lineUserName, ',');
			getline(usersFile, lineName, ',');
			getline(usersFile, lineMoney, '\n');
			
			//check for empty data
			if (!lineUserName.empty()) {
				if (lineUserName == username) {
					return User(username, lineName, stoi(lineMoney));
				}
			}
		} // end of loop 
	}
	//close file		
	usersFile.close();

	cout << "What is your name?";
	while (!(cin >> fullname)) {
		cout << "Bad Input" << endl;
	}

	ofstream outfile;
	outfile.open("users.txt", ios::out | ios::app);
	if (outfile.is_open()) {
		outfile << username << "," << fullname << "," << 500 << "\n";
	}

	return User(username, fullname, 500);

	outfile.close();
}

void updateUserList(User user) {

	ifstream inputFile;
	ofstream outputFile;
	string lineUser, lineName, lineMoney;

	//open temp and user files
	inputFile.open("users.txt");
	outputFile.open("temp.txt");

	if (inputFile.is_open() && outputFile.is_open()) {

		//loop through input file
		while (!inputFile.eof()) {

			//get contents
			getline(inputFile, lineUser, ',');
			getline(inputFile, lineName, ',');
			getline(inputFile, lineMoney, '\n');

			if (!lineUser.empty() && !lineName.empty()) {
				//stuff here
				if (user.username == lineUser) {
					//output user info
					outputFile << user.username << "," << user.fullname << "," << user.money << "\n";
				}
				else {
					//output file info
					outputFile << lineUser << "," << lineName << "," << lineMoney << "\n";
				}
			}
		} //end of loop
	}

	//close file
	inputFile.close();
	outputFile.close();

	//rename old file
	remove("users.txt");
	rename("temp.txt", "users.txt");
}

int calculateWinnings(vector<Bet> bets) {
	int totalWinnings = 0;

	for (int i = 0; i < bets.size(); i++){
		if (bets.at(i).won){
			totalWinnings += bets.at(i).value;
		}
		else {
			totalWinnings -= bets.at(i).value;
		}
	}

	return totalWinnings;

}

int findBet(string betName, vector<Bet> bets){
	for (int i = 0; i < bets.size(); i++) {
		if (bets.at(i).name == betName){
			return i;
		}
	}
	return -1;
}
//Craps v4
//By Kevin Donkers, Justin Searle, Richard Estrada
//functions.cpp contains all the functions the main will use
//August 15th, 2016

#include "Header.h"

//use the std namespace
using namespace std; 
  
//compete with the computer rolling random dice
int RollDice(){
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

	//output rolls
	cout << "\nYou rolled " << total << " (" << die1 << " & " << die2 << ")\n";

	return total;

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
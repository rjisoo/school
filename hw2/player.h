#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


class Player{
public:
	friend class Rps;
	
	Player(){
		//srand (time(NULL)); RNg shouldn't be seeded more than once
		cout << "Please enter a name for this player:" << endl;
		cin >> name;
	}

	std::string guess(){
		uint number; //the way the random is being used, has negative number
		
		number = ((uint)(rand() * 10))%3;

		switch (number){

		case 0:
				return "Rock";

		case 1:
				return "Paper";

		case 2:
				return "Scissors";

		default:
				return "Dynamite";
		}
	}
	
	std::string getName(){
		return name;
	}

	void setName(std::string new_name){
		name = new_name;
	}

	std::string userguess(){
		std::string input;
/*Extra Challenge 1: 
	Get User input for one of the guesses*/
		cout << "Please enter a guess for " << getName() << " (Rock, Paper, or Scissors):" << endl;
		while (1){
			cin >> input;

			if (input.compare("Rock") == 0 ||
				input.compare("Paper") == 0 ||
				input.compare("Scissors") == 0){
				break; //exit loop
			} else {
				cout << "Invalid selection! Try again." << endl;
			}
		}
		return input;
	}
	
/*Extra Challenge 2: 
	Add the Players name to the object and it constructor. Add a function to get the name/change it*/
private:
	std::string name;
};

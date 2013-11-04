/*
 * Name: 	Geoffrey Corey 					Date = 5-18-2012
 * Course: 	ECE-152 						Assignment: C++ Homework1
 * Description: 	Make a 2 question multiple choice interface that validates the
 * 					answer to make sure it's in the answer range and checks for
 * 					correct and incorrect answers.
 *
 */

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <ctype.h>
using namespace std;

std::string question1[5];
std::string question2[5];
std::string ans1 = "B", ans2 = "A";


/*
 * Function: interface
 * Parameters: none
 * Returns: none
 * Description: 	Prints out header files and what the program is going to do.
 */
void interface(void) {
	cout << "Homework 1" << endl << endl;
	cout << "Please answer the following multiple choice questions:" << endl
			<< endl;
}

/*
 * Function: setup
 * Parameters: none
 * Returns: none
 * Description: 	Sets up the question and its answers
 */
void setup(void) {
	question1[0] = "Question 1: 	What is the difference between a duck?";
	question1[1] = "A. 	You accidently the question.";
	question1[2] = "B. 	One leg is both the same.";
	question1[3] = "C. 	... And what?";
	question1[4] = "D. 	I don't even.";

	question2[0] = "Question 2: 	Nice!";
	question2[1] = "A. 	Nice!";
	question2[2] = "B. 	Your \"question\" is not really a question.";
	question2[3] = "C. 	...";
	question2[4] = "D. 	What?";

}

/*
 * Function: print
 * Parameters: none
 * Returns: none
 * Description: 	Prints out the question and possible answers and has a character
 * 					for the prompt.
 */
void print(std::string question[]) {
	for (int i = 0; i < 5; i++) {
		cout << question[i] << endl;
	}
	cout << "> ";
}

int main(void) {

	std::string user; //variable to store user input.

	interface();
	setup();

	//begin question1
	while (1) {
		print(question1); //print the question and choices.
		cin >> user; //get user answer.
		//string compare returns 0 if equal.
		if (!user.compare("A") || !user.compare("a")
			|| !user.compare("B") || !user.compare("b")
			|| !user.compare("C") || !user.compare("c")
			|| !user.compare("D") || !user.compare("d")) { //checks if in range.
			if (!user.compare(ans1)) { //if user input == answer
				// print correct
				cout << "Correct!" << endl << endl;
				break; //exit the loop
			} else {
				//print out correct answer
				cout << "Wrong! The answer is: " << question1[2] << endl << endl;
				break; //exit the loop
			}
		} else {
			//not valid.
			cout << "'" << user << "' is not a valid entry" << endl << endl;
		}
	}

	while (1) {
		print(question2); //print the question and choices.
		cin >> user; //get user answer.
		//string compare returns 0 if equal.
		if (!user.compare("A") || !user.compare("a")
				|| !user.compare("B") || !user.compare("b")
				|| !user.compare("C") || !user.compare("c")
				|| !user.compare("D") || !user.compare("d")) { //checks if in range.
			if (!user.compare(ans2)) { //if user input == answer
				// print correct
				cout << "Correct!" << endl << endl;
				break; //exit the loop
			} else {
				//print out correct answer
				cout << "Wrong! The answer is: " << question2[1] << endl << endl;
				break; //exit the loop
			}
		} else {
			//not valid.
			cout << "'" << user << "' is not a valid entry" << endl << endl;
		}
	}

	cout << "Bye!" << endl;

	return 0;
}

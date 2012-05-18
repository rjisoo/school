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

	std::string answer; //variable to store unser input.

	interface();
	setup();

	//begin question1
	while (1) { //Infinite loop until a criteria is met then breaks.
		print(question1); //print question1 and the choices.
		cin >> answer; //get user guess for answer.

		if (isalpha(answer[0])) { //check to see if the input is an alphabetical character.
			boost::to_upper(answer); //if it is, convert to uppercase.
			if (answer[0] > 'D') { //is answer between a and d?
				cout << "Invalid entry! Tray again!" << endl; //it's not, print error.
			} else {
				if (answer.compare(ans1)) { //it is in range, compare to answer.
					//it's not the answer, print out the answer.
					cout << "Wrong! It's \"One leg is both the same\"" << endl << endl;
					break; //go on to next question.
				} else { //answer is correct.
					cout << "Correct!" << endl;
					break; // go on to next question.
				}
			}
		} else { //the entered answer is not a alphabetical character.
			//echo the input and say it isn't valid.
			cout << "'" << answer << "' is not a valid entry!" << endl;
		}
	}

	//begin question2.
	while (1) { //Infinite loop until a criteria is met then breaks.
		print(question2); //print question1 and the choices.
		cin >> answer; //get user guess for answer.

		if (isalpha(answer[0])) { //check to see if the input is an alphabetical character.
			boost::to_upper(answer); //if it is, convert to uppercase.
			if (answer[0] > 'D') { //is answer between a and d?
				cout << "Invalid entry! Tray again!" << endl; //it's not, print error.
			} else {
				if (answer.compare(ans2)) { //it is in range, compare to answer.
					//it's not the answer, print out the answer.
					cout << "Wrong! It's \"Nice!\"" << endl << endl;
					break; //go on to next question.
				} else { //answer is correct.
					cout << "Correct!" << endl;
					break; //go on to next question.
				}
			}
		} else { //the entered answer is not a alphabetical character.
			//echo the input and say it isn't valid.
			cout << "'" << answer << "' is not a valid entry!" << endl;
		} //begin while loop again.
	}

	return 0;
}

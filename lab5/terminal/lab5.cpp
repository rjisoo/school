// g++ serial.c++ -lboost_system -lws2_32 -D _WIN32_WINNT=0x0501

#include <iostream>
#include "SimpleSerial.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{

	string inputstr;
	cout << "Lab 5 Code Started" << endl;

	/*When you are dealing with IO devices, it is very important that calls to them be wrapped
	 * in 'try-catch' blocks. These blocks of code tell the program 'if something goes
	 * wrong (an exception) run whatever is in catch rather than simply killing the program.
	*/
    try { 

		// Make a SimpleSerial object with the parameter for your Wunderboard/OS
    	SimpleSerial comm("/dev/ttyUSB0", 9600);
		// Start reading data from your wunderboard and displaying it to the screen.
		
		// Check if there is input to be read from the keyboard
		// If there is THEN read it, otherwise ignore the keyboard
		// If you just read data at it is 'EXIT' return from the program
		
    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return 1;
    }
}

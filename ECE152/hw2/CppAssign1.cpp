#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "rps.h"
using namespace std;

int main()
{
	srand (time(NULL)); //rng shouldn't be seeded multiple times.
	Rps game;

	game.newgame();
	return 0;
}

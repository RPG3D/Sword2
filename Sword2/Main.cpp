

#include "Game.h"

#if !defined(ANDROID)
int main(int argc, char* argv[])
#else
int AppMain(int argc)
#endif
{
	Game game;
	return game.run();
}

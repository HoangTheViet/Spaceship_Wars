#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {
	Game run;
	run.home();
	run.gameLoad();
	run.gameLoop();
	run.quit();
	return 0;
}
#ifndef GAME_H
#define GAME_H

#include "vipText.h"
#include "initWindow.h"
#include "Play.h"
class Game {

public:
	Game() {}
	void home();
	void gameLoop();
	void gameLoad();
	void quit();
private:
	SDL_Event e;
	SDL_Renderer* ren = nullptr;
	SDL_Window* window = nullptr;

	int Enemy;
	int Player;
	int type;

	vipText background;
	vipText playButton;
	vipText title;

	StartScreen start;

	Play AI;
	Play User;
};

#endif

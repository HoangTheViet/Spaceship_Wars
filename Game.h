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
	TTF_Font* font = nullptr;
	vector<int> xAxis = { 460, 500, 540, 580, 620, 660, 700, 740, 780, 820, 860 };

	int Enemy;
	int Player;
	int type;
	int current;
	bool first;
	bool previous;

	vipText background;
	vipText playButton;
	vipText title;

	StartScreen start;

	Play User;
};

#endif

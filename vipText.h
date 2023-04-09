#ifndef VIPTEXT_H
#define VIPTEXT_H

#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
#include <set>
#include <cstdlib>
#include <random>
#include <unordered_map>



class vipText {

public:
	
	vipText(){}

	void free();

	void loadFromFile(SDL_Renderer* ren, std:: string path);

	int getWidth();

	int getHeight();

	void render(SDL_Renderer* ren, int x, int y, int posX, int posY, int w, int h);
	void checkLoad();

	void fixed();
	bool drawed();

	void loadTTF(SDL_Renderer* ren, TTF_Font* font, int r, int g, int b,std:: string s);

private:
	SDL_Texture* text = nullptr;
	bool draw = false;
	int width = 0;
	int height = 0;
};


#endif

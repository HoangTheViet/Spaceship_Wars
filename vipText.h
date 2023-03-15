#ifndef VIPTEXT_H
#define VIPTEXT_H

#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
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

private:
	SDL_Texture* text = nullptr;
	int width = 0;
	int height = 0;
};
/*
bool operator < (vipText a, vipText b) {
	return a.getWidth() < b.getHeight();
} */

#endif

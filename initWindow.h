#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "vipText.h"
#include<iostream>

using namespace std;

void logSDLError(ostream& os, const string& msg, bool fatal = false);

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void initIMGvsMixer();

void quitSDL(SDL_Window* &window, SDL_Renderer* &renderer);

class StartScreen {
public:
	void WaitScreen(vipText &background, vipText &playButton, vipText &title, SDL_Renderer* ren);
	void MatrixScreen(vipText& background, SDL_Renderer* ren);
};

#endif
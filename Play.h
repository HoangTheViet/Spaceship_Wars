#pragma once
#ifndef PLAY_H
#define PLAY_H

#include "initWindow.h"

using namespace std;



class Play {
public:

	Play(){}
	int random(int minn, int maxx);
	void createMatrix(int size);
	bool checkAI(int i, int j, int m, int size);
	void mark(int i, int j, int m, int size);
	void matrixForAI(int size);
	
	string checkUsers(vector<int>& v, int size);
	void load(SDL_Renderer* ren);
	void matrixForPlayer(int size, string s, SDL_Renderer* ren, StartScreen& scr, vipText& background, bool& running);// choose ship
	void maker(vipText& h, vector<int>& runner, StartScreen& scr, SDL_Renderer* ren, vipText& background);// mark and render new
	void renderEx(SDL_Renderer* ren);// render sth which was rendered
	void free();
	bool pick(SDL_Renderer* ren, vector<int>& runner, vipText& green, int x, int y);
	void print();
private:
	int a[10][10] = { 0 };

	set<int> s;
	vector<vipText> toRender;// saving the exShip.
	vector<vector<int>> save;// for saving position of both bot and player.
	vector<vector<int>> posToRen;// for renderring.

	vipText green;
	vipText h4;
	vipText v4;
	vipText h3;
	vipText v3;
	vipText h2;
	vipText v2;
	vipText step;
	vipText notice;

};

#endif
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
	bool matrixForPlayer(int size, string s, SDL_Renderer* ren, StartScreen& scr, vipText& background);
	void maker(vipText& h, map<vipText, vector<int>>& m, vector<int>& runner, SDL_Renderer* ren);
	void renderEx(SDL_Renderer* ren);
	void free();

private:
	int a[10][10] = { 0 };

	set<int> s;
	vector<vector<int>> save;
	vector < map<vipText, vector<int>> > position;
	map<vipText, bool> test;

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
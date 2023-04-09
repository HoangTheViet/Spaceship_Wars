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
	void load(SDL_Renderer* &ren, TTF_Font* &font);
	void matrixForPlayer(int size, string s, SDL_Renderer* &ren, StartScreen& scr, vipText& background, bool& running);// choose ship
	void maker(vipText& h, vector<int>& runner, StartScreen& scr, SDL_Renderer* &ren, vipText& background);// mark and render new
	void renderEx(SDL_Renderer* &ren);// render sth which was rendered
	void free();
	bool pick(SDL_Renderer* &ren, vector<int>& runner, vipText& green, int x, int y);

	void renderScore( SDL_Renderer* &ren, TTF_Font* &font, int &scoreY, int &scoreE);
	void begin(SDL_Renderer* &ren, StartScreen &scr, vipText &background);
	
	//effect
	void flyingRocket(SDL_Renderer*& ren, TTF_Font*& font, StartScreen& scr, vipText& background, int x, int y, int& Y, int& E, int& type);// toa do da dc chinh sua thanh toa do chuan giua
	void Miss(SDL_Renderer*& ren, TTF_Font*& font, StartScreen& scr, vipText& background, int x, int y, int& Y, int& E, int& type);
	void Boom(SDL_Renderer* &ren, TTF_Font*& font, StartScreen& scr, vipText& background, int x, int y, int& Y, int& E, int& type);

	//playing
	vector<int> shoot(bool& previous, bool& first);
	void MissOrHit(SDL_Renderer* ren, StartScreen& scr, vipText& background, TTF_Font*& font, int x, int y, int& Y, int& E, int &type, bool& previous, bool& first, int& current); // con can them
	void renderTurn(SDL_Renderer*& ren, TTF_Font*& font, StartScreen& scr, vipText& background, int& Y, int& E, int& type);
	bool legal(int x, int y);
	
	// check to end game
	
private:
	int a1[10][10] = { 0 }; // for AI
	int a2[10][10] = { 0 };// for bot

	int r[4] = {1, -1, 0, 0};
	int c[4] = {0, 0, 1, -1};
	vector<int> move = { 0, 1, 2, 3 };
	stack<vector<int>> hitman;
	int movement;

	set<int> s;
	vector< vipText > toRender;// saving the exShip.
	vector<vector<int>> saveAI;// for saving positions of bot.
	vector<vector<int>> savePlayer;// for saving positions of player.
	vector<vector<int>> posToRen;// for renderring.
	vector<int> toShoot;

	vipText green;
	vipText h4;
	vipText v4;
	vipText h3;
	vipText v3;
	vipText h2;
	vipText v2;
	vipText step;
	vipText notice;
	
	vipText yours;// render "yours:"
	vipText enemy;// render "enemy:"
	vipText scoreY;// render score
	vipText scoreE;// render score
	// the beginning
	vipText one;
	vipText two;
	vipText three;
	vipText START;
	vipText Pturn;//Player's turn
	vipText Aturn; // AI's turn
	// graphic
	vipText rocket;
	vipText boom;
	vipText miss;
	vipText xred;
	vipText red;
	Mix_Chunk* hit;
	Mix_Chunk* fly;
	Mix_Chunk* small;
};

#endif
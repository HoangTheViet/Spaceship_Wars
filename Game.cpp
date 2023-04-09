#include "Game.h"
#include "someConst.h"
#include "initWindow.h"

void Game::home() {
	initSDL(window, ren);
	initIMGvsMixer();
	initTTF(font, "TtfAndMixer/Vdj.ttf");
	Enemy = 6;
	Player = 6;
	type = 0;
	current = 6;
	previous = false;
	first = false;
}


 void Game::gameLoop() {
	 bool down = false;
	 bool running = true;
	 int x = 0;
	 int y = 0;
	 while (running) {
		 bool WaitPlayer = true;

		 while (SDL_PollEvent(&e) != 0) {
			 if (e.key.keysym.sym == SDLK_ESCAPE) {
				 running = false;
			 }
			 if (e.type == SDL_MOUSEBUTTONDOWN) {
				 x = e.button.x;
				 y = e.button.y;
				 if (type > 9 && x > 460 && x < 860 && y > 40 && y < 440) down = true;
			 }
		 }

		 if (type == 0) {
			 start.WaitScreen(background, playButton, title, ren);
			 if ((x >= 325 && x <= 575) && (y >= 523 && y <= 613) && type == 0) {
				 type++;
			 }
		 }
		 
		 else if (type == 1) {
			 start.MatrixScreen(background, ren);
			 playButton.free();
			 title.free();
			 type++;
		 }
		 else if (type == 2) {
			 User.matrixForAI(4);
			 User.load(ren, font);
			 type++;
		 }
		 else if (type == 3) {
			 User.matrixForPlayer(4, "image/pick4.png", ren, start, background, running);
			 type++;
		 }
		 else if (type == 4) {
			 User.matrixForPlayer(4, "image/pick4.png", ren, start, background, running);
			 type++;
		 }
		 else if (type == 5) {
			 User.matrixForPlayer(3, "image/pick3.png", ren, start, background, running);
			 type++;
		 }
		 else if (type == 6) {
			 User.matrixForPlayer(3, "image/pick3.png", ren, start, background, running);
			 type++;
		 }
		 else if (type == 7) {
			 User.matrixForPlayer(2, "image/pick2.png", ren, start, background, running);
			 type++;
		 }
		 else if (type == 8) {
			 User.matrixForPlayer(2, "image/pick2.png", ren, start, background, running);
			 User.free();
			 type++;
		 }
		 else if (type == 9) {
			 User.begin(ren, start, background);
			 User.renderScore(ren, font, Player, Enemy);
			 type++;
		 }
		 else if (type % 2 == 0) {
			 User.renderTurn(ren, font, start, background, Player, Enemy, type);
			 if (down) {
				 y = (int)(y / 40) * 40 + 20;
				 for (int i = 0; i < xAxis.size() - 1; i++) {
					 if (x >= xAxis[i] && x <= xAxis[i + 1]) {
						 x = xAxis[i] + 20;
						 break;
					 }
				 }
				  User.flyingRocket(ren, font, start, background, x, y, Player, Enemy, type);
				  User.MissOrHit(ren, start, background, font, x, y, Player, Enemy, type, previous, first, current);
				  down = false;
				  type++;
			 }
			 SDL_Delay(500);
		 }
		 else if (type % 2 != 0) {
			 User.renderTurn(ren, font, start, background, Player, Enemy, type);
			 vector<int> res = User.shoot(previous, first);
			 User.flyingRocket(ren, font, start, background, res[0], res[1], Player, Enemy, type);
			 User.MissOrHit(ren, start, background, font, res[0], res[1], Player, Enemy, type, previous, first, current);
			 SDL_Delay(500);
			 type++;
		 }
		 SDL_RenderPresent(ren);
	 }
}

 void Game::gameLoad() {
	 background.loadFromFile(ren, "image/background.png");
	 title.loadFromFile(ren, "image/TITLE.png");
	 playButton.loadFromFile(ren, "image/playButton.png");
}

 void Game:: quit() {
	 quitSDL(window, ren, font);
 }

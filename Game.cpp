#include "Game.h"
#include "someConst.h"
#include "initWindow.h"

void Game::home() {
	initSDL(window, ren);
	initIMGvsMixer();
	Enemy = 6;
	Player = 6;
	type = 0;
}


 void Game::gameLoop() {

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
			 AI.matrixForAI(4);
			 User.load(ren);
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
			 type++;
			 User.free();
			 AI.print();
			 User.print();
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
	 quitSDL(window, ren);
 }

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<SDL_mixer.h>

using namespace std;

const int SCREEN_W = 900;
const int SCREEN_H = 800;
SDL_Renderer* ren = nullptr;
SDL_Window* window = nullptr;
Mix_Chunk* chunk = nullptr;

void initSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
	IMG_Init(IMG_INIT_PNG);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 605000) < 0) {
		cout << "Cannot open Audio " << Mix_GetError();
	}
}

void quitSDL() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}


int main(int argc, char* argv[]) {
	initSDL();
	SDL_Texture* bomb = nullptr;
	SDL_Texture* back = nullptr;
	back = IMG_LoadTexture(ren, "background.png");
	bomb = IMG_LoadTexture(ren, "Explo.png");
	if (bomb == nullptr) cout << "Failed to load image " << SDL_GetError();
	chunk = Mix_LoadWAV("newSound.wav");
	if (chunk == nullptr) cout << "Cannot open bomb " << Mix_GetError();

	SDL_Rect boom;
	SDL_Rect pos;
	int w, h;
	SDL_QueryTexture(bomb, nullptr, nullptr, &w, &h);
	//pos.x = SCREEN_W / 2;
	//pos.y = SCREEN_H / 2;
	pos.w = w;
	pos.h = h / 24;

	int frameAdd = h / 24;
	boom.x = 0;
	boom.y = h;
	boom.w = w;
	boom.h = frameAdd;

	SDL_Event e;
	bool running = true;
	bool condition = true;
	int frameTime = 0;
	while (running) {
		condition = true;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) running = false;
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				boom.y = h;
				SDL_GetMouseState(&pos.x, &pos.y);
				Mix_PlayChannel(-1, chunk, 0);
				while (condition) {

					frameTime++;
					if (frameTime == 40) {
						boom.y -= frameAdd;
						frameTime = 0;
						if (boom.y <= 0) {
							condition = false;
						}
					}
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, back, nullptr, nullptr);
					SDL_RenderCopy(ren, bomb, &boom, &pos);
					SDL_RenderPresent(ren);
				}
			}
		}
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, back, nullptr, nullptr);
		SDL_RenderPresent(ren);
		
	}
	quitSDL();
	return 0;
}




	
	
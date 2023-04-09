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

using namespace std;

const int WIDTH = 900;
const int HEIGHT = 700;

SDL_Renderer* ren = nullptr;
SDL_Window* window = nullptr;

void logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
}
void initTTF(TTF_Font*& font, std::string s) {
    font = TTF_OpenFont(s.c_str(), 25);
}

void initIMG_Mixer_TTF() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        logSDLError(std::cout, "InitIMG", true);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 605000) < 0)
    {
        logSDLError(std::cout, "InitMixer", true);
    }
    if (TTF_Init() == -1) {
        logSDLError(std::cout, "InitTTF", true);
    }
}

void renderLine() {
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 0);
    int x1 = 40;
    int y1 = 40;
    int x2 = 40;
    int y2 = 440;
    for (int i = 0; i < 11; i++) {
        SDL_RenderDrawLine(ren, x1, y1, x2, y2);
        x1 += 40;
        x2 += 40;
    }
    x1 = 40;
    y1 = 40;
    x2 = 440;
    y2 = 40;
    for (int i = 0; i < 11; i++) {
        SDL_RenderDrawLine(ren, x1, y1, x2, y2);
        y1 += 40;
        y2 += 40;
    }
    x1 = 460;
    y1 = 40;
    x2 = 860;
    y2 = 40;
    for (int i = 0; i < 11; i++) {
        SDL_RenderDrawLine(ren, x1, y1, x2, y2);
        y1 += 40;
        y2 += 40;
    }
    x1 = 460;
    y1 = 40;
    x2 = 460;
    y2 = 440;
    for (int i = 0; i < 11; i++) {
        SDL_RenderDrawLine(ren, x1, y1, x2, y2);
        x1 += 40;
        x2 += 40;
    }
}

void render(SDL_Texture* text, SDL_Renderer* ren, int x, int y, int posX, int posY, int w, int h) {
    SDL_Rect area = { posX, posY, w, h };
    SDL_Rect take = { x, y, w, h };
    SDL_RenderCopy(ren, text, &take , &area);
}

int main(int argv, char* argc[]) {
    initSDL(window, ren);
    initIMG_Mixer_TTF();

    SDL_Texture* background = IMG_LoadTexture(ren, "image/background.png");
    SDL_Texture* boom = IMG_LoadTexture(ren, "image/Explo.png");
    if (background == nullptr) {
        cout << "Cannot load background" << SDL_GetError();
    }
    if (boom == nullptr) {
        cout << "Cannot load boom" << SDL_GetError();
    }

    int w, h;
    SDL_QueryTexture(boom, nullptr, nullptr, &w, &h);
    int increase = h / 24;
    int start = h - increase;
    int x = 0;
    int y = 0;
    bool down = false;
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&x, &y);
                down = true;
            }
        }
        
            while (down) {
                SDL_RenderCopy(ren, background, nullptr, nullptr);
                renderLine();
                render(boom, ren, 0, start, x, y, w, increase);
                SDL_RenderPresent(ren);
                start -= increase;
                SDL_Delay(60);
                if (start < 0) {
                    SDL_RenderCopy(ren, background, nullptr, nullptr);
                    renderLine();
                    SDL_RenderPresent(ren);
                    down = false;
                    start = h - increase;
                }
        }
    }
    
    return 0;
}





/* while (posY > 40) {
           // while (count--) {
             //   SDL_RenderCopy(ren, text, nullptr, nullptr);
              //  renderLine();
              //  render(rocket, ren, x, y, posX, posY, width, increase);
                SDL_RenderPresent(ren);
                posY -= 8;
                SDL_Delay(30);
            }
            count = 10;
            y -= increase;
            if (y < 0) {
                y = height - increase;
            }
            SDL_Delay(20);
        }*/







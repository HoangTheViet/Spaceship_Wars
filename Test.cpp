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

void initIMGvsMixer() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        logSDLError(std::cout, "InitIMG", true);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 605000) < 0)
    {
        logSDLError(std::cout, "InitMixer", true);
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


int main(int argv, char* argc[]) {
    initSDL(window, ren);
    initIMGvsMixer();

    SDL_Texture* green = IMG_LoadTexture(ren, "Green.png");
    if (green == nullptr) cout << "cannot load" << SDL_GetError();
    SDL_Texture* background = IMG_LoadTexture(ren, "background.png");
    SDL_Texture* step = IMG_LoadTexture(ren, "pick4.png");
    SDL_Texture* notice = IMG_LoadTexture(ren, "notice.png");
    SDL_Texture* spaceShip = IMG_LoadTexture(ren, "SpaceShip4x.png");


    bool running = true;
    SDL_Event e;
    int x = 0; int y = 0;
    SDL_Event k;
    bool run = true;
    bool check = true;
    vector<int> save;

    while (running) {

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDLK_ESCAPE) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&x, &y);
            }
        }
        SDL_RenderCopy(ren, background, nullptr, nullptr);
        renderLine();
       
        while (run) {
            while (SDL_PollEvent(&k) != 0) {
                if (k.type == SDL_MOUSEBUTTONDOWN) SDL_GetMouseState(&x, &y);
            }
            if (check == false) {
                SDL_RenderCopy(ren, background, nullptr, nullptr);
                renderLine();
                check = true;
            }
            if ((x >= 40 && x <= 440) && (y >= 40 && y <= 440)) {
                int lead = x / 40;
                int trail = y / 40;
                SDL_Rect area;
                int w, h;
                SDL_QueryTexture(green, nullptr, nullptr, &w, &h);
                area = { lead * 40, trail * 40, w, h };
                SDL_RenderCopy(ren, green, nullptr, &area);
                int b = lead * 10 + trail;
                int count = 0;
                for (int i = 0; i < save.size(); i++) {
                    if (save[i] == b) count++;
                }
                if (count == 0) save.push_back(b);
            }
            else {
                check = false;
            }
            if (save.size() == 4) {
                SDL_RenderCopy(ren, background, nullptr, nullptr);
                renderLine();
                sort(save.begin(), save.end());
                int l = save[0] / 10;
                int t = save[0] % 10;
                SDL_Rect are;
                are.x = l * 40;
                are.y = t * 40;
                int wi, he;
                SDL_QueryTexture(spaceShip, nullptr, nullptr, &wi, &he);
                are.w = wi;
                are.h = he;
                SDL_RenderCopy(ren, spaceShip, nullptr, &are);
                save.clear();
               
            }
            SDL_RenderPresent(ren);
        }
    }
    return 0;
}
/*
while (run) {
    // event
    while (SDL_PollEvent(&k) != 0) {
        if (k.type == SDL_QUIT) run = false;
        if (k.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&dx, &dy);
        }
    }
    //do
    if ((dx >= 40 && dx <= 440) && (dy >= 40 && dy <= 440)) {
        int l = dx / 40;
        int t = dy / 40;
        int count = 0;
        for (int i = 0; i < runner.size(); i++) {
            if (runner[i] == l * 10 + t) count++;
        }
        if (count == 0) {
            if (a[l - 1][t - 1] == 0) {
                runner.push_back(l * 10 + t);
                green.render(ren, 0, 0, l * 40, t * 40, green.getWidth(), green.getHeight());
                SDL_RenderPresent(ren);
            }
            else {
                continue;
            }
        }
    }
    else if (dy >= 540 && dy <= 590) {
        if (dx >= 370 && dx <= 450) {
            scr.MatrixScreen(background, ren);
            step.render(ren, 0, 0, 295, 460, step.getWidth(), step.getHeight());
        }
        else if (dx > 450 && dx <= 530) {
            if (checkUsers(runner, size)) {
                scr.MatrixScreen(background, ren);
                int left = runner[0] / 10;
                int right = runner[0] % 10;
                spaceship4x.render(ren, 0, 0, left * 40, right * 40, spaceship4x.getWidth(), spaceship4x.getHeight());
                //mark
                run = false;
            }
            else {
                scr.MatrixScreen(background, ren);
                notice.render(ren, 0, 0, 295, 460, step.getWidth(), step.getHeight());

            }
        }
    }
    SDL_RenderPresent(ren);
*/
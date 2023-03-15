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
       
       
            SDL_RenderPresent(ren);
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


/*
SDL_Event k;
bool run = true;
int dx = 0; int dy = 0;
vector<int> runner;
map<vipText, vector<int>> m;
bool check = true;
while (run) {
    //event
    while (SDL_PollEvent(&k) != 0) {
        if (k.type == SDL_QUIT) run = false;
        if (k.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&dx, &dy);
        }
    }
    // do
    if ((dx >= 40 && dx <= 440) && (dy >= 40 && dy <= 440) && check == true) {
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
    else if ((dy >= 540 && dy <= 590) && check == true) {
        if (dx >= 370 && dx <= 450) {
            scr.MatrixScreen(background, ren);
            step.render(ren, 0, 0, 295, 460, step.getWidth(), step.getHeight());
            renderEx(ren);
        }
        else if (dx > 450 && dx <= 530) {
            string str = checkUsers(runner, size);
            if (str == "wrong") {
                runner.clear();
                check = false;
                scr.MatrixScreen(background, ren);
                renderEx(ren);
                notice.render(ren, 0, 0, 295, 460, notice.getWidth(), notice.getHeight());
            }
            else if (str == "h4") {
                maker(h4, m, runner, ren);
                return true;
            }
            else if (str == "v4") {
                maker(v4, m, runner, ren);
                return true;
            }
            else if (str == "h3") {
                maker(h3, m, runner, ren);
                return true;
            }
            else if (str == "v3") {
                maker(v3, m, runner, ren);
                return true;
            }
            else if (str == "h2") {
                maker(h2, m, runner, ren);
                return true;
            }
            else if (str == "v2") {
                maker(v2, m, runner, ren);
                return true;
            }
        }// con thieu buoc mark ma tran
    }
    else if (dy >= 580 && dy <= 620 && check == false) {
        if (dx >= 450 && dx <= 530) {
            return false;
        }
        else if (dx >= 370 && dx <= 450) {
            check = true;
            scr.MatrixScreen(background, ren);
            step.render(ren, 0, 0, 295, 460, step.getWidth(), step.getHeight());
            renderEx(ren);
        }
    }
    SDL_RenderPresent(ren);

}
}

string Play::checkUsers(vector<int>& v, int size) {
    if (v.size() != size) return "wrong";

    sort(v.begin(), v.end());
    int countV = 0;
    int countH = 0;

    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i + 1] - v[i] == 10) countV++;
        if (v[i + 1] - v[i] == 1) countH++;
    }

    if (size == 4) {
        if (countV == v.size() - 1) {
            return "v4";
        }
        else if (countH == v.size() - 1) {
            return "h4";
        }
    }
    else if (size == 3) {
        if (countV == v.size() - 1) {
            return "v3";
        }
        else if (countH == v.size() - 1) {
            return "h3";
        }
    }
    else if (size == 2) {
        if (countV == v.size() - 1) {
            return "v2";
        }
        else if (countH == v.size() - 1) {
            return "h2";
        }
    }
    return "wrong";
}

void Play::renderEx(SDL_Renderer* ren) {
    for (int i = 0; i < position.size(); i++) {
        for (auto x : position[i]) {
            vipText tmp = x.first;
            vector<int> vi = x.second;
            tmp.render(ren, 0, 0, vi[0], vi[1], tmp.getWidth(), tmp.getHeight());
            tmp.free();
        }
    }
}

void Play::maker(vipText& h, map<vipText, vector<int>>& m, vector<int>& runner, SDL_Renderer* ren) {
    test[h] = true;
    vector<int> r;
    int l = runner[0] / 10;
    int t = runner[0] % 10;

    h.render(ren, 0, 0, l * 40, t * 40, h4.getHeight(), h4.getWidth());
    r.push_back(l * 40);
    r.push_back(t * 40);
    m[h] = r;
    position.push_back(m);
}
*/
#include "initWindow.h"
#include "someConst.h"
using namespace std;

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

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_RenderSetLogicalSize(renderer, SCREEN_W, SCREEN_H);
}

void initIMGvsMixer() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        logSDLError(std::cout, "InitIMG", true);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1000000) < 0)
    {
        logSDLError(std::cout, "InitMixer", true);
    }      
}

void initTTF(TTF_Font* &font, std::string s) {
    if (TTF_Init() == -1) {
        logSDLError(std::cout, "InitTTF", true);
    }
    else {
        font = TTF_OpenFont(s.c_str(), 28);
        if (font == nullptr) {
            logSDLError(std::cout, "Cannot load the font ", true);
        }
    }
}

void StartScreen::WaitScreen(vipText& background, vipText& playButton, vipText& title, SDL_Renderer* ren) {
    background.render(ren, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    title.render(ren, 0, 0, 250, 0, title.getWidth(), title.getHeight());
    playButton.render(ren, 0, 0, 325, 523, playButton.getWidth(), playButton.getHeight());
}

void StartScreen::MatrixScreen(vipText& background, SDL_Renderer* ren) {
    background.render(ren, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 0);
    int x1 = 40;
    int y1 = 40;
    int x2 = 40;
    int y2 = 440;
    for(int i = 0; i < 11; i++) {
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

void quitSDL(SDL_Window* &window, SDL_Renderer* &ren, TTF_Font* &font) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}
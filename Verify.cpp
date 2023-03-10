#include <iostream>
#include<string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "PHONG NGUYEN";

void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal)
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
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);



    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}




void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    int frameW, frameH;
    int textureW, textureH;

    SDL_Texture* character = loadTexture("nezuko running to right.png", renderer);
    SDL_Rect charRect;
    SDL_Rect charPos;

    charPos.w = 300;
    charPos.h = 300;
    charPos.x = 0;
    charPos.y = SCREEN_HEIGHT / 2;

    int frameTime = 0;

    SDL_QueryTexture(character, NULL, NULL, &textureW, &textureH);
    frameW = textureW / 4;
    frameH = textureH;
    charRect.x = charRect.y = 0;
    charRect.w = frameW;
    charRect.h = frameH;

    SDL_Texture* background = loadTexture("map.png", renderer);

    SDL_Event e;
    bool gameRunning = true;
    while (gameRunning) {
        frameTime++;
        if (frameTime == 15) {
            frameTime = 0;
            charRect.x += frameW;
            if (charRect.x >= textureW) {
                charRect.x = 0;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, character, &charRect, &charPos);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {
                gameRunning = false;
                break;
            }
        }
        charPos.x += 3;
        SDL_Delay(10);
    }

    quitSDL(window, renderer);
    return 0;
}
#include "vipText.h"

using namespace std;


void vipText::free() {
	if (text != nullptr) {
		SDL_DestroyTexture(text);
		width = 0;
		height = 0;
		text = nullptr;
	}
}

void vipText::loadFromFile(SDL_Renderer* ren, std:: string path) {
	text = IMG_LoadTexture(ren, path.c_str());
	if (text == nullptr) {
		std::cout << "The text cannot be loaded " << SDL_GetError();
	}
	SDL_QueryTexture(text, nullptr, nullptr, &width, &height);
}

void vipText::render(SDL_Renderer* ren, int x, int y, int posX, int posY, int w, int h) {
	SDL_Rect area = { x, y, w, h };
	SDL_Rect target = { posX, posY, w, h };
	SDL_RenderCopy(ren, text, &area, &target);
}

int vipText:: getWidth() {
	return width;
}

int vipText::getHeight() {
	return height;
}

void vipText::checkLoad() {
	if (text == nullptr) {
		cout << "cannot load image " << SDL_GetError();
	}
}


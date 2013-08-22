#include <iostream>
#include <string>
#include <stdexcept>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
	
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

SDL_Texture* LoadImage(std::string file){
	SDL_Texture *texture = nullptr;
	
	texture = IMG_LoadTexture(renderer, file.c_str());
	if(texture == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
	return texture;
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend){
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	
	SDL_RenderCopy(rend, tex, NULL, &pos);
}


int main(int argc, char** argv){
	if(SDL_Init(SDL_INIT_EVERYTHING == -1)){
		std::cout << SDL_GetError() << std::endl;
		return 1;	
	}

	window = SDL_CreateWindow("Tutorial 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 2;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 3;
	}	

	SDL_Texture *image = nullptr;
	try {
		image = LoadImage("res/image4.png");
	}
	catch(const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		return 4;
	}

	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	SDL_Event e;
	
	// Main loop
	bool quit = false;
	while(!quit){
		
		// Event polling
		while(SDL_PollEvent(&e)){
			// if user closes the window
			if(e.type == SDL_QUIT)
				quit = true;
			// if user presses any key
			if(e.type == SDL_KEYDOWN)
				quit = true;	
			// if user clicks the mouse
			if(e.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
		}

		// Rendering
		SDL_RenderClear(renderer);
		// Draw the image
		ApplySurface(x, y, image, renderer);		
		
		// Update the screen
		SDL_RenderPresent(renderer);
	}	

	SDL_DestroyTexture(image);	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
	return 0;
}

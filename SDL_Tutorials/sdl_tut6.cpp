#include <iostream>
#include <string>
#include <stdexcept>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

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

SDL_Texture* RenderText(std::string message, std::string fontFile, SDL_Color color, int fontSize)
{
	//Open Font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if(font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	// Render the msg to an SDL_Surface, as that's what TT_RenderText_X returns
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	
	return texture;
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect *clip = NULL){
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	//Detect if we should use clip width settings or texture width
	if(clip != NULL){
		pos.w = clip->w;
		pos.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	}
	SDL_RenderCopy(rend, tex, clip, &pos);
}


int main(int argc, char** argv){
	if(SDL_Init(SDL_INIT_EVERYTHING == -1)){
		std::cout << SDL_GetError() << std::endl;
		return 1;	
	}
	
	if(TTF_Init() == -1){
		std::cout << TTF_GetError() << std::endl;
		return 2;
	}

	window = SDL_CreateWindow("SDL Tuts", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 3;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 4;
	}	

	SDL_Texture *image = nullptr;
	try {
		SDL_Color color = {255, 255, 255};
		image = RenderText("TTF fonts are cool!", "res/fonts/SourceSansPro_FontsOnly-1.050/TTF/SourceSansPro-Regular.ttf", color, 64);
	}
	catch(const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		return 5;
	}
	
	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT /2 - iH / 2;

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
			{
				switch(e.key.keysym.sym){
					case SDLK_1:
						break;
					case SDLK_2:
						break;
					case SDLK_3:
						break;
					case SDLK_4:
						break;
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}

			}
			// if user clicks the mouse
			if(e.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
		}

		// Rendering
		SDL_RenderClear(renderer);
		// Draw the image
		ApplySurface(x, y, image, renderer, NULL);		
		
		// Update the screen
		SDL_RenderPresent(renderer);
	}	

	SDL_DestroyTexture(image);	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
	return 0;
}

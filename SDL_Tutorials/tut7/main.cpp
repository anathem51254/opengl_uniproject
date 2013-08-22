#include <stdexcept>
#include <string>
#include <iostream>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include "SDL2/SDL.h"
#endif

#include "window.h"

int main(int arc, char** argv){
	// Start our window
	try {
		Window::Init("Lesson 7");	
	}
	catch(const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}

	// Load up an image and some text
	SDL_Texture *img, *msg;
	try {
		// Load the image
		std::string imgFile = "../res/img/image.png";
		img = Window::LoadImage(imgFile);
		// Load the font and message
		std::string fontFile = "../res/fonts/SourceSansPro_FontsOnly-1.050/TTF/SourceSansPro-Regular.ttf";	
		std::string text = "TTF fonts too!";
		SDL_Color color = { 255, 255, 255 };
		msg = Window::RenderText(text, fontFile, color, 25);
	}
	catch(const std::runtime_error &e){
		// Catch error and crash
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}
	
	// Set a position to draw it with
	SDL_Rect pos = { Window::Box().w / 2 - 150 / 2, Window::Box().h / 2 - 150 / 2, 150, 150 };
	// The angle to draw at, so we can play with it
	int angle = 0;
	
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
					// Rotating image
					case SDLK_d:
						angle += 2;
						break;
					case SDLK_a:
						angle -= 2;
						break;
                                        case SDLK_ESCAPE:
                                        	quit = true;
                                        	break;
                                        default:
                                        	break;
				}
                        }
                }
		
		// Rendering
		Window::Clear();
		
		Window::Draw(img, pos, NULL, angle);
		Window::Draw(msg, pos, NULL, angle, 0, 0, SDL_FLIP_VERTICAL);

		Window::Present();	
	}
	
	SDL_DestroyTexture(img);
	SDL_DestroyTexture(msg);
	
	Window::Quit();
	return 0;
}

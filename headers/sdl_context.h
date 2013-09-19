
#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT__H

#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"


class SDL_CONTEXT 
{

	public:
		
		SDL_CONTEXT ();

		~SDL_CONTEXT ();

		enum		WindowEvents { 
						NOEVENT, 
						ESC, 
						ONE, 
						TWO 
					     }; 

		SDL_Window* 	CreateSDLWindow(std::string title, int WINDOW_HEIGHT, int WINDOW_WIDTH);		
		
		SDL_GLContext	CreateGLContext(SDL_Window* SDLWindow);

		void 		ClearWindow(SDL_Window* SDLWindow);
		
		WindowEvents 	ProcessEvent();

		void 		Quit();	
};

#endif

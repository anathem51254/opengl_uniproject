
#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H

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
						TWO,
						FIVE,
						SIX,
						SEVEN,
						EIGHT,
						MOUSE,
						W,
						S,
						A,
						D,
						Q,
						E,
						RIGHT,
						LEFT
					     }; 

		SDL_Event SDLEvent;

		SDL_Window* 	CreateSDLWindow(std::string title, int WINDOW_HEIGHT, int WINDOW_WIDTH);		
		
		SDL_GLContext	CreateGLContext(SDL_Window* SDLWindow);

		void 		ClearWindow(SDL_Window* SDLWindow);
		
		WindowEvents 	ProcessEvent();

		unsigned int	GetTime();

		void		CenterMouse(SDL_Window* SDLWindow, int width, int height);

		float		GetMouseRelX();
		float		GetMouseRelY();
	
	private:

};

#endif

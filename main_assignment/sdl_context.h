#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H

#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"

/**
 * SDL Context class
 *
 */

class SDL_CONTEXT {
	public:
		static SDL_GLContext mglContext;
		
		static SDL_GLContext Init( std::string title, int WINDOW_HEIGHT, int WINDOW_WIDTH );		
		static  ProcessInput();

		static void Quit();	

	private:
		static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow;
		//static std::unique_ptr<SDL_GLContext, void (*)(SDL_GLContext)> mglContext;
		static SDL_Rect mBox;
		static SDL_Event windowEvent;
};

#endif

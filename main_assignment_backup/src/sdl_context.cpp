
#include "../sdl_context.h"


SDL_CONTEXT::SDL_CONTEXT()
{

}

SDL_CONTEXT::~SDL_CONTEXT()
{

}

SDL_Window* SDL_CONTEXT::CreateSDLWindow(std::string title, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		throw std::runtime_error("[DEBUG] SDL Init Failed");

	SDL_Window* SDLWindow = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL );

	if( SDLWindow == nullptr )
		throw std::runtime_error("[DEBUG] Failed to Create Window");

	return SDLWindow;
}

SDL_GLContext SDL_CONTEXT::CreateGLContext(SDL_Window* SDLWindow)
{
	SDL_GLContext GLContext = SDL_GL_CreateContext(SDLWindow);	
	if( GLContext == 0 || GLContext < 0)
	{
		std::cout << "[DEBUG] GLContext Error: " << SDL_GetError() << std::endl;
		std::cout << "[DEBUG] GLContext: " << GLContext << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	return GLContext;
}

void SDL_CONTEXT::ClearWindow(SDL_Window* SDLWindow)
{
	SDL_GL_SwapWindow(SDLWindow);
}

int SDL_CONTEXT::ProcessEvent()
{	
		int winEvent = 0;
	
		SDL_Event sdl_Event;

		if( SDL_PollEvent(&sdl_Event) )
		{
				if( sdl_Event.type == SDL_QUIT )
				{
					winEvent = 1;
				}
				else if ( sdl_Event.type == SDL_KEYUP && sdl_Event.key.keysym.sym == SDLK_ESCAPE )
				{
					winEvent = 1;
				}
				else
					winEvent = 0;
		}
		
		return winEvent;
}

void SDL_CONTEXT::Quit()
{
	SDL_Quit();
}

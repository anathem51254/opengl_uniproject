
#include "../headers/sdl_context.h"


SDL_CONTEXT::SDL_CONTEXT()
{

}

SDL_CONTEXT::~SDL_CONTEXT()
{
	SDL_Quit();
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

SDL_CONTEXT::WindowEvents SDL_CONTEXT::ProcessEvent()
{	
		WindowEvents winEvent = NOEVENT;
	
		SDL_Event sdl_Event;

		if(SDL_PollEvent(&sdl_Event))
		{
				if(sdl_Event.type == SDL_QUIT)
				{
					winEvent = ESC;
				}
				else if (sdl_Event.type == SDL_KEYUP && sdl_Event.key.keysym.sym == SDLK_ESCAPE)
				{
					winEvent = ESC;
				}
				else if( sdl_Event.type == SDL_KEYUP && sdl_Event.key.keysym.sym == SDLK_1)
				{
					winEvent = ONE;
				}
				else if( sdl_Event.type == SDL_KEYUP && sdl_Event.key.keysym.sym == SDLK_2)
				{
					winEvent = TWO;
				}
				else if( sdl_Event.type == SDL_KEYUP && sdl_Event.key.keysym.sym == SDLK_5)
				{
					winEvent = FIVE;
				}
				else if(sdl_Event.key.keysym.sym == SDLK_a)
				{
					winEvent = A;
				}
				else if(sdl_Event.key.keysym.sym == SDLK_d)
				{
					winEvent = D;
				}
				else
					winEvent = NOEVENT;
		}
		
		return winEvent;
}


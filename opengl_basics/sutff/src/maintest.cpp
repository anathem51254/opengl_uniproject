#include <stdexcept>
#include <string>
#include <iostream>

#include "SDL2/SDL.h"

#include "../sdl_context.h"
//#include "gl_core.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
	try
	{
		SDL_Context::Init("Test", WINDOW_WIDTH, WINDOW_HEIGHT );
	}
	catch( const std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		SDL_Context::Quit();
		return -1;
	}
	
	SDL_Event windowEvent;
	while( true )
	{
			
		//while((err = glGetError()) != GL_NO_ERROR)
		//	std::cout << "[DEBUG] OpenGL Error in MainLoop: " << err << std::endl;
	
		if( SDL_PollEvent( &windowEvent ) )
		{
			if ( windowEvent.type == SDL_QUIT ) break;
			if ( windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE ) break;
		}

		//SDL_GL_SwapWindow(window);
	}
	
	//CleanUp();		

	SDL_Context::Quit();
	return 0;
}

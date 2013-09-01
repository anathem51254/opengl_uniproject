
#include "../core.h"

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;

CORE::WindowEvents = { ESC, ONE, TWO, NOEVENT };

int CORE::InitSDL()
{
	try
	{
		SDL_CONTEXT::mglContext = SDL_CONTEXT::Init( "Test", WINDOW_WIDTH, WINDOW_HEIGHT );
	}
	catch( const std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		SDL_CONTEXT::Quit();
		return -1;
	}

	return 0;
}


void CORE::Initialise()
{
	InitSDL();
	//InitGL();
}



void CORE::CleanUp()
{
	//GL_CORE::CleanUp();		

	SDL_CONTEXT::Quit();
}

int CORE::MainLoop()
{
	CORE::WindowEvents winEvent = NOEVENT;
	while( true )
	{
			
		//while((err = glGetError()) != GL_NO_ERROR)
		//	std::cout << "[DEBUG] OpenGL Error in MainLoop: " << err << std::endl;
		
		winEvent = SDL_CONTEXT::ProcessInput();	
		

		//SDL_GL_SwapWindow(window);
	}
	return 0;
}

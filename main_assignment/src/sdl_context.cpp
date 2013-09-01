
#include "../core.h"
#include "../sdl_context.h"


std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> SDL_CONTEXT::mWindow = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);

/*std::unique_ptr<SDL_GLContext, void (*)(SDL_GLContext)> SDL_Context::mglContext = std::unique_ptr<SDL_GLContext, void (*)(SDL_GLContext)>(nullptr, SDL_GL_DeleteContext);
*/

SDL_Rect SDL_CONTEXT::mBox;

SDL_Event SDL_CONTEXT::windowEvent;


SDL_GLContext SDL_CONTEXT::Init( std::string title, int WINDOW_WIDTH, int WINDOW_HEIGHT )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		throw std::runtime_error("[DEBUG] SDL Init Failed");

	mBox.x = 0;
	mBox.y = 0;
	mBox.w = WINDOW_WIDTH;
	mBox.h = WINDOW_HEIGHT;

	mWindow.reset( SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mBox.w, mBox.h, SDL_WINDOW_SHOWN ) );

	if( mWindow == nullptr )
		throw std::runtime_error("[DEBUG] Failed to Create Window");

	
	return SDL_CONTEXT::mglContext = SDL_GL_CreateContext(mWindow.get());	
}

CORE::WindowEvent SDL_CONTEXT::ProcessInput()
{
		CORE::WindowEvent winEvent = NOEVENT;
		
		if( SDL_PollEvent( &SDL_CONTEXT::windowEvent ) )
		{
			switch(SDL::windowEvent.type)
			{
				case SDL_QUIT:
					winEvent = ESC;
					break;
				case ( SDL_CONTEXT::windowEvent.type 	       == SDL_KEYUP && 
				       SDL_CONTEXT::windowEvent.key.keysym.sym == SDLK_ESCAPE 
				     ):
					winEvent = ESC;
					break;
				default:
					winEvent = NOEVENT;
			}
		}
		
		return winEvent;
}

void SDL_CONTEXT::Quit()
{
	SDL_Quit();
}

#include <string>
#include <stdexcept>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"

#include "../sdl_context.h"


std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> SDL_Context::mWindow = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);

/*std::unique_ptr<SDL_GLContext, void (*)(SDL_GLContext)> SDL_Context::mglContext = std::unique_ptr<SDL_GLContext, void (*)(SDL_GLContext)>(nullptr, SDL_GL_DeleteContext);
*/

SDL_GLContext SDL_Context::mglContext; 

SDL_Rect SDL_Context::mBox;


void SDL_Context::Init( std::string title, int WINDOW_WIDTH, int WINDOW_HEIGHT )
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

	
	SDL_Context::mglContext = SDL_GL_CreateContext(mWindow.get());	
}

void SDL_Context::Quit()
{
	SDL_Quit();
}

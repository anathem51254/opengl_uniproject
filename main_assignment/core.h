#ifndef CORE_H
#define CORE_H

#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "SOIL/SOIL.h"

#include "gl_core.h"
#include "sdl_context.h"

class CORE 
{
	public:
		
		static enum 	WindowEvents; 
						
		static void 	Start();	
		
		static void 	Initialise();
		
		static int 	InitSDL();	
		
		static int 	MainLoop();
		
		static void 	CleanUp();
	
	private:		


};

#endif

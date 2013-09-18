#ifndef UTILS_H
#define UTILS_H

#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include <GL/glew.h>
#include <GL/gl.h>

//#include "SDL2/SDL.h"

class UTILS
{
	public:
		
		UTILS ();
		~UTILS ();

		void CheckErrors(std::string FunctionName);

	private:

};


#endif

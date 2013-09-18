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

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"

#include "utils.h"
#include "sdl_context.h"

class CORE 
{
	public:
		
		CORE ();
		~CORE ();

		SDL_GLContext GLContext;

		SDL_Window *SDLWindow;

		enum		WindowEvents { 
						NOEVENT, 
						ESC, 
						ONE, 
						TWO 
					     }; 

		void    	Start();	
	
	private:		

		void	    	Initialise();
		
		int	    	InitSDL();	

		int		InitGL();

		WindowEvents 	ProcessEvent();
		
		int	    	MainLoop();

		void		SetDefaultCamera();

		void		MoveCameraLeft();

		void		MoveCameraRight();
		
		void		InitScene();

		void	    	DisplayScene();
		
		void	    	CleanUp();

		int		DebugShaderProgram(GLuint ShaderProgram, GLint status);

		GLuint 		CreateShader( const std::string &shaderSource, GLenum eShaderType ); 

		void 		InitBuffers();

		int		InitGenericShaders();

		void 		gl_LoadTexture( std::string file, unsigned int texNum );

};

#endif

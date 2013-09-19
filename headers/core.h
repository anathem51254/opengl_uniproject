#ifndef CORE_H
#define CORE_H

#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>

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
#include "shaderprogram.h"

class CORE 
{
	public:
		
		CORE ();
		~CORE ();

		UTILS *utils;
		SDL_CONTEXT *sdl_context;

		SHADER_PROGRAM *generic_shader;

		SDL_GLContext GLContext;

		SDL_Window *SDLWindow;

		unsigned int WINDOW_WIDTH;
		unsigned int WINDOW_HEIGHT;

		float FOV;	
		float NearPlane;
		float FarPlane;

		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;

		enum		WindowEvents { 
						NOEVENT, 
						ESC, 
						ONE, 
						TWO,
						FIVE,
						A,
						D
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

		glm::mat4	TranslateModelMatrix(glm::mat4 temp_ModelMatrix, glm::vec3 const vec);
		
		glm::mat4	ScaleModelMatrix(glm::mat4 temp_ModelMatrix, glm::vec3 const vec);

		glm::mat4	RotateModelMatrix(glm::mat4 temp_ModelMatrix, const float angle, glm::vec3 const vec);

		glm::mat4	PushModelMatrix(glm::mat4 temp_ModelMatrix);

		glm::mat4 	PopModelMatrix(glm::mat4 temp_ModelMatrix);
		
		void		InitScene();

		void	    	DisplayScene();
		
		void	    	CleanUp();

		void 		InitBuffers();

		void 		gl_LoadTexture(std::string file, unsigned int texNum);

};

#endif

#ifndef CORE_H
#define CORE_H

#include <stdexcept>
#include <memory>

#include <string>
#include <stack>

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

#include "bridgescene.h"
#include "utils.h"
#include "camera.h"
#include "sdl_context.h"
#include "shaderprogram.h"
#include "objects.h"

using namespace std;

class CORE 
{
	public:
		
		CORE ();
		~CORE ();

		SDL_CONTEXT *sdl_context;

		UTILS *utils;
		CAMERA *camera;

		SHADER_PROGRAM *generic_shader;

		OBJECTS *objects;

		SDL_GLContext GLContext;

		SDL_Window *SDLWindow;


		float 	WINDOW_WIDTH;
		float 	WINDOW_HEIGHT;

		float 	FOV;	
		float 	NearPlane;
		float 	FarPlane;

		struct 	CameraMatrix;

		float 	CameraAngle = 0.0f;

		enum	WindowEvents 
		{ 
			NOEVENT, 
			ESC, 
			ONE, 
			TWO,
			FIVE,
			SIX,
			SEVEN,
			EIGHT,
			MOUSE,
			W,
			S,
			A,
			D,						
			Q,
			E,
			RIGHT,
			LEFT
		}; 

		enum 	Scenes
		{
			TEST,
			BRIDGE
		};

		Scenes Scene;

		WindowEvents Event;
		WindowEvents CameraEvent;

		void    Start();	
	
	private:		

		void   	Initialise();
		
		int    	InitSDL();	

		int	InitGL();

		void	ProcessEvent();

		void	ProcessCameraEvent();
		
		int    	MainLoop();

		void	TranslateModelMatrix(glm::vec3 const vec);
		
		void	ScaleModelMatrix(glm::vec3 const vec);

		void	RotateModelMatrix(const float angle, glm::vec3 const vec);
		
		void	DrawFloor();
		void	DrawRails();
		void	DrawBeams();
		void	DrawUnderBeams();
		void	DrawLegs();
		void	DrawLegSupport();
		void	DrawGateOne();
		void	DrawGateTwo();

		void 	DrawLampPole();
		void	DrawLamp();

		void 	DrawCube();
		void 	DrawCylinder();
		void 	DrawHalfCylinder();
		void 	DrawCone();
		void 	DrawCircle();
		void	DrawRectangle_ONE();

		void	DrawNormalCube();

		void	DisplayScene(const float);
		
		void  	CleanUp();
};

#endif

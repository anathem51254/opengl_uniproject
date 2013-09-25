
#include "../headers/core.h"


std::stack<glm::mat4> MatrixStack;


CORE::CORE () 
{ 
	WINDOW_WIDTH = 1600.0f;
	WINDOW_HEIGHT = 900.0f;

	FOV = 90.0f;
	NearPlane = 0.1f;
	FarPlane = 100.0f;
	
	sdl_context = new SDL_CONTEXT;

	utils = new UTILS;
	camera = new CAMERA(WINDOW_WIDTH, WINDOW_HEIGHT, FOV, NearPlane, FarPlane);

	generic_shader = new SHADER_PROGRAM;

	cube = new OBJECTS;
}

CORE::~CORE () 
{ 
	delete sdl_context;

	delete utils;
	delete camera;

	delete generic_shader;

	delete cube;
}


//////////////////////////////////////////////////
//		Model Matrix Code		//
//////////////////////////////////////////////////

void CORE::RotateModelMatrix(const float angle, glm::vec3 const vec)
{
       	MatrixStack.top() = glm::rotate(MatrixStack.top(), angle, vec); 
}

void CORE::TranslateModelMatrix(glm::vec3 const vec)
{
	MatrixStack.top() = glm::translate(MatrixStack.top(), vec);
}

void CORE::ScaleModelMatrix(glm::vec3 const vec)
{
	MatrixStack.top() = glm::scale(MatrixStack.top(), vec);
}


int CORE::InitGL()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "[DEBUG] GLEW Error: " << glewGetErrorString(err) << std::endl;
		return -1;
	}

	std::cout << "[DEBUG] Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;	
	std::cout << "[DEBUG] Using OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "[DEBUG] Using GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	utils->CheckErrors("glEnable(GL_DEPTH_TEST)");
	
	generic_shader->InitGenericShaders();

	cube->InitBuffers();

	return 0;	
}

void CORE::InitScene()
{
	camera->SetDefaultCamera();
}

void CORE::DrawFloorANDReflection()
{
	glEnable(GL_STENCIL_TEST);
	utils->CheckErrors("glEnable(GL_STENCIL_TEST)");

		cube->BindObject(1);
		// Draw Floor
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glDepthMask(GL_FALSE);
		glClear(GL_STENCIL_BUFFER_BIT);

		cube->DrawFloor();
		
		// Draw Reflection
		cube->BindObject(0);
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDepthMask(GL_TRUE);	

		TranslateModelMatrix(glm::vec3(0.0f, 0.0f, -1.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());

		ScaleModelMatrix(glm::vec3(1.0f, 1.0f, -1.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		
		generic_shader->ChangeUniformColor(0.3f, 0.3f, 0.3f);	
		cube->DrawCube();
		generic_shader->ChangeUniformColor(1.0f, 1.0f, 1.0f);
	
	glDisable(GL_STENCIL_TEST);
}


void CORE::DrawBeams(glm::mat4 ModelMatrix)
{
	// Center Beam
	for(float x = -1; x < 2; x++)
	{
		MatrixStack.push(ModelMatrix);
			TranslateModelMatrix(glm::vec3(0.0f, x, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			cube->DrawCube();
		MatrixStack.pop();
	}
	
	// Draw beams to the right 
	for(float x = 1; x < 4; x++)
	{
		for(float y = -1; y < 2; y++)
		{
			MatrixStack.push(ModelMatrix);
				TranslateModelMatrix(glm::vec3(x, y, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}

	// Draw beams to the left
	for(float x = -1; x > -4; x--)	
	{
		for(float y = -1; y < 2; y++)
		{
			MatrixStack.push(ModelMatrix);
				TranslateModelMatrix(glm::vec3(x, y, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}
}

void CORE::DrawLegs(glm::mat4 ModelMatrix)
{
	// Draw legs to the right
	for(float x = 1; x < 4; x+=2)
	{
		for(float y = -1; y < 2; y+=2)
		{
			MatrixStack.push(ModelMatrix);
				TranslateModelMatrix(glm::vec3(x, y, -1.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}

	for(float x = -1; x > -4; x-=2)
	{
		for(float y = -1; y < 2; y+=2)
		{
			MatrixStack.push(ModelMatrix);
				TranslateModelMatrix(glm::vec3(x, y, -1.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}
}

void CORE::DisplayScene()
{
	generic_shader->UseShaderProgram(camera->DefaultCameraMatrix.ViewMatrix, camera->DefaultCameraMatrix.ProjectionMatrix);	

	glm::mat4 ModelMatrix;

	MatrixStack.push(ModelMatrix);

	//glEnable(GL_STENCIL_TEST);
	//utils->CheckErrors("glEnable(GL_STENCIL_TEST)");

		/*glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glDepthMask(GL_FALSE);
		glClear(GL_STENCIL_BUFFER_BIT);
		*/

		cube->BindObject(0);

		/*		
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDepthMask(GL_TRUE);	
		*/

		generic_shader->ChangeUniformColor(0.3f, 0.6f, 0.2f);	

		RotateModelMatrix(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());

		DrawBeams(ModelMatrix);
		DrawLegs(ModelMatrix);

	//glDisable(GL_STENCIL_TEST);

	MatrixStack.pop();
}

CORE::WindowEvents CORE::ProcessEvent()
{
	WindowEvents windowEvent = (WindowEvents)sdl_context->ProcessEvent();

	switch(windowEvent)
	{
		case ESC:
			return ESC;
		case ONE:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			return ONE;
		case TWO:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			return TWO;
		case FIVE:
			camera->SetDefaultCamera();
			return FIVE;
		case A:
			camera->RotateCameraLeft();
			return A;
		case D:
			camera->RotateCameraRight();
			return D;
		default:
			return NOEVENT;
	}	
}

int CORE::InitSDL()
{
	try
	{
		SDLWindow = sdl_context->CreateSDLWindow("Test", WINDOW_WIDTH, WINDOW_HEIGHT);
		GLContext = sdl_context->CreateGLContext(SDLWindow);
	}
	catch( const std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	return 0;
}

void CORE::CleanUp()
{
}

int CORE::MainLoop()
{
	WindowEvents event = NOEVENT;

	InitScene();

	while( event != ESC )
	{
		utils->CheckErrors("MainLoop()");	

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		event = ProcessEvent();	
		if( event != NOEVENT )
			std::cout << "[DEBUG] " << event << std::endl;

		DisplayScene();

		sdl_context->ClearWindow(SDLWindow);
	}

	CleanUp();
	
	return 0;
}

void CORE::Initialise()
{
	InitSDL();
	InitGL();
}

void CORE::Start()
{
	Initialise();
	MainLoop();
	CleanUp();
}

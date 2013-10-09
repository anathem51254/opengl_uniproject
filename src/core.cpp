
#include "../headers/core.h"


std::stack<glm::mat4> MatrixStack;


const int UPDATES_PER_SECOND 	= 60;
const int SKIP_UPDATES		= 1000 / UPDATES_PER_SECOND;	
const int MAX_FRAMESKIP 	= 5;

unsigned int NextGameTick;
int Loops;
float Interpolation;

bool Running = true;

unsigned int Time;

CORE::CORE () 
{ 
	WINDOW_WIDTH = 1024.0f;
	WINDOW_HEIGHT = 720.0f;

	FOV = 90.0f;
	NearPlane = 0.1f;
	FarPlane = 5000.0f;

	Event = NOEVENT;
	
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

void CORE::DrawBeams()
{

	cube->BindObject(0);

	generic_shader->ChangeUniformColor(255.0f, 206.0f, 153.0f);	

	// Draw beams to the right and down the Z axis
	for(float x = 16.0f; x < 112.0f; x += 32.0f)
	{
		for(float z = -48.0f; z > -144.0f; z += -32.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, 32.0f, z));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}

	// Draw beams to the left and down the Z axis
	for(float x = -16.0f; x > -112.0f; x += -32.0f)
	{
		for(float z = -48.0f; z > -144.0f; z += -32.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, 32.0f, z));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}
}

void CORE::DrawLegs()
{
	cube->BindObject(1);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	// Draw legs to the right and down the Z axis
	for(float x = 16.0f; x < 112.0f; x += 64.0f)
	{
		for(float z = -40.0f; z > -136.0f; z += -80.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, -16.0f, z));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}

	// Draw legs to the left and down the Z axis
	for(float x = -16.0f; x > -112.0f; x += -64.0f)
	{
		for(float z = -40.0f; z > -136.0f; z += -80.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, -16.0f, z));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				cube->DrawCube();
			MatrixStack.pop();
		}
	}
}

void CORE::DrawCube()
{
	cube->BindObject(0);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-16.0f, 0.0f, -50.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		cube->DrawCube();
	MatrixStack.pop();

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(16.0f, 0.0f, -50.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		cube->DrawCube();
	MatrixStack.pop();

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-16.0f, 32.0f, -50.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		cube->DrawCube();
	MatrixStack.pop();

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(16.0f, 32.0f, -50.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		cube->DrawCube();
	MatrixStack.pop();
}

void CORE::DisplayScene(const float _Interpolation)
{

	//generic_shader->UseShaderProgram(camera->DefaultCameraMatrix.MVP + _Interpolation);	
	generic_shader->UseShaderProgram(camera->DefaultCameraMatrix.MVP);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);

		//DrawCube(); // Test to see if everything is ok
		
		// Bridge
		DrawBeams();
		DrawLegs();

	MatrixStack.pop();
}

void CORE::ProcessEvent()
{

	float x, y;

	switch(Event)
	{
		case ESC:
				std::cout << "[DEBUG] Event: ESC" << std::endl;
			break;
		case MOUSE:

				x = sdl_context->GetMouseRelX();
				y = sdl_context->GetMouseRelY();

				std::cout << "[DEBUG] X: " << x << std::endl;
				std::cout << "[DEBUG] Y: " << y << std::endl;

				camera->MoveMouseCamera(x, y, 1);

				camera->ComputeVectors();	
			break;
		case W:
				camera->MoveCameraForward(1);
				
				std::cout << "[DEBUG] CameraEvent: W" << std::endl;
			break;
		case S:
				camera->MoveCameraBackward(1);
				
				std::cout << "[DEBUG] CameraEvent: S" << std::endl;
			break;
		case A:
				camera->StrafeCameraRight(1);
				
				std::cout << "[DEBUG] CameraEvent: A" << std::endl;
			break;
		case D:
				camera->StrafeCameraLeft(1);

				std::cout << "[DEBUG] CameraEvent: D" << std::endl;
			break;
		case ONE:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				std::cout << "[DEBUG] Event: ONE" << std::endl;
			break;
		case TWO:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				std::cout << "[DEBUG] Event: TWO" << std::endl;
			break;
		case FIVE:
				if(Running == true)
				{
					Running = false;
					Time = 0;
				}
				else
				{
					Running = true;
					Time = sdl_context->GetTime();
				}

				std::cout << "[DEBUG] Event: FIVE" << std::endl;
			break;
		case Q:
			break;
		case E:
			break;
		case RIGHT:
			break;
		case LEFT:
			break;
		case NOEVENT:
			break;

	}	

	sdl_context->CenterMouse(SDLWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
	camera->UpdateDefaultCamera();
}

void CORE::ProcessCameraEvent()
{
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
	sdl_context->CenterMouse(SDLWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
	camera->SetDefaultCamera();

	NextGameTick = sdl_context->GetTime();

	while(Event != ESC)
	{

		Event = (WindowEvents)sdl_context->ProcessEvent();

		Loops = 0;
		while(sdl_context->GetTime() > NextGameTick && Loops < MAX_FRAMESKIP && Event != ESC)
		{
			ProcessEvent();	

			NextGameTick += SKIP_UPDATES;
			Loops++;
		}

		camera->UpdateMVP();

		Interpolation = float(sdl_context->GetTime() + SKIP_UPDATES - NextGameTick) / float(SKIP_UPDATES);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		DisplayScene(Interpolation);

		utils->CheckErrors("MainLoop()");	

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

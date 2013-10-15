
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

	objects = new OBJECTS;
}

CORE::~CORE () 
{ 
	delete sdl_context;

	delete utils;
	delete camera;

	delete generic_shader;

	delete objects;
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

	objects->BuildObjects();

	return 0;	
}


void CORE::DrawBeams()
{
	objects->BindObject(0);

	generic_shader->ChangeUniformColor(255.0f, 206.0f, 153.0f);	

	for(float x = 4.0f; x < 128.0f; x += 8.0f)
	{
		float z = -40.0f;
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 76.0f, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	for(float x = -4.0f; x > -128.0f; x += -8.0f)
	{
		float z = -40.0f;
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 76.0f, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}
}

void CORE::DrawLegs()
{
	objects->BindObject(2);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	for(float x = 32.0f; x < 128.0f; x += 64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();
	}

	for(float x = -32.0f; x > -128.0f; x += -64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();
	}
}

void CORE::DrawRails()
{
	objects->BindObject(1);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	for(float x = 16.0f; x < 128.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 82.0f, 10.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 82.0f, -90.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	for(float x = -16.0f; x > -128.0f; x += -32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 82.0f, 10.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 82.0f, -90.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}
}

void CORE::DrawLampPole()
{
}

void CORE::DrawLamp()
{
}

void CORE::DrawFloor()
{
	objects->BindObject(3);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	for(float x = 0.0f; x < 256.0f; x += 16.0f)
	{
		for(float z = 54.0f; z > -256.0f; z += -16.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, 0.0f, z));
				ScaleModelMatrix(glm::vec3(16.0f, 0.0f, 16.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawSquare();
			MatrixStack.pop();
		}
	}
	
	for(float x = 0.0f; x > -256.0f; x -= 16.0f)
	{
		for(float z = 54.0f; z > -256.0f; z += -16.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, 0.0f, z));
				ScaleModelMatrix(glm::vec3(16.0f, 0.0f, 16.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawSquare();
			MatrixStack.pop();
		}
	}
}

// TEST
void CORE::DrawCube()
{
	objects->BindObject(0);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(0.0, 0.0f, -50.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawCube();
	MatrixStack.pop();
}

void CORE::DrawHalfCylinder()
{
	objects->BindObject(4);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-40.0f, 0.0f, -10.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawHalfCylinder_ONE();
	MatrixStack.pop();

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-40.0f, 0.0f, -10.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawHalfCylinder_TWO();
	MatrixStack.pop();

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-40.0f, 0.0f, -10.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawHalfCylinder_THREE();
	MatrixStack.pop();
}

void CORE::DrawCylinder()
{
	objects->BindObject(4);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-40.0f, 0.0f, -10.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawCylinder();
	MatrixStack.pop();
}

void CORE::DrawCircle()
{
	objects->BindObject(5);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(20.0f, 0.0f, -10.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawCircle();
	MatrixStack.pop();
}

void CORE::DrawCone()
{
	objects->BindObject(6);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(40.0f, 0.0f, -10.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawCylinder();
	MatrixStack.pop();
}

void CORE::DisplayScene(const float _Interpolation)
{
	//generic_shader->UseShaderProgram(camera->DefaultCameraMatrix.MVP + _Interpolation);	
	generic_shader->UseShaderProgram(camera->DefaultCameraMatrix.MVP);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);

		if(Scene == TEST)
		{
			//DrawCube(); // Test to see if everything is ok
			//DrawCylinder();
			DrawHalfCylinder();
			//DrawCone();
			//DrawCircle();
		}
		else if(Scene == BRIDGE)
		{
			DrawFloor();
			DrawBeams();
			DrawLegs();
			DrawRails();
		}

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

				//std::cout << "[DEBUG] X: " << x << std::endl;
				//std::cout << "[DEBUG] Y: " << y << std::endl;

				camera->MoveMouseCamera(x, y, 1);

				camera->ComputeVectors();	
			break;
		case W:
				camera->MoveCameraForward(1);
				camera->ComputeVectors();	
				
				std::cout << "[DEBUG] CameraEvent: W" << std::endl;
			break;
		case S:
				camera->MoveCameraBackward(1);
				camera->ComputeVectors();	
				
				std::cout << "[DEBUG] CameraEvent: S" << std::endl;
			break;
		case A:
				camera->StrafeCameraRight(1);
				camera->ComputeVectors();	
				
				std::cout << "[DEBUG] CameraEvent: A" << std::endl;
			break;
		case D:
				camera->StrafeCameraLeft(1);
				camera->ComputeVectors();	

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

				camera->FaceCameraFront();
				camera->ComputeVectors();	
				std::cout << "[DEBUG] Event: FIVE" << std::endl;
			break;
		case SIX:
			
				camera->FaceCameraBack();
				camera->ComputeVectors();	
				std::cout << "[DEBUG] Event: SIX" << std::endl;

			break;
		case SEVEN: 
			
				camera->FaceCameraRight();
				camera->ComputeVectors();	
				std::cout << "[DEBUG] Event: SEVEN" << std::endl;
			break;
		case EIGHT:
			
				camera->FaceCameraLeft();
				camera->ComputeVectors();	
				std::cout << "[DEBUG] Event: EIGHT" << std::endl;
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

	Scene = TEST;

	sdl_context->CenterMouse(SDLWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
	camera->FaceCameraFront();
	camera->ComputeVectors();

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

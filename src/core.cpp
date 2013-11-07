
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

bool AnimateGateOne = false;
bool AnimateGateTwo = false;


bool AnimateGateOneOpen = false;
bool AnimateGateOneClose = true;

bool AnimateGateTwoOpen = false;
bool AnimateGateTwoClose = true;

float AnimateAngleOne = 0.0f;
float AnimateAngleTwo = 0.0f;

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
	
	generic_shader->BuildShaders();

	objects->BuildObjects();

	return 0;	
}


void CORE::DrawBeams()
{
	float x = 0.0f;
	float z = 0.0f;
	float y = 0.0f;

	objects->BindObject(0);

	generic_shader->ChangeUniformColor(255.0f, 206.0f, 153.0f);	

	y = 76.0f;
	z = -40.0f;

	for(x = 4.0f; x < 128.0f; x += 8.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	for(x = -4.0f; x > -128.0f; x += -8.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}


	// Sloped end
	//
	y = 75.0f;
	
	for(x = 132.0f; x < 224.0f; x += 8.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(355.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		y -= 1.0;
	}
}

void CORE::DrawUnderBeams()
{
	float x = 0.0f;
	float y = 0.0f;
	float yu = 0.0f;
	float zf = 0.0f;
	float zb = 0.0f;
	float zm = 0.0f;

	objects->BindObject(7);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	y = 72.0f;
	yu = 70.0f; 
	zf = 0.0f;
	zb = -80.0f;
	zm = -40.0f;

	// Under Beam
	for(x = 0.0f; x < 128.0f; x += 32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zm));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

	}

	for(x = 0.0f; x > -128.0f; x += -32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zm));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}
	

	objects->BindObject(8);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	float rotx = 0.0f;
	float roty = 270.0f;
	float rotz = 90.0f;
	for(x = 0.0f; x < 160.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();
	}

	for(x = 0.0f; x > -128.0f; x += -32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();
	}

	// End
	
	objects->BindObject(7);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	y = 71.0f;
	yu = 67.0f; 
	zf = 0.0f;
	zb = -80.0f;
	zm = -40.0f;

	for(x = 128.0f; x < 224.0f; x += 32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zm));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		y -= 3;
	}

	objects->BindObject(8);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	rotx = 355.0f;
	roty = 270.0f;
	rotz = 90.0f;
	for(x = 160.0f; x < 256.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		yu -= 3;
	}
}

void CORE::DrawLegs()
{
	objects->BindObject(2);

	generic_shader->ChangeUniformColor(221.0f, 183.0f, 152.0f);	

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

void CORE::DrawLegSupport()
{
	float y = 0.0f;
	float zf = 0.0f;
	float zb = 0.0f;
	float rotx = 90.0f;
	float roty = 0.0f;
	float rotz = 0.0f;

	objects->BindObject(9);

	generic_shader->ChangeUniformColor(221.0f, 183.0f, 22.0f);	
	
	y  = 60.0f;
	zf = -40.0f;
	zb = -88.0f;
	for(float x = 32.0f; x < 128.0f; x += 64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
	}

	for(float x = -32.0f; x > -128.0f; x += -64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
	}
}

void CORE::DrawRails()
{
	float zf = 0.0f;
	float zb = 0.0f;
	float y = 0.0f;

	objects->BindObject(1);

	generic_shader->ChangeUniformColor(230.0f, 201.0f, 179.0f);	

	zf = 10.0f;
	zb = -90.0f;
	y = 78.0f;
	for(float x = 16.0f; x < 128.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	for(float x = -16.0f; x > -128.0f; x += -32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	objects->BindObject(4);

	zf = 10.0f;
	zb = -90.0f;
	y = 88.0f;
	for(float x = 0.0f; x < 160.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
	}

	for(float x = 0.0f; x > -128.0f; x += -32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
	}


	// Sloped end
	objects->BindObject(1);

	zf = 10.0f;
	zb = -90.0f;
	y = 75.0f;
	for(float x = 143.0f; x < 223.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
		y -= 3;
	}

	objects->BindObject(4);

	zf = 10.0f;
	zb = -90.0f;
	y = 85.0f;
	for(float x = 159.0f; x < 253.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();

		y -= 3;
	}
}

void CORE::DrawGateOne()
{
	float zf = 0.0f;
	float zb = 0.0f;
	float y = 0.0f;
	float x = 0.0f;

	objects->BindObject(1);

	generic_shader->ChangeUniformColor(230.0f, 201.0f, 179.0f);	

	zf = 10.0f;
	zb = -90.0f;
	y = 72.0f;
	x = 225.0f;
	//y = 0.0f;
	//x = 0.0f;


	if(AnimateGateOne == true)
	{
		if(AnimateGateOneClose == true)
		{
			AnimateAngleOne += 1.0;

			if(AnimateAngleOne > 90.0f)
			{
				AnimateGateOne = false;
				AnimateGateOneOpen = true;
				AnimateGateOneClose = false;
				AnimateAngleOne = 90.0f;
			}
			//std::cout << "[DEBUG] +Angle: " << AnimateAngleOne << std::endl;
		}

		if(AnimateGateOneOpen == true)
		{
			AnimateAngleOne -= 1.0;

			if(AnimateAngleOne < 0.0f)
			{
				AnimateGateOne = false;
				AnimateGateOneClose = true;
				AnimateGateOneOpen = false;
				AnimateAngleOne = 0.0f;
			}
			//std::cout << "[DEBUG] -Angle: " << AnimateAngleOne << std::endl;
		}
	}

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);

		TranslateModelMatrix(glm::vec3(x, y, zf));
		generic_shader->UpdateUniformModel(MatrixStack.top());


		RotateModelMatrix(AnimateAngleOne, glm::vec3(0.0f, 1.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());


			TranslateModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		

			TranslateModelMatrix(glm::vec3(-48.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());


			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(8.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();
			
				// Reset
				TranslateModelMatrix(glm::vec3(-8.0f, 34.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(-4.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

		TranslateModelMatrix(glm::vec3(4.0f, 34.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());

	MatrixStack.pop();
}

void CORE::DrawGateTwo()
{
	float zf = 0.0f;
	float zb = 0.0f;
	float y = 0.0f;
	float x = 0.0f;

	objects->BindObject(1);

	generic_shader->ChangeUniformColor(230.0f, 201.0f, 179.0f);	

	zf = -90.0f;
	zb = -90.0f;
	y = 72.0f;
	x = 225.0f;
	//y = 0.0f;
	//x = 0.0f;

	if(AnimateGateTwo == true)
	{
		if(AnimateGateTwoClose == true)
		{
			AnimateAngleTwo -= 1.0;

			if(AnimateAngleTwo < -90.0f)
			{
				AnimateGateTwo = false;
				AnimateGateTwoOpen = true;
				AnimateGateTwoClose = false;
				AnimateAngleTwo = -90.0f;
			}
			//std::cout << "[DEBUG] -Angle: " << AnimateAngleTwo << std::endl;
		}

		if(AnimateGateTwoOpen == true)
		{
			AnimateAngleTwo += 1.0;

			if(AnimateAngleTwo > 0.0f)
			{
				AnimateGateTwo = false;
				AnimateGateTwoClose = true;
				AnimateGateTwoOpen = false;
				AnimateAngleTwo = 0.0f;
			}
			//std::cout << "[DEBUG] +Angle: " << AnimateAngleTwo << std::endl;
		}

	}

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);

		TranslateModelMatrix(glm::vec3(x, y, zf));
		generic_shader->UpdateUniformModel(MatrixStack.top());


		RotateModelMatrix(AnimateAngleTwo, glm::vec3(0.0f, 1.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());


			TranslateModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		

			TranslateModelMatrix(glm::vec3(-48.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());


			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(8.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();
			
				// Reset
				TranslateModelMatrix(glm::vec3(-8.0f, 34.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(-4.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

		TranslateModelMatrix(glm::vec3(4.0f, 34.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());

	MatrixStack.pop();
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
	objects->BindObject(10);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		//TranslateModelMatrix(glm::vec3(0.0, 0.0f, -10.0f));
		//generic_shader->UpdateUniformModel(MatrixStack.top());
		
		glm::mat4 model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		generic_shader->UpdateTextureGenericShaderUniform(model, camera->DefaultCameraMatrix.ViewMatrix, camera->DefaultCameraMatrix.ProjectionMatrix, camera->DefaultCameraMatrix.Normal);

		//generic_shader->UpdateUniformModel(MatrixStack.top(), camera->DefaultCameraMatrix.Normal);
		objects->DrawCube();
	MatrixStack.pop();
}

// TEST
void CORE::DrawNormalCube()
{
	objects->BindObject(11);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	TranslateModelMatrix(glm::vec3(0.0, 0.0f, 0.0f));
	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(0.0, 0.0f, 0.0f));
		//glm::mat4 model = glm::translate(model, glm::vec3(0.0f, -20.0f, 0.0f));
		//generic_shader->UpdateTextureGenericShaderUniform(model, camera->DefaultCameraMatrix.ViewMatrix, camera->DefaultCameraMatrix.ProjectionMatrix, camera->DefaultCameraMatrix.Normal);
		generic_shader->UpdateUniformModel(MatrixStack.top(), camera->DefaultCameraMatrix.Normal);
		objects->DrawCube();
	MatrixStack.pop();
}

void CORE::DrawHalfCylinder()
{
	objects->BindObject(4);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	


	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-40.0f, 0.0f, -10.0f));
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawHalfCylinder_ONE();
	MatrixStack.pop();

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-40.0f, 0.0f, -10.0f));
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawHalfCylinder_TWO();
	MatrixStack.pop();

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(-40.0f, 0.0f, -10.0f));
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
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

void CORE::DrawRectangle_ONE()
{

	objects->BindObject(7);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);
		TranslateModelMatrix(glm::vec3(0.0f, 0.0f, -10.0f));
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());
		objects->DrawCube();
	MatrixStack.pop();
}

void CORE::DisplayScene(const float _Interpolation)
{
	generic_shader->UseShaderProgram(0);	

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);

		if(Scene == TEST)
		{
			DrawCube();
			//DrawNormalCube();
			//DrawCylinder();
			//DrawHalfCylinder();
			//DrawCone();
			//DrawCircle();
			//DrawRectangle_ONE();
			//DrawLegSupport();
			//DrawGateOne();
			//DrawGateTwo();
		}
		else if(Scene == BRIDGE)
		{
			DrawFloor();
			DrawBeams();
			DrawUnderBeams();
			DrawLegs();
			DrawLegSupport();
			DrawRails();
			DrawGateOne();
			DrawGateTwo();
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
			AnimateGateOne = true;
			AnimateGateTwo = true;
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

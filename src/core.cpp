
#include "../headers/core.h"


GLuint vao[2];

glm::mat4 MatrixStack[10];

unsigned int MatrixStackNumber = 0;

float CameraAngle = 0.0f;

// Cube 
const float CubeVertices[] = { 
//	 X	Y     Z     R     G	B     U     V	
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f

};

const float FloorVertices[] = {
	
	// floor
	-1.2f, -1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //0.0f, 1.0f,
	 1.2f, -1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //1.0f, 1.0f,
	 1.2f,  1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //1.0f, 0.0f,
	 1.2f,  1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //1.0f, 0.0f,
	-1.2f,  1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //0.0f, 0.0f,
	-1.2f, -1.2f, -0.5f, 0.0f, 0.0f, 0.0f //0.0f, 1.0f
};


CORE::CORE () 
{ 
	WINDOW_WIDTH = 1600;
	WINDOW_HEIGHT = 900;

	FOV = 90.0f;
	NearPlane = 0.1f;
	FarPlane = 100.0f;
	
	utils = new UTILS;
	sdl_context = new SDL_CONTEXT;
	generic_shader = new SHADER_PROGRAM;
}

CORE::~CORE () 
{ 
	delete utils;
	delete sdl_context;
	delete generic_shader;
}

void CORE::InitBuffers()
{
	GLuint vbo;
	
	glGenVertexArrays(2, vao);

	//*******************************************//
	//		Cube Buffer		     //
	//*******************************************//
	glBindVertexArray(vao[0]);	
	glGenBuffers( 1, &vbo);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	glBufferData( GL_ARRAY_BUFFER, sizeof( CubeVertices ), CubeVertices, GL_STATIC_DRAW );

	// Linking vertex data and vertex array attributes
	glEnableVertexAttribArray( 0 );	
	utils->CheckErrors("glEnableVertexAttribArray( index = 0 )");
	glEnableVertexAttribArray( 1 );
	utils->CheckErrors("glEnableVertexAttribArray( index = 1 )");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	utils->CheckErrors("glVertexAttribPointer( index = 0 )");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)( 3*sizeof(float)));
	utils->CheckErrors("glVertexAttribPointer( index = 1 )");


	//*******************************************//
	//		Floor Buffer		     //
	//*******************************************//
	glBindVertexArray(vao[1]);	
	glGenBuffers( 1, &vbo);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	glBufferData( GL_ARRAY_BUFFER, sizeof( FloorVertices ), FloorVertices, GL_STATIC_DRAW );

	// Linking vertex data and vertex array attributes
	glEnableVertexAttribArray( 0 );	
	utils->CheckErrors("glEnableVertexAttribArray( index = 0 )");
	glEnableVertexAttribArray( 1 );
	utils->CheckErrors("glEnableVertexAttribArray( index = 1 )");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	utils->CheckErrors("glVertexAttribPointer( index = 0 )");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)( 3*sizeof(float)));
	utils->CheckErrors("glVertexAttribPointer( index = 1 )");

}

//////////////////////////////////////////////////
//		Model Matrix Code		//
//////////////////////////////////////////////////

glm::mat4 CORE::RotateModelMatrix(glm::mat4 temp_modelMatrix, const float angle, glm::vec3 const vec)
{
       	temp_modelMatrix = glm::rotate(temp_modelMatrix, angle, vec); 

	return temp_modelMatrix;
}

glm::mat4 CORE::TranslateModelMatrix(glm::mat4 temp_modelMatrix, glm::vec3 const vec)
{
	temp_modelMatrix = glm::translate(temp_modelMatrix, vec);

	return temp_modelMatrix;
}

glm::mat4 CORE::ScaleModelMatrix(glm::mat4 temp_modelMatrix, glm::vec3 const vec)
{
	temp_modelMatrix = glm::scale(temp_modelMatrix, vec);
	
	return temp_modelMatrix;
}

glm::mat4 CORE::PushModelMatrix(glm::mat4 temp_ModelMatrix)
{
	MatrixStack[MatrixStackNumber] = temp_ModelMatrix;
	MatrixStackNumber++;

	return temp_ModelMatrix;
}

glm::mat4 CORE::PopModelMatrix(glm::mat4 temp_ModelMatrix)
{
	if(MatrixStackNumber == 0)
	{
		temp_ModelMatrix = MatrixStack[0];
	}
	else
	{
		MatrixStackNumber--;
		temp_ModelMatrix = MatrixStack[MatrixStackNumber];
		
	}

	return temp_ModelMatrix;
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
	InitBuffers();

	return 0;	
}




void CORE::SetDefaultCamera()
{
	CameraAngle = 0.0f;

	float aspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

	ViewMatrix = glm::lookAt(glm::vec3(0.0f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	ProjectionMatrix = glm::perspective(FOV, aspectRatio, NearPlane, FarPlane);
}

void CORE::MoveCameraLeft()
{
	if(CameraAngle == 0.0f)
	{
		CameraAngle = 360.0f;
	}

	if(CameraAngle <= 360.0f)
	{
		CameraAngle -= 1.0f; 
	}

	std::cout << "[DEBUG] Camera Angle: " << CameraAngle << std::endl;

	float aspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

	ViewMatrix = glm::lookAt(glm::vec3(0.0f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

       	ViewMatrix = glm::rotate(ViewMatrix, CameraAngle, glm::vec3(0.0f, 0.0f, 1.0f)); 

	ProjectionMatrix = glm::perspective(FOV, aspectRatio, NearPlane, FarPlane);
}

void CORE::MoveCameraRight()
{
	if(CameraAngle == 360.0f)
	{
		CameraAngle = 0.0f;
	}

	if(CameraAngle <= 360.0f)
	{
		CameraAngle += 1.0f; 
	}

	std::cout << "[DEBUG] Camera Angle: " << CameraAngle << std::endl;

	float aspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

	ViewMatrix = glm::lookAt(glm::vec3(0.0f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

       	ViewMatrix = glm::rotate(ViewMatrix, CameraAngle, glm::vec3(0.0f, 0.0f, 1.0f)); 

	ProjectionMatrix = glm::perspective(FOV, aspectRatio, NearPlane, FarPlane);
}




void CORE::InitScene()
{
	SetDefaultCamera();
}

void CORE::DisplayScene()
{

	generic_shader->UseShaderProgram(ViewMatrix, ProjectionMatrix);	

	glm::mat4 temp_modelMatrix;

	temp_modelMatrix = PushModelMatrix(temp_modelMatrix);

	temp_modelMatrix = RotateModelMatrix(temp_modelMatrix, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	generic_shader->UpdateUniformModel(temp_modelMatrix);


	// Draw Cube
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glEnable(GL_STENCIL_TEST);
	utils->CheckErrors("glEnable(GL_STENCIL_TEST)");

		glBindVertexArray(vao[1]);
		// Draw Floor
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glDepthMask(GL_FALSE);
		glClear(GL_STENCIL_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glBindVertexArray(vao[0]);
		// Draw Reflection
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDepthMask(GL_TRUE);	

		//temp_modelMatrix = PopMatrix(temp_modelMatrix);		
		//temp_modelMatrix = PushMatrix(temp_modelMatrix);

		temp_modelMatrix = TranslateModelMatrix(temp_modelMatrix, glm::vec3(0.0f, 0.0f, -1.0f));
		generic_shader->UpdateUniformModel(temp_modelMatrix);

		temp_modelMatrix = ScaleModelMatrix(temp_modelMatrix, glm::vec3(1.0f, 1.0f, -1.0f));
		generic_shader->UpdateUniformModel(temp_modelMatrix);
		
		generic_shader->ChangeUniformColor(0.3f, 0.3f, 0.3f);	
		glDrawArrays(GL_TRIANGLES, 0, 36);
		generic_shader->ChangeUniformColor(1.0f, 1.0f, 1.0f);
	
	glDisable(GL_STENCIL_TEST);

	temp_modelMatrix = PopModelMatrix(temp_modelMatrix);

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
			SetDefaultCamera();
			return FIVE;
		case A:
			MoveCameraLeft();
			return A;
		case D:
			MoveCameraRight();	
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
	glDeleteVertexArrays(2, vao);
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

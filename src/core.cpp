
#include "../core.h"

UTILS *utils;
SDL_CONTEXT *sdl_context;

const unsigned int WINDOW_WIDTH  = 1280;
const unsigned int WINDOW_HEIGHT = 720;

const float FOV = 90.0f;
const float NearPlane = 0.1f;
const float FarPlane = 100.0f;

const int ShaderNumber = 2;

GLuint Shaders[ShaderNumber];

GLuint GenericShaderProgram = 0;

GLuint vao[2];

glm::mat4 ViewMatrix; 
glm::mat4 ProjectionMatrix;

GLint uniModel;
GLint uniView;
GLint uniProj;

GLint uniColor;

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

// Shaders
const std::string vertexShaderSource(
	"#version 430\n"
	"layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec3 color;\n"
	"out vec3 Color;\n"
	"uniform mat4 modelMatrix;\n"
	"uniform mat4 viewMatrix;\n"
	"uniform mat4 projMatrix;\n"
	"uniform vec3 overrideColor;\n"
	"void main() {\n"
		"Color = overrideColor * color;\n"
		"gl_Position = projMatrix * viewMatrix * modelMatrix * vec4( position, 1.0f );\n"
	"}\n"
);	

const std::string fragmentShaderSource(
	"#version 430\n"
	"in vec3 Color;\n"
	"out vec4 outColor;\n"
	"void main() {\n"
		"outColor = vec4( Color, 1.0 );\n"
	"}\n"
);


CORE::CORE () 
{ 
	utils = new UTILS;
	sdl_context = new SDL_CONTEXT;
}

CORE::~CORE () 
{ 
	delete utils;
	delete sdl_context;
}

int CORE::DebugShaderProgram(GLuint ShaderProgram, GLint status)
{
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		std::cout << "[DEBUG] Linking Program [FAILED]\n" << std::endl;
		
		GLint infoLogLength;
		glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(ShaderProgram, infoLogLength, NULL, strInfoLog);

		std::cout << "[DEBUG] Linking Program Log: \n\n" << strInfoLog << std::endl;

		delete[] strInfoLog;

		return -1;
	}
	std::cout << "[DEBUG] Linking Program [OK]\n" << std::endl;

	return 0;
}

GLuint CORE::CreateShader( const std::string &shaderSource, GLenum eShaderType )
{
	GLuint shader = glCreateShader(eShaderType);
	const char* shaderSourceStr = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderSourceStr, NULL);

	glCompileShader(shader);

	const char* strShaderType = NULL;
	switch(eShaderType)
	{
		case GL_VERTEX_SHADER:
			strShaderType = "Vertex"; break;
		case GL_GEOMETRY_SHADER:
			strShaderType = "Geometry"; break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "Fragment"; break;
	}

	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		
		std::cout << "[DEBUG] " << strShaderType << " Compilation error: " << strInfoLog << std::endl;
		delete[] strInfoLog;
	}
	else
		std::cout << "[DEBUG] " << strShaderType << " Compilation [OK] " << std::endl;

	return shader;
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

int CORE::InitGenericShaders()
{
	int retn = 0;

	Shaders[0] = CreateShader( vertexShaderSource, GL_VERTEX_SHADER );
	Shaders[1] = CreateShader( fragmentShaderSource, GL_FRAGMENT_SHADER );

	GenericShaderProgram = glCreateProgram();
	utils->CheckErrors("glCreateProgram()");

	for(int i = 0; i < ShaderNumber; i++)
	{
		glAttachShader(GenericShaderProgram, Shaders[i]);
	}

	GLint status = 0;

	glLinkProgram(GenericShaderProgram);
	retn = DebugShaderProgram(GenericShaderProgram, status);

	if(retn == 0)
	{
		uniModel = glGetUniformLocation(GenericShaderProgram, "modelMatrix");	
		utils->CheckErrors("glGetUniformLocation(modelMatrix)");
		uniView = glGetUniformLocation(GenericShaderProgram, "viewMatrix");
		utils->CheckErrors("glGetUniformLocation(viewMatrix)");
		uniProj = glGetUniformLocation(GenericShaderProgram, "projMatrix");
		utils->CheckErrors("glGetUniformLocation(projMatrix)");

		uniColor = glGetUniformLocation(GenericShaderProgram, "overrideColor");
		utils->CheckErrors("glGetUniformLocation(overrideColor)");
	}

	return retn;
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
	
	InitGenericShaders();
	InitBuffers();

	return 0;	
}

void CORE::SetDefaultCamera()
{
	float aspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

	ViewMatrix = glm::lookAt(glm::vec3( 1.5f, 1.5f, 1.5f ), glm::vec3(0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ));

	ProjectionMatrix = glm::perspective(FOV, aspectRatio, NearPlane, FarPlane);
}

void CORE::MoveCameraLeft()
{

}

void CORE::MoveCameraRight()
{

}

void CORE::InitScene()
{
	SetDefaultCamera();
}

void CORE::DisplayScene()
{
	glUseProgram(GenericShaderProgram);

	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	
	glm::mat4 temp_modelMatrix;

       	temp_modelMatrix = glm::rotate( temp_modelMatrix, ( (float)clock() / (float)CLOCKS_PER_SEC * 180.0f ) , glm::vec3( 0.0, 0.0f, 1.0f ) ); 
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(temp_modelMatrix));


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
		
		temp_modelMatrix = glm::scale( glm::translate(temp_modelMatrix, glm::vec3(0,0,-1) ), glm::vec3(1, 1, -1));
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(temp_modelMatrix));
		
		glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);
	
	glDisable(GL_STENCIL_TEST);	
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
		sdl_context->Quit();
		return -1;
	}

	return 0;
}

void CORE::CleanUp()
{

	glDeleteVertexArrays(2, vao);

	glDeleteProgram(GenericShaderProgram);

	for(int i = 0; i < ShaderNumber; i++)
	{
		glDeleteShader(Shaders[i]);
	}

	sdl_context->Quit();
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

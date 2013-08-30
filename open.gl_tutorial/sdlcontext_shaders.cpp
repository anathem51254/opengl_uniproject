#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <ctime>

#include <GL/glew.h>
#include <GL/gl.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
	

SDL_Window* window;
SDL_GLContext glcontext;

GLenum err;
GLuint vao;
GLuint vbo;
GLuint ebo;

GLuint elements[] = {
	0, 1, 2, 
	2, 3, 0
};
	
float vertices[] = { 
	-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top left 
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Top right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom right
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom left
};

// Shaders
const std::string vertexShaderSource(
	"#version 430\n"
	"layout(location = 0) in vec2 position;\n"
	"layout(location = 1) in vec3 color;\n"
	"out vec3 Color;\n"
	"void main() {\n"
	"Color = color;\n"
	"gl_Position = vec4( position, 0.0, 1.0 );\n"
	"}\n"
);	

const std::string fragmentShaderSource(
	"#version 430\n"
	"in vec3 Color;\n"
	"out vec4 outColor;\n"
	"void main() {\n"
	"outColor = vec4(Color, 1.0f);\n"
	"}\n"
);
/*
const std::string fragmentShaderSource(
	"#version 430\n"
	"layout(location = 2) uniform vec3 triangleColor;\n"
	"out vec4 outColor;\n"
	"void main() {\n"
	"outColor = vec4(triangleColor, 1.0f);\n"
	"}\n"
);
*/

void printVersions()
{
	printf("[DEBUG] Using OpenGL Version: %s\n", (const char*)glGetString(GL_VERSION));
	printf("[DEBUG] Using GLSL Version: %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void checkErrors(std::string func)
{
	if((err = glGetError()) != GL_NO_ERROR)
	std::cout << "[DEBUG] " << func << " OpenGl error: " << err << std::endl;
}

GLuint CreateShader( const std::string &shaderSource, GLenum eShaderType )
{
	GLuint shader = glCreateShader( eShaderType );
	const char* shaderSourceStr = shaderSource.c_str();
	glShaderSource( shader, 1, &shaderSourceStr, NULL );

	glCompileShader( shader );

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
	glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
	if(status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );
		
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		
		std::cout << "[DEBUG] " << strShaderType << " Compilation error: " << strInfoLog << std::endl;
		delete[] strInfoLog;
	}
	else
		std::cout << "[DEBUG] " << strShaderType << " Compilation [OK] " << std::endl;

	return shader;
} 

void initVertexObjects()
{
	// Vertex Array Object
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );	

	// Init Vertex Data & put in GPU memory
	glGenBuffers( 1, &vbo);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void initElementObjects()
{
	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );
}

void init()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	
	window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	glcontext = SDL_GL_CreateContext(window);	
	
	printVersions();
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	initVertexObjects();	
	initElementObjects();
}

void Draw(GLuint shaderProgram)
{
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	
		glClear( GL_COLOR_BUFFER_BIT );
			
		//glUseProgram( shaderProgram );
		//checkErrors("glUseProgram()");	
		//glBindBuffer( GL_ARRAY_BUFFER, vbo );
	/*	
		GLint uniColor = glGetUniformLocation( shaderProgram, "triangleColor" );
		checkErrors( "glGetUniformLocation()");
		float time = (float)clock() / (float)CLOCKS_PER_SEC;
		std::cout << "[DEBUG] Clock: " << ( sin( time * 4.0f )  ) / 2.0f << std::endl;
		glUniform3f( uniColor, ( sin( time * 2.0f ) + 1.0f) / 2.0f, 0.0f, 0.0f );
		checkErrors( "glUniform3f()" );
	*/	
		// Linking vertex data and attributes
		glEnableVertexAttribArray( 0 );	
		checkErrors("glEnableVertexAttribArray( index = 0 )");
		glEnableVertexAttribArray( 1 );
		checkErrors("glEnableVertexAttribArray( index = 1 )");

		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0 );
		checkErrors("glVertexAttribPointer( index = 0 )");
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)( 2*sizeof(float) ) );

		//glDrawArrays( GL_TRIANGLES, 0, 6 );	
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
		checkErrors( "glDrawElements()" );
	
		glDisableVertexAttribArray( 0 );
		//glUseProgram( 0 );		
}

int main( int argc, char *argv[] )
{
	init();
		
	// Build shaders into program	
	GLuint shaderProgram = glCreateProgram();
	checkErrors("glCreateProgram()");
	
	glAttachShader( shaderProgram, CreateShader( vertexShaderSource, GL_VERTEX_SHADER ));
	glAttachShader( shaderProgram, CreateShader( fragmentShaderSource, GL_FRAGMENT_SHADER ));

	//glBindFragDataLocation( shaderProgram, 0, "outColor" );	
	//glBindAttribLocation( shaderProgram, 1, "position" );
		
	GLint status = 0;
	glLinkProgram( shaderProgram );
	glGetProgramiv( shaderProgram, GL_LINK_STATUS, &status );
	if(status == GL_FALSE) {
		printf( "[DEBUG] Linking Program [FAILED]\n");
		char buffer[512];
		glGetProgramInfoLog( shaderProgram, 512, NULL, buffer );
		printf( "[DEBUG] Linking Program Log: \n\n%s\n", buffer );
		return -1;
	}
	else
		printf( "[DEBUG] Linking Program [OK]\n");

	glUseProgram( shaderProgram );
	checkErrors("glUseProgram()");	
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	/*
	GLint uniColor = glGetUniformLocation( shaderProgram, "triangleColor" );
	checkErrors( "glGetUniformLocation()");
	glUniform3f( uniColor, 1.0f, 0.0f, 0.0f );
	checkErrors( "glUniform3f()" );
	*/
	SDL_Event windowEvent;
	while( true )
	{
			
		while((err = glGetError()) != GL_NO_ERROR)
			std::cout << "[DEBUG] OpenGL Error in MainLoop: " << err << std::endl;
	
		if( SDL_PollEvent( &windowEvent ) )
		{
			if ( windowEvent.type == SDL_QUIT ) break;
			if ( windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE ) break;
		}
		Draw( shaderProgram );
		SDL_GL_SwapWindow(window);
	}
		
	glDeleteProgram( shaderProgram );
	//glDeleteShader( fragmentShader );
	//glDeleteShader( vertexShader );	
	
	glDeleteBuffers( 1, &vbo );
	glUseProgram( 0 );
	
	glDeleteVertexArrays( 1, &vao );

	SDL_Quit();
	return 0;
}

#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <ctime>

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"

#include "SOIL/SOIL.h"	

SDL_Window* window;
SDL_GLContext glcontext;

GLuint shaderProgram;

GLenum err;

GLuint vao;
GLuint vbo;
GLuint ebo;

const unsigned int textureNumber = 2;	
GLuint texturesArray[textureNumber];

std::string textureFileNames[textureNumber] = { "sample.png", "sample2.png" }; 

glm::mat4 model;

GLuint elements[] = {
	0, 1, 2, 
	2, 3, 0
};
	
// Rectangle - using two triangles w/ elements
float vertices[] = { 
//	Pos	      TexCoords   Color	
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Top left 
	 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top right
	 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom right
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f  // Bottom left
};

// Shaders
const std::string vertexShaderSource(
	"#version 430\n"
	"layout(location = 0) in vec2 position;\n"
	"layout(location = 1) in vec2 texcoord;\n"
	"layout(location = 2) in vec3 color;\n"
	"out vec3 Color;\n"
	"out vec2 Texcoord;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 proj;\n"
	"void main() {\n"
		"Color = color;\n"
		"Texcoord = texcoord;\n"
		"gl_Position = proj * view * model * vec4( position, 0.0, 1.0f );\n"
	"}\n"
);	

const std::string fragmentShaderSource(
	"#version 430\n"
	"in vec3 Color;\n"
	"in vec2 Texcoord;\n"
	"out vec4 outColor;\n"
	"uniform sampler2D texKitten;\n"
	"uniform sampler2D texPuppy;\n"
	"void main() {\n"
		"outColor = mix( texture( texKitten, Texcoord ), texture( texPuppy, Texcoord ), 0.5 );\n"
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

void CleanUp()	
{
	for( unsigned int i = 0; i < textureNumber; ++i ) 
	{
		glDeleteTextures( 1, &texturesArray[i] );
		checkErrors( "glDeleteTextures()" );
	}

	glDeleteProgram( shaderProgram );
	//glDeleteShader( fragmentShader );
	//glDeleteShader( vertexShader );	
	
	glDeleteBuffers( 1, &vbo );
	glUseProgram( 0 );
	
	glDeleteVertexArrays( 1, &vao );
}

void LoadTexture(std::string file, unsigned int texNum )
{
	glActiveTexture( GL_TEXTURE0 + texNum );
	glBindTexture( GL_TEXTURE_2D, texturesArray[texNum] );
	checkErrors( "glBindTexture()" );
	
	int width, height;	
	unsigned char* image = nullptr;
	image = SOIL_load_image( file.c_str(), &width, &height, 0, SOIL_LOAD_RGB );
	if( image == nullptr )
	{	
		std::cout << "[DEBUG] Loading Texture: " << file << " [FAILED]"<< std::endl;	
	}
	else
		std::cout << "[DEBUG] Loading Texture: " << file << " [OK]"<< std::endl;	

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	checkErrors( "glTexImage2D() " );
	SOIL_free_image_data( image );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
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

void Draw(GLuint shaderProgram, GLint uniTrans)
{
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	
		glClear( GL_COLOR_BUFFER_BIT );
			
		//glUseProgram( shaderProgram );
		//checkErrors("glUseProgram()");	
		//glBindBuffer( GL_ARRAY_BUFFER, vbo );
		
		// Linking vertex data and attributes
		glEnableVertexAttribArray( 0 );	
		checkErrors("glEnableVertexAttribArray( index = 0 )");
		glEnableVertexAttribArray( 1 );
		checkErrors("glEnableVertexAttribArray( index = 1 )");
		glEnableVertexAttribArray( 2 );
		checkErrors("glEnableVertexAttribArray( index = 2 )");

		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0 );
		checkErrors("glVertexAttribPointer( index = 0 )");
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)( 2*sizeof(float) ) );
		checkErrors("glVertexAttribPointer( index = 1 )");
		glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)( 5*sizeof(float) ) );
		checkErrors("glVertexAttribPointer( index = 2 )");
		
		model = glm::rotate( model, ( (float)clock() / (float)CLOCKS_PER_SEC * 180.0f ) / 5, glm::vec3( 0.0, 0.0f, 1.0f ) ); 

		glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr( model ) );
		checkErrors( "glUnifromMatrix4fv()" );

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
	shaderProgram = glCreateProgram();
	checkErrors("glCreateProgram()");
	
	glAttachShader( shaderProgram, CreateShader( vertexShaderSource, GL_VERTEX_SHADER ) );
	glAttachShader( shaderProgram, CreateShader( fragmentShaderSource, GL_FRAGMENT_SHADER ) );

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
	
	glGenTextures( textureNumber, texturesArray );
	checkErrors( "glGenTextures()" );
	for( unsigned int i = 0; i < textureNumber; ++i)
	{
		LoadTexture( textureFileNames[i], i );
	}	
	
	glUniform1i( glGetUniformLocation( shaderProgram, "texKitten" ), 0 );
	checkErrors( "glUniform1i()" );
	glUniform1i( glGetUniformLocation( shaderProgram, "texPuppy" ), 1 );
	checkErrors( "glUniform1i()" );
	
	glm::mat4 view = glm::lookAt(
		glm::vec3( 1.2f, 1.2f, 1.2f ),
		glm::vec3( 0.0f, 0.0f, 0.0f ),
		glm::vec3( 0.0f, 0.0f, 1.0f )
	);

	glm::mat4 proj = glm::perspective( 45.0f, 800.0f / 600.0f, 1.0f, 10.0f );
	
	GLint uniModel = glGetUniformLocation( shaderProgram, "model" );	
	GLint uniView = glGetUniformLocation( shaderProgram, "view" );
	GLint uniProj = glGetUniformLocation( shaderProgram, "proj" );

	glUniformMatrix4fv( uniView, 1, GL_FALSE, glm::value_ptr( view ) );
	glUniformMatrix4fv( uniProj, 1, GL_FALSE, glm::value_ptr( proj ) );

	/*
	trans = glm::rotate( trans, 180.0f, glm::vec3( 0.0, 0.0f, 1.0f ) ); 
	glm::vec4 result = trans * glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );

	glUniformMatrix4fv( glGetUniformLocation( shaderProgram, "trans" ), 1, GL_FALSE, glm::value_ptr( trans ) );
	checkErrors( "glUnifromMatrix4fv()" );
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
		Draw( shaderProgram, uniModel );
		SDL_GL_SwapWindow(window);
	}
	
	CleanUp();		

	SDL_Quit();
	return 0;
}

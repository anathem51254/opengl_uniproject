
#include "../headers/shaderprogram.h"

GLint 		uniModel;
GLint 		uniView;
GLint 		uniProj;
GLint 		uniColor;
GLint 		uniMVP;

unsigned int 	ShaderNumber = 2;

GLuint 		Shaders[2];

// Shaders
const 	std::string GenericVertexShaderSource(
	"#version 430\n"
	"layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec3 color;\n"
	"out vec3 Color;\n"
	//"uniform mat4 modelMatrix;\n"
	//"uniform mat4 viewMatrix;\n"
	//"uniform mat4 projMatrix;\n"
	"uniform mat4 MVP;\n"
	"uniform vec3 overrideColor;\n"
	"void main() {\n"
		"Color = overrideColor * color;\n"
		//"gl_Position = projMatrix * viewMatrix * modelMatrix * vec4( position, 1.0f );\n"
		"gl_Position = MVP * vec4( position, 1.0f );\n"
	"}\n"
);	

const 	std::string GenericFragmentShaderSource(
	"#version 430\n"
	"in vec3 Color;\n"
	"out vec4 outColor;\n"
	"void main() {\n"
		"outColor = vec4( Color, 1.0 );\n"
	"}\n"
);

SHADER_PROGRAM::SHADER_PROGRAM()
{
}

SHADER_PROGRAM::~SHADER_PROGRAM()
{
	glDeleteProgram(ShaderProgram);

	for(unsigned int i = 0; i < ShaderNumber; i++)
	{
		glDeleteShader(Shaders[i]);
	}
}


int SHADER_PROGRAM::DebugShaderProgram(GLint status)
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

void SHADER_PROGRAM::UpdateUniformModel(const glm::mat4 MVP)
{
	//glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(temp_modelMatrix));
	glUniformMatrix4fv(uniMVP, 1, GL_FALSE, &MVP[0][0]);
}

float SHADER_PROGRAM::ConvertColor(float rgb)
{
	return rgb / 255.0f;
}

void SHADER_PROGRAM::ChangeUniformColor(float r, float g, float b)
{
	r /= 255.0f;
	g /= 255.0f;
	b /= 255.0f;
	glUniform3f(uniColor, r, g, b);
}

void SHADER_PROGRAM::UseShaderProgram(const glm::mat4 MVP)
{
	glUseProgram(ShaderProgram);

	//glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	//glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	//glUniformMatrix4fv(uniMVP, 1, GL_FALSE, &MVP[0][0]);
	
}

GLuint SHADER_PROGRAM::CreateShader( const std::string &shaderSource, GLenum eShaderType )
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

int SHADER_PROGRAM::InitGenericShaders()
{
	int retn = 0;

	Shaders[0] = CreateShader(GenericVertexShaderSource, GL_VERTEX_SHADER);
	Shaders[1] = CreateShader(GenericFragmentShaderSource, GL_FRAGMENT_SHADER);

	ShaderProgram = glCreateProgram();
	//utils->CheckErrors("glCreateProgram()");

	for(unsigned int i = 0; i < ShaderNumber; i++)
	{
		glAttachShader(ShaderProgram, Shaders[i]);
	}

	GLint status = 0;

	glLinkProgram(ShaderProgram);
	retn = DebugShaderProgram(status);

	if(retn == 0)
	{
		uniModel = glGetUniformLocation(ShaderProgram, "modelMatrix");	
		//utils->CheckErrors("glGetUniformLocation(modelMatrix)");
		uniView = glGetUniformLocation(ShaderProgram, "viewMatrix");
		//utils->CheckErrors("glGetUniformLocation(viewMatrix)");
		uniProj = glGetUniformLocation(ShaderProgram, "projMatrix");
		//utils->CheckErrors("glGetUniformLocation(projMatrix)");

		uniColor = glGetUniformLocation(ShaderProgram, "overrideColor");
		//utils->CheckErrors("glGetUniformLocation(overrideColor)");
	}

	return retn;
}

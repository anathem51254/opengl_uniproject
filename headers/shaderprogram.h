#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "SOIL/SOIL.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SHADER_PROGRAM 
{
	public:

		SHADER_PROGRAM();
		~SHADER_PROGRAM();

		struct Color
		{
			float r;
			float g;
			float b;
		};


		void 	InitGenericShaders();
		GLuint	InitPhongShaders();

		void	UseShaderProgram(const glm::mat4 MVP, const GLuint shader);

		void	UpdateUniformModel(const glm::mat4 MVP);
		void	UpdateUniformModel(const glm::mat4 MVP, const glm::mat4 Normal);

		void	ChangeUniformColor(float r, float g, float b);

		float	ConvertColor(float rgb);

		void	BuildShaders();

	private:

		GLuint		GenericShaderProgram;
		GLuint		PhongShaderProgram;

		int		DebugShaderProgram(GLint status, GLuint ShaderProg);

		GLuint 		CreateShader(const std::string &shaderSource, GLenum eShaderType); 

};

#endif

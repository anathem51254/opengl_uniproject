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

		int		InitGenericShaders();

		void		UseShaderProgram(const glm::mat4 ViewMatrix, const glm::mat4 ProjectionMatrix);

		void		UpdateUniformModel(glm::mat4 temp_ModelMatrix);

		void		ChangeUniformColor(const float r, const float g, const float b);

	private:

		GLuint		ShaderProgram;


		int		DebugShaderProgram(GLint status);

		GLuint 		CreateShader(const std::string &shaderSource, GLenum eShaderType); 

};

#endif

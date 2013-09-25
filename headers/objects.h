#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdexcept>
#include <memory>

#include <string>
#include <stack>

#include <iostream>
#include <fstream>
#include <sstream>

#include <ctime>
#include <cmath>

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class OBJECTS 
{

	public:

		OBJECTS();
		~OBJECTS();

		GLuint VAOArray[2];

		GLuint CurrentVao;

		void InitBuffers();

		void BindObject(const int vao); 

		void DrawCube();

		void DrawFloor();

	private:


};

#endif

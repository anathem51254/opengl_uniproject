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

		GLuint VAOArray[6];

		GLuint CurrentVao;

		void BuildObjects();

		void BindObject(const int vao); 

		void DrawCube();

		void DrawCylinder();

		void DrawFloor();

	private:
		
		GLuint vbo;

		void InitBuffers();

		template <size_t N>
		void AddObjectToVAO(const int vao, const float (&ObjectVectices)[N]);

		template <size_t N>
		void GenCylinder(const float Radius, const float Height, const int Resolution, float (&Cylinder)[N]);

		template <size_t N>
		void GenCube(const float Width, const float Height, const float Depth, float (&Cube)[N]);

};

#endif

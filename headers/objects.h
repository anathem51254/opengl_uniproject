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

		GLuint VAOArray[10];

		GLuint CurrentVao;

		void BuildObjects();

		void BindObject(const int vao); 

		void DrawCube();

		void DrawCylinder();

		void DrawHalfCylinder_ONE();
		void DrawHalfCylinder_TWO();
		void DrawHalfCylinder_THREE();

		void DrawUnderBeamRound_ONE();
		void DrawUnderBeamRound_TWO();
		void DrawUnderBeamRound_THREE();

		void DrawLegs();

		void DrawLegs_ONE();
		void DrawLegs_TWO();
		void DrawLegs_THREE();

		void DrawLegSupport_ONE();
		void DrawLegSupport_TWO();
		void DrawLegSupport_THREE();


		void DrawCone();

		void DrawCircle();

		void DrawSquare();

	private:
		
		GLuint vbo;

		void InitBuffers();

		template <size_t N>
		void AddObjectToVAO(const int vao, const float (&ObjectVectices)[N]);

		template <size_t N>
		void GenCylinder(const float Radius, const float Height, const int Resolution, float (&Cylinder)[N]);

		template <size_t N>
		void GenHalfCylinder(const float Radius, const float Height, const int Resolution, float (&Cylinder)[N]);

		template <size_t N>
		void GenCone(const float Radius, const float Height, const int Resolution, float (&Cone)[N]);

		template <size_t N>
		void GenCircle(const float Radius, const float Height, const int Resolution, float (&Circle)[N]);

		template <size_t N>
		void GenCube(const float Width, const float Height, const float Depth, float (&Cube)[N]);

};

#endif

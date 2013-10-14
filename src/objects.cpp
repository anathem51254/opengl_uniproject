
#include "../headers/objects.h"

const float BaseCubeVertices[] = { 
//	 X	Y     Z     R     G	B     U     V	
	-1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,

	-1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,

	-1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

	 1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

	-1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-1.0f, -1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,

	-1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-1.0f,  1.0f,  1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f

};


OBJECTS::OBJECTS()
{
	
}

OBJECTS::~OBJECTS()
{
	glDeleteVertexArrays(5, VAOArray);
}

template <size_t N>
void OBJECTS::GenCube(const float Width, const float Height, const float Depth, float (&NewCube)[N])
{
	int j = 0;
	while(j < N)	
	{
		NewCube[j] = BaseCubeVertices[j] * Width;
		j++;
		NewCube[j] = BaseCubeVertices[j] * Height;
		j++;
		NewCube[j] = BaseCubeVertices[j] * Depth;
		j++;
		NewCube[j] = 0.5f;
		j++;
		NewCube[j] = 0.5f;
		j++;
		NewCube[j] = 0.5f;
		j++;
	}
}

template <size_t N>
void OBJECTS::GenCylinder(const float Radius, const float Height, const int Resolution, float (&Cylinder)[N])
{
	int j = 0;

	// bottom
	Cylinder[j] = 0.0f;
	j++;
	Cylinder[j] = 0.0f;
	j++;
	Cylinder[j] = 0.0f;
	j++;
	
	Cylinder[j] = 0.5f;
	j++;
	Cylinder[j] = 0.5f;
	j++;
	Cylinder[j] = 0.5f;
	j++;

	for(int i = 0; i < Resolution; i++)
	{
		Cylinder[j] = cos((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;
		Cylinder[j] = 0.0f;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * 2 * M_PI) * Radius;
		j++;
	
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
	}

	// top
	Cylinder[j] = 0.0f;
	j++;
	Cylinder[j] = Height;
	j++;
	Cylinder[j] = 0.0f;
	j++;
	
	Cylinder[j] = 0.5f;
	j++;
	Cylinder[j] = 0.5f;
	j++;
	Cylinder[j] = 0.5f;
	j++;

	for(int i = 0; i < Resolution; i++)
	{
		Cylinder[j] = cos((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;
		Cylinder[j] = Height;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * 2 * M_PI) * Radius;
		j++;

		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
	}

	for(int i = 0; i < Resolution; i++) 
	{
		Cylinder[j] = cos((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;
		Cylinder[j] = 0.0f;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * 2 * M_PI) * Radius;
		j++;

		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;

		Cylinder[j] = cos((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;
		Cylinder[j] = Height;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;

		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
	}
/*
	int l = 0;
	while(l < 156)
	{
		std::stringstream str;
		int u = l;
		while(u < (l+6))	
		{
			str << Cylinder[u] << " ";

			u++;
		}
		std::cout << "[DEBUG] Cylinder: " << str.str() << std::endl;
		l = u;
	}
*/
}

template <size_t N>
void OBJECTS::AddObjectToVAO(const int vao, const float (&ObjectVectices)[N])
{
	glBindVertexArray(VAOArray[vao]);	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ObjectVectices), ObjectVectices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);	
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)( 3*sizeof(float)));
}

void OBJECTS::BuildObjects()
{
	glGenVertexArrays(5, VAOArray);

	float SixteenXEightXSixtyFourCube[216];
	GenCube(16.0f, 8.0f, 64.0f, SixteenXEightXSixtyFourCube);

	float EightXThirtyTwoXEightCube[216];
	GenCube(8.0f, 32.0f, 8.0f, EightXThirtyTwoXEightCube);
	
	float SixteenXFourXEightCube[216];
	GenCube(16.0f, 4.0f, 8.0f, SixteenXFourXEightCube);
	
	float TwoXThirtyTwoXTwo[216];
	GenCube(2.0f, 32.0f, 2.0f, TwoXThirtyTwoXTwo);
	
	float FourXTwoXTwo[216];
	GenCube(4.0f, 2.0f, 2.0f, FourXTwoXTwo);

	float Cylinder[156];
	GenCylinder(10.0f, 50.0f, 6.0f, Cylinder);

	AddObjectToVAO(0, SixteenXEightXSixtyFourCube);
	AddObjectToVAO(1, EightXThirtyTwoXEightCube);
	AddObjectToVAO(2, SixteenXFourXEightCube);
	AddObjectToVAO(3, TwoXThirtyTwoXTwo);
	AddObjectToVAO(4, FourXTwoXTwo);

	AddObjectToVAO(5, Cylinder);
}


void OBJECTS::BindObject(const int vao)
{
	CurrentVao = VAOArray[vao];
	glBindVertexArray(VAOArray[vao]);
}

void OBJECTS::DrawCube()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void OBJECTS::DrawCylinder()
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
	glDrawArrays(GL_TRIANGLE_FAN, 7, 14);
	glDrawArrays(GL_TRIANGLE_STRIP, 14, 26);
}

void OBJECTS::DrawFloor()
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

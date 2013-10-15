
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

const float BaseSquareVectices[] = {

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


	for(int i = 0; i <= Resolution; i++)
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

	std::cout << "[DEBUG] Cylinder Sides: " << j << std::endl;

	
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

	for(int i = 0; i <= Resolution; i++)
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

	std::cout << "[DEBUG] Cylinder Sides: " << j << std::endl;


	for(int i = 0; i <= Resolution; i++) 
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

	std::cout << "[DEBUG] Cylinder Sides: " << j << std::endl;
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
void OBJECTS::GenHalfCylinder(const float Radius, const float Height, const int Resolution, float (&Cylinder)[N])
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


	for(int i = 0; i <= Resolution; i++)
	{
		Cylinder[j] = cos((float)i/Resolution * M_PI) * Radius;
	    	j++;
		Cylinder[j] = 0.0f;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * M_PI) * Radius;
		j++;
	
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
	}

	std::cout << "[DEBUG] Half Cylinder Sides: " << j << std::endl;

	
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

	for(int i = 0; i <= Resolution; i++)
	{
		Cylinder[j] = cos((float)i/Resolution * M_PI) * Radius;
	    	j++;
		Cylinder[j] = Height;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * M_PI) * Radius;
		j++;

		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
	}

	std::cout << "[DEBUG] Half Cylinder Sides: " << j << std::endl;

	for(int i = 0; i <= Resolution; i++) 
	{
		Cylinder[j] = cos((float)i/Resolution * M_PI) * Radius;
	    	j++;
		Cylinder[j] = 0.0f;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * M_PI) * Radius;
		j++;

		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;

		Cylinder[j] = cos((float)i/Resolution * M_PI) * Radius;
	    	j++;
		Cylinder[j] = Height;
	    	j++;
		Cylinder[j] = sin((float)i/Resolution * M_PI) * Radius;
	    	j++;

		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
		Cylinder[j] = 0.5f;
		j++;
	}

	std::cout << "[DEBUG] Half Cylinder Sides: " << j << std::endl;
}

template <size_t N>
void OBJECTS::GenCone(const float Radius, const float Height, const int Resolution, float (&Cone)[N])
{
	int j = 0;
	
	// bottom
	Cone[j] = 0.0f;
	j++;
	Cone[j] = Height;
	j++;
	Cone[j] = 0.0f;
	j++;

	Cone[j] = 0.5f;
	j++;
	Cone[j] = 0.5f;
	j++;
	Cone[j] = 0.5f;
	j++;
	
	for(int i = 0; i <= Resolution; i++)
	{
		Cone[j] = cos((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;
		Cone[j] = 0.0f;
	    	j++;
		Cone[j] = sin((float)i/Resolution * 2 * M_PI) * Radius;
		j++;

		Cone[j] = 0.5f;
		j++;
		Cone[j] = 0.5f;
		j++;
		Cone[j] = 0.5f;
		j++;
	}

	std::cout << "[DEBUG] Cone Sides: " << j << std::endl;
}

template <size_t N>
void OBJECTS::GenCircle(const float Radius, const float Height, const int Resolution, float (&Circle)[N])
{
	int j = 0;
	
	// bottom
	Circle[j] = 0.0f;
	j++;
	Circle[j] = 0.0f;
	j++;
	Circle[j] = 0.0f;
	j++;

	Circle[j] = 0.5f;
	j++;
	Circle[j] = 0.5f;
	j++;
	Circle[j] = 0.5f;
	j++;
	
	for(int i = 0; i <= Resolution; i++)
	{
		Circle[j] = cos((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;
		Circle[j] = 0.0f;
	    	j++;
		Circle[j] = sin((float)i/Resolution * 2 * M_PI) * Radius;
		j++;

		Circle[j] = 0.5f;
		j++;
		Circle[j] = 0.5f;
		j++;
		Circle[j] = 0.5f;
		j++;
	}

	// bottom
	Circle[j] = 0.0f;
	j++;
	Circle[j] = Height;
	j++;
	Circle[j] = 0.0f;
	j++;

	Circle[j] = 0.5f;
	j++;
	Circle[j] = 0.5f;
	j++;
	Circle[j] = 0.5f;
	j++;
	
	for(int i = 0; i <= Resolution; i++)
	{
		Circle[j] = cos((float)i/Resolution * 2 * M_PI) * Radius;
	    	j++;
		Circle[j] = Height;
	    	j++;
		Circle[j] = sin((float)i/Resolution * 2 * M_PI) * Radius;
		j++;

		Circle[j] = 0.5f;
		j++;
		Circle[j] = 0.5f;
		j++;
		Circle[j] = 0.5f;
		j++;
	}

	std::cout << "[DEBUG] Circle Sides: " << j << std::endl;
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
	glGenVertexArrays(7, VAOArray);

	float Beams[216];
	GenCube(4.0f, 2.0f, 48.0f, Beams);

	float Rails[216];
	GenCube(2.0f, 16.0f, 2.0f, Rails);
	
	//float Legs[2340];
	//GenCylinder(4.0f, 64.0f, 96.0f, Legs);

	float Legs[1188];
	GenCylinder(4.0f, 64.0f, 48.0f, Legs);
	
	//float Cylinder[156];
	//GenCylinder(4.0f, 64.0f, 5.0f, Cylinder);

	float Cone[42];
	GenCone(10.0f, 50.0f, 5.0f, Cone);

	float HalfCylinder[132];
	GenHalfCylinder(4.0f, 50.0f, 4.0f, HalfCylinder);

	float Circle[84];
	GenCircle(10.0f, 50.0f, 5.0f, Circle);
	

	AddObjectToVAO(0, Beams);

	AddObjectToVAO(1, Rails);

	AddObjectToVAO(2, Legs);
	
	AddObjectToVAO(3, BaseSquareVectices);

	AddObjectToVAO(4, HalfCylinder);

	AddObjectToVAO(5, Circle);

	AddObjectToVAO(6, Cone);
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


void OBJECTS::DrawLegs_ONE()
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 50);
}

void OBJECTS::DrawLegs_TWO()
{
	glDrawArrays(GL_TRIANGLE_FAN, 50, 100);
}

void OBJECTS::DrawLegs_THREE()
{
	glDrawArrays(GL_TRIANGLE_STRIP, 100, 198);
}

/* High Res
void OBJECTS::DrawLegs()
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 196);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 196, 390);
}
*/

void OBJECTS::DrawCylinder()
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 14);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 14, 26);
}

void OBJECTS::DrawHalfCylinder_ONE()
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
}

void OBJECTS::DrawHalfCylinder_TWO()
{
	glDrawArrays(GL_TRIANGLE_FAN, 6, 12);
}

void OBJECTS::DrawHalfCylinder_THREE()
{
	glDrawArrays(GL_TRIANGLE_STRIP, 12, 22);
}




void OBJECTS::DrawCone()
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
}

void OBJECTS::DrawCircle()
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
}

void OBJECTS::DrawSquare()
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

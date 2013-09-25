
#include "../headers/objects.h"

// Cube 
const float CubeVertices[] = { 

//	 X	Y     Z     R     G	B     U     V	
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.5f, //0.0f, 1.0f

};

const float FloorVertices[] = {
	
	// floor
	-1.2f, -1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //0.0f, 1.0f,
	 1.2f, -1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //1.0f, 1.0f,
	 1.2f,  1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //1.0f, 0.0f,
	 1.2f,  1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //1.0f, 0.0f,
	-1.2f,  1.2f, -0.5f, 0.0f, 0.0f, 0.0f, //0.0f, 0.0f,
	-1.2f, -1.2f, -0.5f, 0.0f, 0.0f, 0.0f //0.0f, 1.0f
};

OBJECTS::OBJECTS()
{
	
}

OBJECTS::~OBJECTS()
{
	glDeleteVertexArrays(2, VAOArray);
}


void OBJECTS::InitBuffers()
{
	GLuint vbo;
	
	glGenVertexArrays(2, VAOArray);

	//*******************************************//
	//		Cube Buffer		     //
	//*******************************************//
	glBindVertexArray(VAOArray[0]);	
	glGenBuffers( 1, &vbo);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	glBufferData( GL_ARRAY_BUFFER, sizeof( CubeVertices ), CubeVertices, GL_STATIC_DRAW );

	// Linking vertex data and vertex array attributes
	glEnableVertexAttribArray( 0 );	
	//utils->CheckErrors("glEnableVertexAttribArray( index = 0 )");
	glEnableVertexAttribArray( 1 );
	//utils->CheckErrors("glEnableVertexAttribArray( index = 1 )");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	//utils->CheckErrors("glVertexAttribPointer( index = 0 )");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)( 3*sizeof(float)));
	//utils->CheckErrors("glVertexAttribPointer( index = 1 )");


	//*******************************************//
	//		Floor Buffer		     //
	//*******************************************//
	glBindVertexArray(VAOArray[1]);	
	glGenBuffers( 1, &vbo);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	glBufferData( GL_ARRAY_BUFFER, sizeof( FloorVertices ), FloorVertices, GL_STATIC_DRAW );

	// Linking vertex data and vertex array attributes
	glEnableVertexAttribArray( 0 );	
	//utils->CheckErrors("glEnableVertexAttribArray( index = 0 )");
	glEnableVertexAttribArray( 1 );
	//utils->CheckErrors("glEnableVertexAttribArray( index = 1 )");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	//utils->CheckErrors("glVertexAttribPointer( index = 0 )");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)( 3*sizeof(float)));
	//utils->CheckErrors("glVertexAttribPointer( index = 1 )");

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

void OBJECTS::DrawFloor()
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

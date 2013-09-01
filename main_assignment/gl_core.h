#ifndef GL_CORE_H
#define GL_CORE_H

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL_CORE {
	public:

		static void Init();
	
		static void CleanUp();

		static void LoadTexture( std::string file, unsigned int texNum );
		
		static GLuint CreateShader( const std::string &shaderSource, GLenum eShaderType ); 

		static void InitVertexObjects();

		static void InitElementObjects();
		
		


	private:

};

#endif

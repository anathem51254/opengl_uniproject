
#include "../headers/shaderprogram.h"

GLint 		uniModel;
GLint 		uniView;
GLint 		uniProj;
GLint 		uniColor;
GLint 		uniMVP;
GLint		uniNormal;

std::array<GLuint, 3> Shaderprograms;

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

const 	std::string TextureGenericVertexShaderSource(
	"#version 430\n"
	//"layout(location = 0) in vec4 position;\n"
	"layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec3 color;\n"
	//"layout(location = 2) in vec2 texturecoords;\n"	
	"out vec3 Color;\n"
	"uniform mat4 modelMatrix;\n"
	"uniform mat4 viewMatrix;\n"
	"uniform mat4 projMatrix;\n"
	"uniform mat4 normalMatrix;\n"
	"uniform vec3 overrideColor;\n"
	"void main() {\n"
		"Color = overrideColor * color;\n"
		"gl_Position = (projMatrix * viewMatrix * modelMatrix) * vec4(position, 1.0f);\n"
	"}\n"
);	

const 	std::string TextureGenericFragmentShaderSource(
	"#version 430\n"
	"in vec3 Color;\n"
	"out vec4 outColor;\n"
	"void main() {\n"
		"outColor = vec4( Color, 1.0 );\n"
	"}\n"
);

/* From super bible - doesnt compile
const	std::string PhongVectexShaderSource(
	"#version 430\n"
	"layout(location = 0) in vec3 position;\n"
	"layout(location = 1) in vec3 normal;\n"
	"uniform mat4 modelMatrix;\n"
	"uniform mat4 viewMatrix;\n"
	"uniform mat4 projMatrix;\n"
	"out VS_OUT {\n"
		"vec3 N;\n"
		"vec3 L;\n"
		"vec3 V;\n"
	"} vs_out;\n"
	"uniform vec3 light_pos = vec3(100.0, 100.0, 100.0);\n"
	"void main(void) {\n"
		"vec4 P = modelMatrix * vec4(position, 1.0);\n"
		"vs_out.N = mat3(modelMatrix) * normal;\n"
		"vs_out.L = light_pos - P.xyz;\n"
		"vs_out.V = -P.xyz;\n"
		"gl_Position = projMatrix * P;\n"
	"}\n"
);
*/

const	std::string PhongVertexShaderSource(
	"#version 430\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 normal;\n"
	"layout (location = 2) in vec3 color;\n"
	"uniform mat4 modelMatrix;\n"
	"uniform mat4 viewMatrix;\n"
	"uniform mat4 projMatrix;\n"
	"uniform mat4 normalMatrix;\n"
	"uniform vec3 overrideColor;\n"
	"out vec4 vpeye;\n"
	"out vec4 vneye;\n"
	"out vec3 Color;\n"
	"void main() {\n"
		"Color = overrideColor * color;\n"
		"vpeye = (modelMatrix * viewMatrix) * vec4(position, 1.0);\n"
		"vneye = vec4((normalMatrix * vec4(normal, 0.0)));\n"
		"gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);\n"
	"}\n"
);


/* From super bible - doesnt compile
const 	std::string PhongFragmentShaderSource(
	"#version 430\n"
	"layout(location = 0) out vec4 color;\n"
	"in VS_OUT {\n"
		"vec3 N;\n"
		"vec3 L;\n"
		"vec3 V;\n"
	"} fs_in;\n"
	"uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);\n"
	"uniform vec3 specular_albedo = vec3(0.5, 0.2, 0.7);\n"
	"uniform float specular_power = 128.0;\n"
	"void main(void) {\n"
		"vec3 N = normalize(fs_in.N);\n"
		"vec3 L = normalize(fs_in.L);\n"
		"vec3 V = normalize(fs_in.V);\n"
		"vec3 R = reflect(-L, N);\n"
		"vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;\n"
		"vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;\n"
		"color = vec4(diffuse + specular, 1.0);\n"
	"}\n"
);
*/

const 	std::string PhongFragmentShaderSource(
	"#version 430\n"
	"in vec4 vpeye;\n"
	"in vec4 vneye;\n"
	"in vec3 Color;\n"
	"uniform vec4 lightPosition;\n"
	"uniform vec4 kAmbient;\n"
	"uniform vec4 kDiffuse;\n"
	"uniform vec4 kSpecular;\n"
	"uniform float nSpecularPow;\n"
	"uniform vec4 diffuseColor;\n"
	"layout (location = 0) out vec4 fragColor;\n"
	"void main() {\n"
		"vec4 n_eye = normalize(vneye);\n"
		"vec4 s_eye = normalize(lightPosition - vpeye);\n"
		"vec4 v_eye = normalize(-vpeye);\n"
		"vec4 h_eye = normalize(v_eye + vneye);\n"
		//vec4 r_eye = normalize(-s_eye, vneye);\n"
		"vec4 Ia = vec4(0.1, 0.1, 0.1, 1) * kAmbient;\n"
		"vec4 Id = diffuseColor * kDiffuse * max(dot(s_eye, n_eye), 0.0);\n"
		"vec4 Is = vec4(1, 1, 1, 1) * kSpecular * pow(max(dot(h_eye, v_eye), 0), nSpecularPow);\n"
		"fragColor = (Color, 1.0) * (Ia + Id + Is);\n"
		"}\n"
);

SHADER_PROGRAM::SHADER_PROGRAM()
{
}

SHADER_PROGRAM::~SHADER_PROGRAM()
{
	glDeleteProgram(Shaderprograms[0]);
	glDeleteProgram(Shaderprograms[1]);
	glDeleteProgram(Shaderprograms[2]);

	/*for(unsigned int i = 0; i < ShaderNumber; i++)
	{
		glDeleteShader(Shaders[i]);
	}
	*/
}


int SHADER_PROGRAM::DebugShaderProgram(GLint status, GLuint ShaderProg)
{
	glGetProgramiv(ShaderProg, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		std::cout << "[DEBUG] Linking Program [FAILED]\n" << std::endl;
		
		GLint infoLogLength;
		glGetProgramiv(ShaderProg, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(ShaderProg, infoLogLength, NULL, strInfoLog);

		std::cout << "[DEBUG] Linking Program Log: \n\n" << strInfoLog << std::endl;

		delete[] strInfoLog;

		return -1;
	}
	std::cout << "[DEBUG] Linking Program [OK]\n" << std::endl;

	return 0;
}

void SHADER_PROGRAM::UpdateTextureGenericShaderUniform(const glm::mat4 model, const glm::mat4 view, const glm::mat4 proj, const glm::mat4 normal)
{
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(uniNormal, 1, GL_FALSE, glm::value_ptr(normal));
}

void SHADER_PROGRAM::UpdateUniformModel(const glm::mat4 MVP, const glm::mat4 normal)
{
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(uniView, 1, GL_FALSE, &MVP[1][1]);
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, &MVP[2][2]);
	glUniformMatrix4fv(uniNormal, 1, GL_FALSE, &glm::mat3(normal)[0][0]);
}

void SHADER_PROGRAM::UpdateUniformModel(const glm::mat4 MVP)
{
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

void SHADER_PROGRAM::UseShaderProgram(const GLuint shader)
{
	switch(shader)
	{
		case 0:
			glUseProgram(GenericShaderProgram);
			break;
		case 1:
			glUseProgram(TextureGenericShaderProgram);
			break;
		//glUseProgram(PhongShaderProgram);
	}
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

void SHADER_PROGRAM::InitGenericShaders()
{
	GLuint vert = CreateShader(GenericVertexShaderSource, GL_VERTEX_SHADER);
	GLuint frag = CreateShader(GenericFragmentShaderSource, GL_FRAGMENT_SHADER);

	GenericShaderProgram = glCreateProgram();
	//utils->CheckErrors("glCreateProgram()");

	glAttachShader(GenericShaderProgram, vert);
	glAttachShader(GenericShaderProgram, frag);

	GLint status = 0;

	glLinkProgram(GenericShaderProgram);
	DebugShaderProgram(status, GenericShaderProgram);

		uniModel = glGetUniformLocation(GenericShaderProgram, "modelMatrix");	
		//utils->CheckErrors("glGetUniformLocation(modelMatrix)");
		uniView = glGetUniformLocation(GenericShaderProgram, "viewMatrix");
		//utils->CheckErrors("glGetUniformLocation(viewMatrix)");
		uniProj = glGetUniformLocation(GenericShaderProgram, "projMatrix");
		//utils->CheckErrors("glGetUniformLocation(projMatrix)");

		uniColor = glGetUniformLocation(GenericShaderProgram, "overrideColor");
		//utils->CheckErrors("glGetUniformLocation(overrideColor)");
}

GLuint SHADER_PROGRAM::InitPhongShaders()
{
	GLuint vert = CreateShader(PhongVertexShaderSource, GL_VERTEX_SHADER);
	GLuint frag = CreateShader(PhongFragmentShaderSource, GL_FRAGMENT_SHADER);

	PhongShaderProgram = glCreateProgram();
	//utils->CheckErrors("glCreateProgram()");

	glAttachShader(PhongShaderProgram, vert);
	glAttachShader(PhongShaderProgram, frag);

	GLint status = 0;

	glLinkProgram(PhongShaderProgram);
	DebugShaderProgram(status, PhongShaderProgram);

	uniModel = glGetUniformLocation(PhongShaderProgram, "modelMatrix");	
	//utils->CheckErrors("glGetUniformLocation(modelMatrix)");
	uniView = glGetUniformLocation(PhongShaderProgram, "viewMatrix");
	//utils->CheckErrors("glGetUniformLocation(viewMatrix)");
	uniProj = glGetUniformLocation(PhongShaderProgram, "projMatrix");
	//utils->CheckErrors("glGetUniformLocation(projMatrix)");

	uniNormal = glGetUniformLocation(PhongShaderProgram, "normal");

	uniColor = glGetUniformLocation(PhongShaderProgram, "overrideColor");
	//utils->CheckErrors("glGetUniformLocation(overrideColor)");
		
/*		
	"uniform vec4 lightPosition;\n"
	"uniform vec4 kAmbient;\n"
	"uniform vec4 kDiffuse;\n"
	"uniform vec4 kSpecular;\n"
	"uniform float nSpecularPow;\n"
	"uniform vec4 diffuseColor;\n"
*/
	return PhongShaderProgram;
}

GLuint SHADER_PROGRAM::InitTextureGenericShaders()
{
	GLuint vert = CreateShader(TextureGenericVertexShaderSource, GL_VERTEX_SHADER);
	GLuint frag = CreateShader(TextureGenericFragmentShaderSource, GL_FRAGMENT_SHADER);

	TextureGenericShaderProgram = glCreateProgram();

	glAttachShader(TextureGenericShaderProgram, vert);
	glAttachShader(TextureGenericShaderProgram, frag);

	GLint status = 0;

	glLinkProgram(TextureGenericShaderProgram);
	DebugShaderProgram(status, TextureGenericShaderProgram);

	uniModel = glGetUniformLocation(TextureGenericShaderProgram, "modelMatrix");	
	//utils->CheckErrors("glGetUniformLocation(modelMatrix)");
	uniView = glGetUniformLocation(TextureGenericShaderProgram, "viewMatrix");
	//utils->CheckErrors("glGetUniformLocation(viewMatrix)");
	uniProj = glGetUniformLocation(TextureGenericShaderProgram, "projMatrix");
	//utils->CheckErrors("glGetUniformLocation(projMatrix)");

	uniNormal = glGetUniformLocation(TextureGenericShaderProgram, "normal");

	uniColor = glGetUniformLocation(TextureGenericShaderProgram, "overrideColor");
	//utils->CheckErrors("glGetUniformLocation(overrideColor)");
	
	return TextureGenericShaderProgram;
}

void SHADER_PROGRAM::BuildShaders()
{
	//InitGenericShaders();
	InitTextureGenericShaders();
	//InitPhongShaders();
}

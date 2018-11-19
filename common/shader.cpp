#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include "shader.h"


GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path){
	// create the shaders
	GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the vertex shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		std::cerr << "ERROR: Impossible to open " << vertex_file_path << std::endl;
		return 0;
	}

	// Read the fragment shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}else{
		std::cerr << "ERROR: Impossible to open " << fragment_file_path << std::endl;
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile the vertex shader
	std::cout << "Compiling shader: " << vertex_file_path << std::endl;
	char const *VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderId, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderId);

	// Check if it compiled
	glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderId, GL_INFO_LENGTH, &InfoLogLength);
	if( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cerr << "ERROR: " << &VertexShaderErrorMessage[0] << std::endl;
	}

	// Compile the fragment shader
	std::cout << "Compiling shader: " << fragment_file_path << std::endl;
	char const *FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderId, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderId);

	// Check if it compiled
	glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderId, GL_INFO_LENGTH, &InfoLogLength);
	if( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cerr << "ERROR: " << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the shader programs
	std::cout << "Linking the program" << std::endl;
	GLuint ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);

	// Check the linked program
	glGetProgramiv(ProgramId, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cerr << "ERROR: " << &ProgramErrorMessage[0] << std::endl;
	}

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(VertexShaderId);
	glDeleteShader(FragmentShaderId);

	return ProgramId;
}

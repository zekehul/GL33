// Include headers
// standard ones
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/glew.h> //GLExtensionWrangler
#include <GLFW/glfw3.h> //
#include <glm/glm.hpp>
#include "../common/shader.h"

using namespace glm;

int main(){
	glewExperimental = true;
	if( !glfwInit() ){
		std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window;
	window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
	if( window == NULL ){
		std::cerr << "ERROR: Failed to open GLFW window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if( glewInit() != GLEW_OK ){
		std::cerr << "ERROR: Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// create the vertex array object
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programId = LoadShaders("vshader.glsl", "fshader.glsl");

	//triangle vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	// vertex buffer id
	GLuint vertexbuffer;
	// generate 1 buffer, save id in `vertexbuffer`
	glGenBuffers(1, &vertexbuffer);
	// bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// send the vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do {
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Drawing code
		// 1st attribute buffer : vertices
		glUseProgram(programId);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,		// attribute 0. No idea why 0, but it must match the layout in the shader		
			3,		// size
			GL_FLOAT,	// type
			GL_FALSE,	// normalized?
			0,		// stride
			(void*)0	// array buffer offset
		);
		// draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while ( (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(window) == 0) );

	return 0;
}

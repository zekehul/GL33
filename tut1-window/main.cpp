// Include headers
// standard ones
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/glew.h> //GLExtensionWrangler
#include <GLFW/glfw3.h> //
#include <glm/glm.hpp>

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

	do {
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
		// Drawing code
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while ( (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(window) == 0) );
}

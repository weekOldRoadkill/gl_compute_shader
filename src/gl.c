// Headers
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "types.h"
#include "utils.h"


// File Variables
static uint8_t initialized = 0x00;
static char buff1[0x00020000];
static GLFWwindow* window;


// GL Initialization Function
void gl_init() {
	// Setup
	if(initialized) {
		error("GL already initialized, cannot initialize again.");
	}

	if(!glfwInit()) error("GLFW failed to initialize.");

	glfwWindowHint(GLFW_VISIBLE, 0x00);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0x04);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0x06);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(0x01, 0x01, "", 0x00, 0x00);
	if(!window) error("GLFW failed to create an OpenGL context.");

	glfwMakeContextCurrent(window);
	if(glewInit()) error("GLEW failed to initialize.");


	// De-initialization
	info("GL initialized successfully.");
	initialized = 0x01;
}


// GL De-initialization Function
void gl_deinit() {
	// Setup
	if(!initialized) error("GL not initialized, cannot de-initialize.");

	glfwTerminate();

	info("GL de-initialized successfully.");


	// De-initialization
	initialized = 0x00;
}


// Compile Shader Function
void compile_shader(uint32_t shader, char* src) {
	glShaderSource(shader, 0x01, (const char**) &src, 0x00);
	glCompileShader(shader);

	int32_t temp;
	buff1[0x00] = 0x00;
	glGetShaderInfoLog(shader, sizeof(buff1), 0x00, buff1);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &temp);

	if(temp) {
		info("Shader compiled successfully.");
		if(buff1[0x00]) {
			info("Compile Info:");
			puts(buff1);
		}
	} else {
		info("Compile Info:");
		puts(buff1);
		error("Shader failed to compile.");
	}
}


// Link Program Function
void link_program(uint32_t program) {
	glLinkProgram(program);

	int32_t temp;
	buff1[0x00] = 0x00;
	glGetProgramInfoLog(program, sizeof(buff1), 0x00, buff1);
	glGetProgramiv(program, GL_LINK_STATUS, &temp);

	if(temp) {
		info("Program linked successfully.");
		if(buff1[0x00]) {
			info("Link Info:");
			puts(buff1);
		}
	} else {
		info("Link Info:");
		puts(buff1);
		error("Program failed to link.");
	}
}
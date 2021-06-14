// Macros
#define THREAD_COUNT	0x10


// Headers
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <pthread.h>

#include "gl.h"
#include "image.h"
#include "types.h"
#include "utils.h"


// File Variables
static char buff1[0x00020000];
static image_t current_image;


// Mandelbrot CPU Thread Function
static void* mandelbrot_cpu_thread(void* args) {
	for(uint32_t x = (size_t) args; x < current_image.res.x;
	x += THREAD_COUNT) {

		for(uint32_t y = 0x00; y < current_image.res.y; y++) {
			size_t index = y*current_image.res.x+x;

			vec2f_t c = {
				2.0f*x/current_image.res.x-1.5f,
				2.0f*y/current_image.res.y-0x01
			};

			uint8_t in = 0x01;
			vec2f_t z = {};
			vec2f_t temp;

			uint16_t i;
			for(i = 0x00; i < 0x0200; i++) {
				temp.x = z.x*z.x-z.y*z.y+c.x;
				temp.y = 0x02*z.x*z.y+c.y;
				z = temp;

				if(z.x*z.x+z.y*z.y > 0x04) {
					in = 0x00;
					break;
				}
			}

			if(in) {
				current_image.data[index].r = 0x00;
				current_image.data[index].g = 0x00;
				current_image.data[index].b = 0x00;
				current_image.data[index].a = 0xFF;
			} else {
				uint8_t v = sqrtf(i/511.0f)*0xFF;
				current_image.data[index].r = v;
				current_image.data[index].g = v;
				current_image.data[index].b = v;
				current_image.data[index].a = 0xFF;
			}
		}
	}

	return 0x00;
}


// Mandelbrot CPU Function
static inline void mandelbrot_cpu(image_t image) {
	// Setup
	pthread_t t[THREAD_COUNT-0x01];
	double time;
	size_t i;

	current_image = image;


	// Execution
	for(uint8_t j = 0x00; j < 0x04; j++) {
		time = get_time();

		for(i = 0x00; i < THREAD_COUNT-0x01; i++) {
			pthread_create(
				&t[i],
				0x00,
				mandelbrot_cpu_thread,
				(void*) i
			);
		}
		mandelbrot_cpu_thread((void*) i);

		for(i = 0x00; i < THREAD_COUNT-0x01; i++) {
			pthread_join(t[i], 0x00);
		}

		info("%lfs", get_time()-time);
	}
}


// Mandelbrot GPU Function
static inline void mandelbrot_gpu(image_t image) {
	// Setup
	uint32_t shader, program, ssbo;
	double time;
	FILE* file;
	void* data;


	// OpenGL Initialization
	gl_init();


	// Shader Loading
	file = fopen("resources/shaders/shader.glsl", "rb");
	if(!file) error("Failed to open resources/shaders/shader.glsl.");
	fread(buff1, 0x01, sizeof(buff1), file);
	fclose(file);


	// Shader and Program Compilation
	shader = glCreateShader(GL_COMPUTE_SHADER);
	program = glCreateProgram();
	compile_shader(shader, buff1);
	glAttachShader(program, shader);
	link_program(program);
	glDeleteShader(shader);
	glUseProgram(program);


	// Buffer Generation
	glGenBuffers(0x01, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		image.size_bytes,
		0x00,
		GL_STATIC_READ
	);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0x00, ssbo);


	// Execution
	glUniform2ui(0x00, image.res.x, image.res.y);

	for(uint8_t i = 0x00; i < 0x04; i++) {
		time = get_time();

		glDispatchCompute(image.res.x/0x10, image.res.y/0x10, 0x01);

		data = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		memcpy(image.data, data, image.size_bytes);
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		info("%lfs", get_time()-time);
	}


	// De-initialization
	glDeleteBuffers(0x01, &ssbo);
	glDeleteProgram(program);
	gl_deinit();
}


// Main Function
int32_t main(int32_t argc, char** args) {
	// Setup
	void (*func)(image_t image) = mandelbrot_gpu;
	for(int32_t i = 0x01; i < argc; i++) {
		if(!strcmp(args[i], "-cpu")) {
			func = mandelbrot_cpu;
			break;
		}
	}

	if(func == mandelbrot_gpu) {
		info("GPU method selected.");
	} else {
		info("CPU method selected.");
	}

	image_t image = new_image(0x2000, 0x2000);


	// Code
	func(image);


	// De-initialization
	save_image(image, "out.png");
	delete_image(image);
	return 0x00;
}
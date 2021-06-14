#ifndef GL_H
#define GL_H


// Headers
#include "types.h"


// GL Initialization Function
void gl_init();


// GL De-initialization Function
void gl_deinit();


// Compile Shader Function
void compile_shader(uint32_t shader, char* src);


// Link Program Function
void link_program(uint32_t program);


#endif
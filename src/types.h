#ifndef TYPES_H
#define TYPES_H


// Macros
#define PI	3.14159265359f
#define TAU	6.28318530718f


// Headers
#include <stddef.h>
#include <inttypes.h>


// Types
typedef struct {
	uint32_t x, y;
} vec2u_t;

typedef struct {
	int32_t x, y;
} vec2i_t;

typedef struct {
	float x, y;
} vec2f_t;

typedef struct {
	uint8_t r, g, b, a;
} pixel_t;

typedef struct {
	float r, g, b, a;
} color_t;

typedef struct {
	vec2u_t res;
	size_t size;
	pixel_t* data;
	size_t size_bytes;
} image_t;


#endif
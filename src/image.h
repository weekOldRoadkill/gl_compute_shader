#ifndef IMAGE_H
#define IMAGE_H


// Headers
#include "types.h"


// New Image Function
image_t new_image(uint32_t width, uint32_t height);


// Save Image Function
void save_image(image_t image, char* filename);


// Delete Image Function
void delete_image(image_t image);


#endif
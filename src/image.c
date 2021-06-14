// Headers
#include <stdio.h>
#include <stdlib.h>
#include <lodepng.h>

#include "types.h"
#include "utils.h"


// New Image Function
image_t new_image(uint32_t width, uint32_t height) {
	image_t image;
	image.res.x = width;
	image.res.y = height;
	image.size = width*height;
	image.size_bytes = image.size<<0x02;
	image.data = malloc(image.size_bytes);
	info("Image created successfully.");
	info("Image Info:");
	info("\t%"PRIu32"x%"PRIu32, width, height);
	info("\t%.2f MB uncompressed", image.size/262144.0f);
	return image;
}


// Save Image Function
void save_image(image_t image, char* filename) {
	info("Saving image to %s...", filename);
	if(lodepng_encode32_file(
		filename, (void*) image.data, image.res.x, image.res.y
	)) error("Failed to save image to %s.", filename);
	info("Image saved to %s successfully.", filename);
}


// Delete Image Function
void delete_image(image_t image) {
	free(image.data);
	info("Image deleted successfully.");
}
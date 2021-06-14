// Macros
#version 460 core


// In
layout(local_size_x = 0x10, local_size_y = 0x10) in;

layout(std430, binding = 0x00) buffer buff {
	uint pixels[];
};


// Uniforms
layout(location = 0x00) uniform uvec2 res;


// Main Function
void main() {
	uvec2 coords = gl_GlobalInvocationID.xy;

	vec2 c = 2.0f*coords/res-vec2(1.5f, 1.0f);
	uint index = coords.y*res.x+coords.x;
	vec2 z = vec2(0.0f);
	bool inside = true;
	uint i;

	for(i = 0x00; i < 0x0200; i++) {
		z = vec2(z.x*z.x-z.y*z.y, 0x02*z.x*z.y)+c;
		if(dot(z, z) > 0x04) {
			uint v = uint(sqrt(i/511.0f)*0xFF);
			pixels[index] = (v|(v<<0x08)|(v<<0x10))|0xFF000000;
			return;
		}
	}

	pixels[index] = 0xFF000000;
}
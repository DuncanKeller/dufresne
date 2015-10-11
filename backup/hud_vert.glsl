#!vert
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 in_texture_coordinates;
 
out vec2 texture_coordinates;
 
uniform mat4 model;
uniform sampler2D basic_texture;

void main () {
	texture_coordinates = in_texture_coordinates;
	gl_Position = model * vec4 (vertex_position, 1.0);
}
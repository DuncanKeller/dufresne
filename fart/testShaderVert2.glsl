#!vert
layout(location = 0) in vec3 vertex_position;
layout(location = 2) in vec2 in_texture_coordinates;
out vec2 texture_coordinates;
uniform vec2 resolution;
uniform vec2 farts[5];
uniform int hoops[12];
uniform vec4 rect;
uniform sampler2D basic_texture;

void main () {
texture_coordinates = in_texture_coordinates;

if(vertex_position.x < 0.0 && vertex_position.y < 0.0)
{
	gl_Position.x = ((rect.x / resolution.x) * 2) - 1;
	gl_Position.y = ((rect.y / resolution.y) * 2) - 1;
	texture_coordinates.x = 0;
	texture_coordinates.y = 0;
}
else if(vertex_position.x > 0.0 && vertex_position.y < 0.0)
{	
	gl_Position.x = (((rect.x + rect.z) / resolution.x) * 2) - 1;
	gl_Position.y = ((rect.y / resolution.y) * 2) - 1;
	texture_coordinates.x = 1;
	texture_coordinates.y = 0;
}
else if(vertex_position.x < 0.0 && vertex_position.y > 0.0)
{
	gl_Position.x = ((rect.x / resolution.x) * 2) - 1;
	gl_Position.y = (((rect.y + rect.w) / resolution.y) * 2) - 1;
	texture_coordinates.x = 0;
	texture_coordinates.y = 1;
}
else if(vertex_position.x > 0.0 && vertex_position.y > 0.0)
{
	gl_Position.x = (((rect.x + rect.z) / resolution.x) * 2) - 1;
	gl_Position.y = (((rect.y + rect.w) / resolution.y) * 2) - 1;
	texture_coordinates.x = 1;
	texture_coordinates.y = 1;
}

gl_Position.y *= -1;
gl_Position.z = 0.0;
gl_Position.w = 1.0;

}

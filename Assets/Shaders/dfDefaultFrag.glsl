in vec2 texture_coordinates;
uniform sampler2D basic_texture;
out vec4 frag_color;

void main () 
{
	vec4 texel = texture2D (basic_texture, texture_coordinates);
	frag_color = texel;
	frag_color.a = 0;
}
	
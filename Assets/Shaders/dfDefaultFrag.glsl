in vec2 texture_coordinates;
uniform sampler2D basic_texture;
uniform vec2 atlasPos;
uniform vec2 spriteSize;
uniform vec2 atlasSize;
out vec4 frag_color;


void main () 
{
	vec2 realCoord = (atlasPos / atlasSize) + ((spriteSize / atlasSize) * texture_coordinates);
	vec4 texel = texture2D (basic_texture, realCoord);
	frag_color = texel;
}
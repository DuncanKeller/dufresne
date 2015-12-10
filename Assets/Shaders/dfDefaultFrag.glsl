in vec2 texture_coordinates;uniform sampler2D basic_texture;uniform vec2 atlasPos;uniform vec2 spriteSize; uniform vec4 inColor;out vec4 frag_color;

void main () 
{

vec4 texel = texture2D (basic_texture, texture_coordinates);

	frag_color = vec4(texel.r * inColor.r, texel.g * inColor.g, texel.b * inColor.b, texel.a * inColor.a);

	if(frag_color.a == 0 || inColor.a == 0)
	{
		frag_color = vec4(0,0,0,0);
	}
}
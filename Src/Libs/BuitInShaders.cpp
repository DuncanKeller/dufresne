#include "BuitInShaders.h"

const char* defaultPostProcessVert = L""
	"#version 150\n"
	"in vec2 position;"
	"in vec2 texcoord;"
	"out vec2 Texcoord;"
	"void main()" 
	"{"
	"	Texcoord = texcoord;"
	"	gl_Position = vec4(position, 0.0, 1.0);"
	"}"
	"";

const char* defaultPostProcessFrag = L""
	"#version 150\n"
	"in vec2 Texcoord;"
	"out vec4 outColor;"
	"uniform sampler2D texFramebuffer;"
	"void main()"
	"{"
	"	outColor = texture(texFramebuffer, Texcoord);"
	"}"
	"";
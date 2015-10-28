#pragma once
#include <vector>
#include "STDUNC.h"

enum dfBasicType
{
	DF_null,
	DF_int,
	DF_int_arr,
	DF_unsigned_int_arr,
	DF_float,
	DF_float_arr,
	DF_bool,
	DF_vec2,
	DF_vec3,
	DF_vec4,
	DF_vec2_arr,
	DF_vec3_arr,
	DF_vec4_arr,
	DF_rect,
	DF_mat4x4,
	DF_mat4x4_arr,
	DF_point2D,
	DF_sampler2D
};

struct dfFile
{
	char* contents;
	int size;
};

struct UniformInfo
{
	std::vector<char> name;
	dfBasicType type;
	int arraySize;
};

struct ShaderInfo
{
	dfFile shaderFile;
	std::vector<UniformInfo> uniforms;
	int vertFragType;
};

struct TextureInfo
{
	dfFile file;
	char* name;
	std::vector<wchar_t> filetype;
	unsigned int glTexture;
	int width;
	int height;
};

dfBasicType dfGetTypeFromString(std::vector<char> str);

// globals 
extern point2D ScreenResolution;
extern float dfTotalTime;
extern float dfDeltaTime;

// config
const int render_box_initial_number_of_layers = 20;
const int render_box_initial_layer_size = 100;
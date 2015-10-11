#pragma once
#include <vector>
#include "STDUNC.h"

enum dfBasicType
{
	DF_null,
	DF_int,
	DF_int_arr,
	DF_float,
	DF_float_arr,
	DF_bool,
	DF_vec2,
	DF_vec3,
	DF_vec4,
	DF_mat4x4,
	DF_sampler2D
};

dfBasicType dfGetTypeFromString(std::vector<char> str);


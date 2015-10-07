#include "dfBasic.h"
#include "STDUNC.h"

dfBasicType dfGetTypeFromString(std::vector<char> str)
{
	if(dfStrCmp(str, "int"))
	{
		return DF_int;
	}
	else if(dfStrCmp(str, "float"))
	{
		return DF_float;
	}
	else if(dfStrCmp(str, "vec2"))
	{
		return DF_vec2;
	}
	else if(dfStrCmp(str, "vec3"))
	{
		return DF_vec3;
	}
	else if(dfStrCmp(str, "vec4"))
	{
		return DF_vec4;
	}
	else if(dfStrCmp(str, "mat4"))
	{
		return DF_mat4x4;
	}
	else if(dfStrCmp(str, "sampler2D"))
	{
		return DF_sampler2D;
	}

	return DF_null;
}
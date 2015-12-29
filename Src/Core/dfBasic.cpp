#include "dfBasic.h"

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
	else if(dfStrCmp(str, "rect"))
	{
		return DF_rect;
	}
	else if(dfStrCmp(str, "mat4"))
	{
		return DF_mat4x4;
	}
	else if(dfStrCmp(str, "mat4"))
	{
		return DF_mat4x4;
	}
	else if(dfStrCmp(str, "point2D"))
	{
		return DF_point2D;
	}
	else if(dfStrCmp(str, "sampler2D"))
	{
		return DF_sampler2D;
	}

	return DF_null;
}

void InitAsciiTable()
{
	asciiTable[' '] = 32;
	asciiTable['!'] = 33;
	asciiTable['\"'] = 34;
	asciiTable['#'] = 35;
	asciiTable['$'] = 36;
	asciiTable['%'] = 37;
	asciiTable['&'] = 38;
	asciiTable['\''] = 39;
	asciiTable['('] = 40;
	asciiTable[')'] = 41;
	asciiTable['*'] = 42;
	asciiTable['+'] = 43;
	//asciiTable[''] = 44;
	asciiTable['-'] = 45;
	asciiTable['.'] = 46;
	asciiTable['/'] = 47;
	asciiTable['0'] = 48;
	asciiTable['1'] = 49;
	asciiTable['2'] = 50;
	asciiTable['3'] = 51;
	asciiTable['4'] = 52;
	asciiTable['5'] = 53;
	asciiTable['6'] = 54;
	asciiTable['7'] = 55;
	asciiTable['8'] = 56;
	asciiTable['9'] = 57;
	
	asciiTable[':'] = 58;
	asciiTable[';'] = 59;
	asciiTable['<'] = 60;
	asciiTable['='] = 61;
	asciiTable['>'] = 62;
	asciiTable['?'] = 63;
	asciiTable['@'] = 64;

	asciiTable['A'] = 65;
	asciiTable['B'] = 66;
	asciiTable['C'] = 67;
	asciiTable['D'] = 68;
	asciiTable['E'] = 69;
	asciiTable['F'] = 70;
	asciiTable['G'] = 71;
	asciiTable['H'] = 72;
	asciiTable['I'] = 73;
	asciiTable['J'] = 74;
	asciiTable['K'] = 75;
	asciiTable['L'] = 76;
	asciiTable['M'] = 77;
	asciiTable['N'] = 78;
	asciiTable['O'] = 79;
	asciiTable['P'] = 80;
	asciiTable['Q'] = 81;
	asciiTable['R'] = 82;
	asciiTable['S'] = 83;
	asciiTable['T'] = 84;
	asciiTable['U'] = 85;
	asciiTable['V'] = 86;
	asciiTable['W'] = 87;
	asciiTable['X'] = 88;
	asciiTable['Y'] = 89;
	asciiTable['Z'] = 90;
	
	asciiTable['['] = 91;
	asciiTable['\\'] = 92;
	asciiTable[']'] = 93;
	asciiTable['^'] = 94;
	asciiTable['_'] = 95;
	asciiTable['`'] = 96;

	asciiTable['a'] = 97;
	asciiTable['b'] = 98;
	asciiTable['c'] = 99;
	asciiTable['d'] = 100;
	asciiTable['e'] = 101;
	asciiTable['f'] = 102;
	asciiTable['g'] = 103;
	asciiTable['h'] = 104;
	asciiTable['i'] = 105;
	asciiTable['j'] = 106;
	asciiTable['k'] = 107;
	asciiTable['l'] = 108;
	asciiTable['m'] = 109;
	asciiTable['n'] = 110;
	asciiTable['o'] = 111;
	asciiTable['p'] = 112;
	asciiTable['q'] = 113;
	asciiTable['r'] = 114;
	asciiTable['s'] = 115;
	asciiTable['t'] = 116;
	asciiTable['u'] = 117;
	asciiTable['v'] = 118;
	asciiTable['q'] = 119;
	asciiTable['x'] = 120;
	asciiTable['y'] = 121;
	asciiTable['z'] = 122;
	
	asciiTable['{'] = 123;
	asciiTable['|'] = 124;
	asciiTable['}'] = 125;
	asciiTable['~'] = 126;

}

void InitEngine()
{
	InitAsciiTable();
}
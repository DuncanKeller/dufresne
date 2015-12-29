#pragma once

#include <vector>
#include <windows.h>
#include "../Libs/glew.h"
#include <GL/GL.h>

struct Mesh
{
	unsigned int numVerts;
	
	unsigned int vertexArrayObject;
	unsigned int vertexBufferObject;
	unsigned int uvBufferObject;
};

void CreateDefaultMesh(Mesh *mesh);

// todo make data structure to store vertices, normals, etc that will be faster than a vector? 
// investigate if it makes a difference
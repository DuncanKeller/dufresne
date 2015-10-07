#pragma once

#include <vector>
#include <windows.h>
#include "glew.h"
#include <GL/GL.h>

struct Mesh
{
	unsigned int numVerts;

	unsigned int vertexBufferObject;
	unsigned int vertextArrayObject;
};

void CreateDefaultMesh(Mesh *mesh);

// todo make data structure to store vertices, normals, etc that will be faster than a vector? 
// investigate if it makes a difference
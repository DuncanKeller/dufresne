#include "Mesh.h"

void CreateDefaultMesh(Mesh *mesh)
{
	std::vector<float> points;
	points.push_back(-1.f); // x
	points.push_back(-1.f); // y
	points.push_back(0.f);  // z

	points.push_back(1.f);  // x
	points.push_back(-1.f); // y
	points.push_back(0.f);  // z

	points.push_back(1.f);  // x
	points.push_back(1.f);  // y
	points.push_back(0.f);  // z

	points.push_back(-1.f); // x
	points.push_back(-1.f); // y
	points.push_back(0.f);  // z

	points.push_back(1.f);  // x
	points.push_back(1.f);  // y
	points.push_back(0.f);  // z

	points.push_back(-1.f); // x
	points.push_back(1.f);  // y
	points.push_back(0.f);  // z

	mesh->numVerts = 6;

	std::vector<float> uvcoords;
	uvcoords.push_back(0); // u
	uvcoords.push_back(0); // v

	uvcoords.push_back(1); // u
	uvcoords.push_back(0); // v

	uvcoords.push_back(1); // u
	uvcoords.push_back(1); // v

	uvcoords.push_back(0); // u
	uvcoords.push_back(0); // v

	uvcoords.push_back(1); // u
	uvcoords.push_back(1); // v

	uvcoords.push_back(0); // u
	uvcoords.push_back(1); // v


	// vbo for verts
	glGenBuffers (1, &mesh->vertexBufferObject);
	glBindBuffer (GL_ARRAY_BUFFER, mesh->vertexBufferObject);
	glBufferData (GL_ARRAY_BUFFER, points.size() * sizeof (float), &points[0], GL_STATIC_DRAW);

	// vbo uvs
	glGenBuffers(1, &mesh->uvBufferObject);
	glBindBuffer (GL_ARRAY_BUFFER, mesh->uvBufferObject);
	glBufferData (GL_ARRAY_BUFFER, uvcoords.size() * sizeof (float), &uvcoords[0], GL_STATIC_DRAW);

	// vao
	glGenVertexArrays (1, &mesh->vertexArrayObject);
	glBindVertexArray (mesh->vertexArrayObject);
	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, mesh->vertexBufferObject);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer (GL_ARRAY_BUFFER, mesh->uvBufferObject);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}
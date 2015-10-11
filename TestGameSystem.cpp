#include "TestGameSystem.h"


TestGameSystem::TestGameSystem(void)
{
}


TestGameSystem::~TestGameSystem(void)
{
}


void TestGameSystem::Init()
{
	tf = Transform();
	RegisterComponent(&tf);

	render = Renderer();
	render.InitDefaultShader();
	render.SetDefaultRenderInfo();
	render.renderInfo.matrix = &tf.matrix;

	tf.matrix = MatMath::identity_mat4();
	
	render.renderInfo.uniforms[0].valueFloat = &(render.renderInfo.matrix->m[0]);

	RegisterComponent(&render);

	GameSystem::Init();
	
	// todo need process for this
	// todo need texture struct with format, w and h
	glGenTextures(1, &render.renderInfo.glTexture); 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, render.renderInfo.glTexture);

	dfFile textureFile = assMan.GetAsset(L"fart\\testTexture.jpg");

	glTexImage2D (
	  GL_TEXTURE_2D,
	  0,
	  GL_RGB,
	  400,
	  390,
	  0,
	  GL_RGB,
	  GL_UNSIGNED_BYTE,
	  (unsigned char*)textureFile.contents
	);
}

void TestGameSystem::Update()
{

	GameSystem::Update();
}

// notes
// 1
// render.renderInfo.matrix = &tf.matrix;
// OK, obviously I want to use the tf matrix as the render matrix. 
// any way to make this quicker/easier for a user?
// 2
// having to re-set that matrix uniform to point to the tf matrix is a hassle
// render.renderInfo.uniforms[0].valueFloat = &(render.renderInfo.matrix->m[0]);
// can we automate this somehow?
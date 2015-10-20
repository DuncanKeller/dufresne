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
	tf.SetScale(.7f,-.7f,1.f);
	
	// was model matrix, now coords...
	//render.renderInfo.uniforms[0].valueFloat = &(render.renderInfo.matrix->m[0]);

	RegisterComponent(&render);

	GameSystem::Init();
	
	// todo need process for this
	// todo need texture struct with format, w and h
	glGenTextures(1, &render.renderInfo.glTexture); 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, render.renderInfo.glTexture);

	dfFile textureFile = assMan.GetAsset(L"fart\\testTexture2.png");
	SDL_RWops* textureWops = SDL_RWFromMem((void*)textureFile.contents, textureFile.size);
	SDL_Surface *textureSurface = IMG_LoadTyped_RW(textureWops, 0, "PNG");
	if(!textureSurface) {
		const char* theFart = IMG_GetError();
		dfLog((char*)IMG_GetError());
		dfAssert(false); // could not create image asset
	}

	// gl texture params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D (
	  GL_TEXTURE_2D,
	  0,
	  GL_RGBA,
	  256,
	  192,
	  0,
	  GL_RGBA,
	  GL_UNSIGNED_BYTE,
	  textureSurface->pixels
	);
}

void TestGameSystem::Update()
{

	GameSystem::Update();
}

// todo
// notes
// 1
// render.renderInfo.matrix = &tf.matrix;
// OK, obviously I want to use the tf matrix as the render matrix. 
// any way to make this quicker/easier for a user?
// 2
// having to re-set that matrix uniform to point to the tf matrix is a hassle
// render.renderInfo.uniforms[0].valueFloat = &(render.renderInfo.matrix->m[0]);
// can we automate this somehow?
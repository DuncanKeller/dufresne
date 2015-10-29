#include "TestGameSystem.h"


TestGameSystem::TestGameSystem(void)
{
}


TestGameSystem::~TestGameSystem(void)
{
}


void TestGameSystem::Init()
{
	RegisterComponent(&tf);

	render.InitDefaultShader();
	render.renderInfo.matrix = &tf.matrix;

	tf.matrix = MatMath::identity_mat4();
	tf.SetScale(.7f,-.7f,1.f);
	
	// was model matrix, now coords...
	//render.renderInfo.uniforms[0].valueFloat = &(render.renderInfo.matrix->m[0]);

	RegisterComponent(&render);
	
	bc = BoxCollider();
	RegisterComponent(&bc);

	GameSystem::Init();
	
	

	TextureInfo textureFile = assMan.GetTexture(L"fart\\testTexture2.png");

	render.SetTexture(textureFile);
	
}

void TestGameSystem::Update()
{
	GameSystem::Update();

	if(input.keyboard.arrowUp.buttonDown)
	{
		RectMove(0, -0.01f, tf.rectangle);
	}
	if(input.keyboard.arrowDown.buttonDown)
	{
		RectMove(0, 0.01f, tf.rectangle);
	}
	if(input.keyboard.arrowLeft.buttonDown)
	{
		RectMove(-0.01f, 0, tf.rectangle);
	}
	if(input.keyboard.arrowRight.buttonDown)
	{
		RectMove( 0.01f, 0, tf.rectangle);
	}
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
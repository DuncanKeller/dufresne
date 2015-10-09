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
	render.renderInfo.matrix = &tf.matrix;

	RegisterComponent(&render);

	GameSystem::Init();
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
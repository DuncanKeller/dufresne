#include "Renderer.h"


Renderer::Renderer(void)
{
	renderInfo.depth = 0;
	renderInfo.glShaderProgram = 0;
	// todo clear me out VVV
	//renderInfo.mesh;
	for(int i = 0; i < DF_MAX_UNIFORMS; i++) 
	{
		renderInfo.uniforms[i].arrSize = 0;
		renderInfo.uniforms[i].name = 0;
		renderInfo.uniforms[i].type = DF_null;
		renderInfo.uniforms[i].valueInt = 0;
	}
}


Renderer::~Renderer(void)
{
	dfComponent::~dfComponent();
}

void Renderer::Init()
{

}

void Renderer::Update()
{

}

void Renderer::Render()
{

}

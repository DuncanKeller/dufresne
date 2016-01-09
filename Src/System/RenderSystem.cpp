#include "RenderSystem.h"

SDL_Window* RenderSystem::window;

int RenderSystem::currentNumPrimitives = 0;
dfPrimitive RenderSystem::primitives[MAX_DFPRIMITIVES];
unsigned int RenderSystem::primitiveRectShaderProg;
unsigned int RenderSystem::primitiveCircleShaderProg;
unsigned int RenderSystem::primitiveLineShaderProg;

RenderSystem::RenderSystem(void)
{
	letterBox = true;
	letterBoxRatio = vec2(1.f, 1.f);
}


RenderSystem::~RenderSystem(void)
{
}


void RenderSystem::Init()
{
	// gl operations
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// post process init
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &colorBufferTexture);
	glBindTexture(GL_TEXTURE_2D, colorBufferTexture);
	
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB, 
		GameResolution.x * ((float)ScreenResolution.x / (float)GameResolution.x), 
		GameResolution.y  * ((float)ScreenResolution.y / (float)GameResolution.y), 
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTexture, 0
	);

	CreateDefaultMesh(&screenRect);
	
	postProcessVert = Renderer::CompileShaderFromSrc(defaultPostProcessVert, GL_VERTEX_SHADER);
	postProcessFrag = Renderer::CompileShaderFromSrc(defaultPostProcessFrag, GL_FRAGMENT_SHADER);
	
	postProcessShaderProgram = glCreateProgram();
	glAttachShader (postProcessShaderProgram, postProcessVert);
	glAttachShader (postProcessShaderProgram, postProcessFrag);
	glLinkProgram (postProcessShaderProgram);

	Renderer::SetStandardUniforms(postProcessUnifroms);
	ShaderUniform unif;
	unif.name = "screenRatio";
	unif.type = DF_vec2;
	unif.valueFloat = &letterBoxRatio.x;
	postProcessUnifroms.push_back(unif);

	SetupPrimitives();
}

void RenderSystem::SetupPrimitives()
{
	unsigned int vert, frag;

	vert = Renderer::CompileShaderFromSrc(defaultVert, GL_VERTEX_SHADER);
	frag = Renderer::CompileShaderFromSrc(dfPrimitiveRectangleFrag, GL_FRAGMENT_SHADER);
	
	RenderSystem::primitiveRectShaderProg = glCreateProgram();
	glAttachShader (RenderSystem::primitiveRectShaderProg, vert);
	glAttachShader (RenderSystem::primitiveRectShaderProg, frag);
	glLinkProgram (RenderSystem::primitiveRectShaderProg);

	vert = Renderer::CompileShaderFromSrc(dfPrimitiveCircleVert, GL_VERTEX_SHADER);
	frag = Renderer::CompileShaderFromSrc(dfPrimitiveCircleFrag, GL_FRAGMENT_SHADER);
	
	RenderSystem::primitiveCircleShaderProg = glCreateProgram();
	glAttachShader (RenderSystem::primitiveCircleShaderProg, vert);
	glAttachShader (RenderSystem::primitiveCircleShaderProg, frag);
	glLinkProgram (RenderSystem::primitiveCircleShaderProg);

	vert = Renderer::CompileShaderFromSrc(dfPrimitiveLineVert, GL_VERTEX_SHADER);
	frag = Renderer::CompileShaderFromSrc(dfPrimitiveLineFrag, GL_FRAGMENT_SHADER);
	
	RenderSystem::primitiveLineShaderProg = glCreateProgram();
	glAttachShader (RenderSystem::primitiveLineShaderProg, vert);
	glAttachShader (RenderSystem::primitiveLineShaderProg, frag);
	glLinkProgram (RenderSystem::primitiveLineShaderProg);
}

void RenderSystem::UpdateResolution(int w, int h)
{
	vec2 oldRatio = vec2(((float)ScreenResolution.x / (float)GameResolution.x), 
		((float)ScreenResolution.y / (float)GameResolution.y));
	vec2 oldRes = vec2(ScreenResolution.x, ScreenResolution.y);
	
	SDL_SetWindowSize(window, w, h);
	glViewport(0,0,w,h);
	
	ScreenResolution.x = w;
	ScreenResolution.y = h;

	glBindTexture(GL_TEXTURE_2D, colorBufferTexture);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB, 
		GameResolution.x * ((float)ScreenResolution.x / (float)GameResolution.x), 
		GameResolution.y  * ((float)ScreenResolution.y / (float)GameResolution.y), 
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void RenderSystem::Update()
{
}

void RenderSystem::DrawRect(Rect r, vec4 color, int layer)
{
	dfPrimitive prim;
	prim.rect = r;
	prim.layer = layer;
	prim.type = dfPrimRectangle;
	primitives[currentNumPrimitives] = prim;
	dfPrimitive* p = &primitives[currentNumPrimitives];
	p->rInfo.primitive = p;

	p->rInfo.active = true;
	p->rInfo.color = color;
	p->rInfo.depth = layer;
	p->rInfo.glShaderProgram = RenderSystem::primitiveRectShaderProg;
	p->rInfo.glTexture = 0;
	p->rInfo.matrix = 0;
	CreateDefaultMesh(&p->rInfo.mesh);
	
	ShaderUniform unif;
	unif.name = "resolution";
	unif.type = DF_point2D;
	unif.valueInt = &(GameResolution.arr[0]);
	p->rInfo.uniforms.push_back(unif);
	
	unif.name = "rect";
	unif.type = DF_rect;
	unif.valueRect = &p->rect;
	p->rInfo.uniforms.push_back(unif);

	unif.type = DF_vec4;
	unif.name = "inColor";
	unif.valueFloat = &(p->rInfo.color.x);
	p->rInfo.uniforms.push_back(unif);

	currentNumPrimitives++;
}

void RenderSystem::DrawCircle(Circle c, vec4 color, int layer)
{
	dfPrimitive prim;
	prim.circle = c;
	prim.layer = layer;
	prim.type = dfPrimCircle;
	primitives[currentNumPrimitives] = prim;
	dfPrimitive* p = &primitives[currentNumPrimitives];
	p->rInfo.primitive = p;

	p->rInfo.active = true;
	p->rInfo.color = color;
	p->rInfo.depth = layer;
	p->rInfo.glShaderProgram = RenderSystem::primitiveCircleShaderProg;
	p->rInfo.glTexture = 0;
	p->rInfo.matrix = 0;
	CreateDefaultMesh(&p->rInfo.mesh);

	ShaderUniform unif;
	unif.name = "resolution";
	unif.type = DF_point2D;
	unif.valueInt = &(GameResolution.arr[0]);
	p->rInfo.uniforms.push_back(unif);
	
	unif.name = "pos";
	unif.type = DF_vec2;
	unif.valueFloat = &p->circle.center.x;
	p->rInfo.uniforms.push_back(unif);
	
	unif.name = "radius";
	unif.type = DF_float;
	unif.valueFloat = &p->circle.r;
	p->rInfo.uniforms.push_back(unif);

	unif.type = DF_vec4;
	unif.name = "inColor";
	unif.valueFloat = &(p->rInfo.color.x);
	p->rInfo.uniforms.push_back(unif);
		
	currentNumPrimitives++;
}

void RenderSystem::DrawLine(dfLine line, vec4 color, int layer)
{
	dfPrimitive prim;
	prim.line = line;
	prim.layer = layer;
	prim.type = dfPrimLine;
	primitives[currentNumPrimitives] = prim;
	dfPrimitive* p = &primitives[currentNumPrimitives];
	p->rInfo.primitive = p;

	p->rInfo.active = true;
	p->rInfo.color = color;
	p->rInfo.depth = layer;
	p->rInfo.glShaderProgram = RenderSystem::primitiveLineShaderProg;
	p->rInfo.glTexture = 0;
	p->rInfo.matrix = 0;
	CreateDefaultMesh(&p->rInfo.mesh);

	ShaderUniform unif;
	unif.name = "resolution";
	unif.type = DF_point2D;
	unif.valueInt = &(GameResolution.arr[0]);
	p->rInfo.uniforms.push_back(unif);

	unif.type = DF_vec4;
	unif.name = "inColor";
	unif.valueFloat = &(p->rInfo.color.x);
	p->rInfo.uniforms.push_back(unif);
		
	currentNumPrimitives++;
}


unsigned int RenderSystem::CompileShader(ShaderInfo shader)
{
	unsigned int shaderIndex = glCreateShader (shader.vertFragType);
	glShaderSource (shaderIndex, 1, (const GLchar** )&shader.shaderFile.contents, NULL);
	glCompileShader (shaderIndex);
	int params = -1;
	glGetShaderiv (shaderIndex, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) 
	{
		// todo logging
		//fprintf (stderr, "ERROR: GL shader index %i did not compile\n", shaderIndex);
		//PrintShaderLog(shaderIndex);
		dfAssert(false); // did not compile :(
		return 0;
	}

	return shaderIndex;
}

void RenderSystem::InitRenderBox()
{
	renderBox.reserve(render_box_initial_number_of_layers);
	for(int i = 0; i < render_box_initial_number_of_layers; i++)
	{
		renderBox[i].reserve(render_box_initial_layer_size);
	}
}


void RenderSystem::AddToRenderBox(RenderInfo r)
{
	// does not support negative depth values
	dfAssert(r.depth >= 0);
	int currentSize = (int)renderBox.size();

	if((int)renderBox.size() <= r.depth)
	{
		for(int i = 0; i < (r.depth+1) - currentSize; i++)
		{
			std::vector<RenderInfo> newBox;
			newBox.reserve(render_box_initial_layer_size);
			renderBox.push_back(newBox);
		}
	}

	renderBox[r.depth].push_back(r);
}

void RenderSystem::SortRenderBox(int boxIndex)
{
	// todo
	// Not sure if the render box will be big enough for it to really matter,
	// but probably worth looking into using a faster sort algo
	int j;
	RenderInfo temp;
		
	for (int i = 0; i < renderBox[boxIndex].size(); i++)
	{
		j = i;
		
		while (j > 0 && renderBox[boxIndex][j].depth < renderBox[boxIndex][j-1].depth)
		{
			temp = renderBox[boxIndex][j];
			renderBox[boxIndex][j] = renderBox[boxIndex][j-1];
			renderBox[boxIndex][j-1] = temp;
			j--;
		}
	}
}

void RenderSystem::ApplyUniforms(ShaderUniform uniform, unsigned int shaderProgram )
{
	// todo log warning if it can't find the matching uniform name
	if(uniform.valueInt != 0) // todo is it OK just to check int, instead of depending on type?
	{
		int uniformLoc = glGetUniformLocation (shaderProgram, uniform.name);
		if(uniformLoc >= 0)
		{
			// todo implement a buncha deez fuckers
			switch(uniform.type)
			{
			case DF_int:
				glUniform1i (uniformLoc, *uniform.valueInt);
				break;
			case DF_unsigned_int_arr:
				glUniform1uiv (uniformLoc, uniform.arrSize,
					uniform.valueUInt);
				break;
			case DF_float:
				glUniform1f (uniformLoc, *uniform.valueFloat);
				break;
			case DF_float_arr:
				glUniform1fv (uniformLoc, uniform.arrSize,
					uniform.valueFloat);
				break;
			case DF_mat4x4:
				glUniformMatrix4fv (uniformLoc, 1, GL_FALSE, uniform.valueFloat);
				break;
			case DF_mat4x4_arr:
				glUniformMatrix4fv (uniformLoc, uniform.arrSize, GL_FALSE, 
					uniform.valueFloat);
				break;
			case DF_sampler2D:
				// todo: fart, I forget how to use thisss
				//glUniform1i (uniformLoc, renderBox[i][n].glTexture);
				glUniform1i (uniformLoc, 0);
				break;
			case DF_point2D:
				glUniform2f(uniformLoc, (float)uniform.valueInt[0],
					(float)uniform.valueInt[1]);
				break;
			case DF_vec2:
				glUniform2f(uniformLoc, uniform.valueFloat[0],
					uniform.valueFloat[1]);
				break;
			case DF_vec3:
				glUniform3f(uniformLoc, uniform.valueFloat[0],
					uniform.valueFloat[1],
					uniform.valueFloat[2]);
				break;
			case DF_vec4:
				glUniform4f(uniformLoc, uniform.valueFloat[0],
					uniform.valueFloat[1],
					uniform.valueFloat[2],
					uniform.valueFloat[3]);
				break;
			case DF_vec2_arr:
				glUniform2fv(uniformLoc, uniform.arrSize,
					&uniform.valueFloat[0]);
				break;
			case DF_vec3_arr:
				glUniform3fv(uniformLoc, uniform.arrSize,
					&uniform.valueFloat[0]);
				break;
			case DF_vec4_arr:
				glUniform4fv(uniformLoc, uniform.arrSize,
					&uniform.valueFloat[0]);
				break;
			case DF_rect:
				glUniform4f(uniformLoc, uniform.valueRect->arr[0],
					uniform.valueRect->arr[1],
					uniform.valueRect->arr[2],
					uniform.valueRect->arr[3]);
				break;
			}
		}
	}
}

// todo better way than just passing around big vector
// needs to handle scene hirarchy eventually
void RenderSystem::RenderLoop(dfScene* scene) 
{
	// set gl state
	glClear(GL_COLOR_BUFFER_BIT);

	// render to render buffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	for(int i = 0; i < renderBox.size(); i++)
	{
		renderBox[i].clear();
	}
	
	// 1: add all render-able objects into render box
	std::type_index infer = typeid(Renderer);
	Renderer* currRen = (Renderer*)dfComponentMap[typeid(Renderer)];
	while(currRen != 0)
	{
		AddToRenderBox(currRen->renderInfo);
		currRen = (Renderer*)currRen->nextInList;
	}

	infer = typeid(dfParticleSystem);
	dfParticleSystem* currPartSys = (dfParticleSystem*)dfComponentMap[typeid(dfParticleSystem)];
	while(currPartSys != 0)
	{
		if(currPartSys->active)
		{
			for(int i = 0; i < currPartSys->currentParticleCap - 1; i++)
			{
				if(currPartSys->particleRenderers[i].renderInfo.active)
					AddToRenderBox(currPartSys->particleRenderers[i].renderInfo);
			}
			currPartSys = (dfParticleSystem*)currPartSys->nextInList;
		}
	}

	infer = typeid(bmpTextEntity);
	bmpTextEntity* currBmpTextEntity = (bmpTextEntity*)dfComponentMap[typeid(bmpTextEntity)];
	while(currBmpTextEntity != 0)
	{
		for(int i = 0; i < currBmpTextEntity->textLength; i++)
		{
			AddToRenderBox(currBmpTextEntity->glyphs[i].renderInfo);
		}
		currBmpTextEntity = (bmpTextEntity*)currBmpTextEntity->nextInList;
	}

	// add primitives
	for(int i = 0; i < currentNumPrimitives; i++)
	{
		dfPrimitive primitive = primitives[i];
		AddToRenderBox(primitive.rInfo);
	}
	
	// 2: sort renderboxes by similar shader program
	for(int i = 0; i < renderBox.size(); i++)
	{
		SortRenderBox(i);
	}

	// 3: render all boxes
	unsigned int currentShaderProgram = 0;
	bool firstRender = true;

	for(int i = 0; i < renderBox.size(); i++)
	{
		for(int n = 0; n < (int)renderBox[i].size(); n++)
		{
			if(renderBox[i][n].active)
			{
				unsigned int newShaderProg = renderBox[i][n].glShaderProgram;
				if(firstRender) // always set shader program for the first render
				{
					firstRender = false;
					glUseProgram(newShaderProg);
				}
				else
				{
					if(currentShaderProgram != newShaderProg)
					{
						currentShaderProgram = newShaderProg;
						glUseProgram(newShaderProg);
					}
				}
			
				// update uniforms from list
				for(int uIndex = 0; uIndex < renderBox[i][n].uniforms.size(); uIndex++) 
				{
					ApplyUniforms(renderBox[i][n].uniforms[uIndex], newShaderProg);
				}

				if(renderBox[i][n].primitive != NULL && renderBox[i][n].primitive->type == dfPrimLine)
				{
					dfLine line = renderBox[i][n].primitive->line;
					vec4 color = renderBox[i][n].primitive->rInfo.color;
					glLineWidth(line.width); 
					glColor3f(color.x, color.y, color.z);
					glBegin(GL_LINES);
					glVertex3f((line.a.x / GameResolution.x) * 2 - 1, -((line.a.y / GameResolution.y) * 2 - 1), 0.0f);
					glVertex3f((line.b.x / GameResolution.x) * 2 - 1, -((line.b.y / GameResolution.y) * 2 - 1), 0.0f);
					glEnd();
				}
				else
				{
					unsigned int newTexture = renderBox[i][n].glTexture;
					glActiveTexture(GL_TEXTURE0 + 0); // todo + 0 is which texture is passed into the shader... manage this somehow...
					glBindTexture (GL_TEXTURE_2D, newTexture);

					glBindVertexArray (renderBox[i][n].mesh.vertexArrayObject);
					glDrawArrays (GL_TRIANGLES, 0, renderBox[i][n].mesh.numVerts);
				}
			}
		}
	}
	
	// render the buffer to screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(postProcessShaderProgram);
	int uniformLoc = glGetUniformLocation (postProcessShaderProgram, "textureFramebuffer");
	if(uniformLoc >= 0)
		glUniform1i (uniformLoc, 0);

	if(letterBox)
	{
		float gameAspect = (float)GameResolution.x / (float)GameResolution.y;
		float screenAspect = (float)ScreenResolution.x / (float)ScreenResolution.y;
		if(gameAspect < screenAspect)
		{
			letterBoxRatio = vec2(((float)GameResolution.x * ((float)ScreenResolution.y / (float)GameResolution.y)) / (float)ScreenResolution.x, 1.f);
		}
		else if(gameAspect > screenAspect)
		{
			letterBoxRatio = vec2(1.f, ((float)GameResolution.y * ((float)ScreenResolution.x / (float)GameResolution.x)) / (float)ScreenResolution.y);
		}
		else
		{
			letterBoxRatio = vec2(1.f, 1.f);
		}
	}
	else
	{
		letterBoxRatio = vec2(1.f, 1.f);
	}

	for(int i = 0; i < postProcessUnifroms.size(); i++)
	{
		ApplyUniforms(postProcessUnifroms[i], postProcessShaderProgram);
	}

	glActiveTexture(GL_TEXTURE0 + 0); // todo + 0 is which texture is passed into the shader... manage this somehow...
	glBindTexture (GL_TEXTURE_2D, colorBufferTexture);
	glBindVertexArray (screenRect.vertexArrayObject);
	glDrawArrays (GL_TRIANGLES, 0, screenRect.numVerts);
	
	// end gl stuff
	glFlush(); 
	currentNumPrimitives = 0;
}
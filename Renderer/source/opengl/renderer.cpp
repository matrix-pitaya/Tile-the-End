#include"opengl/renderer.h"

#include<stdexcept>

bool Renderer::OpenGLRenderer::Initialize()
{
	if (!window)
	{
		std::runtime_error("Renderer module missing!");
	}

	return true;
}

void Renderer::OpenGLRenderer::Render()
{
	BeginFrame();
	DrawFrame();
	EndFrame();
}

void Renderer::OpenGLRenderer::BeginFrame()
{
	//TODO 渲染阴影贴图

	//TODO 切换到窗口帧帧率缓冲区
	//准备渲染 清空窗口帧缓冲区
	window->ClearFrameBuffer();
}
void Renderer::OpenGLRenderer::DrawFrame()
{
	//TODO 场景绘制
}
void Renderer::OpenGLRenderer::EndFrame()
{
	//TOOD 场景后处理

	//TODO UI绘制

	window->SwapBuffer();
}
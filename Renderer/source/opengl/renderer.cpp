#include"opengl/renderer.h"
#include"log/logapi.h"

#include<stdexcept>
#include<algorithm>
#include<string>

bool Renderer::OpenGLRenderer::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	if (!window)
	{
		std::runtime_error("Renderer module missing!");
		return false;
	}

	renderThread = std::thread(&::Renderer::OpenGLRenderer::RenderThread, this);

	isInitialized = true;
	return true;
}
void Renderer::OpenGLRenderer::Release()
{
	if (isReleased)
	{
		return;
	}

	isRunning = false;
	cond.notify_one();
	if (renderThread.joinable())
	{
		renderThread.join();
	}

	isReleased = true;
}
bool Renderer::OpenGLRenderer::InitOpenGLContext()
{
	openGLWindow = reinterpret_cast<GLFWwindow*>(window->GetNativeWindow());
	if (!openGLWindow)
	{
		Core::Log::Log(Core::Log::LogLevel::Error,"OpenGL Window Get Fail!");
		throw std::runtime_error("OpenGL Window Get Fail!");
		return false;
	}

	//创建OpenGL上下文
	glfwMakeContextCurrent(openGLWindow);

	//初始化GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(openGLWindow); //销毁窗口
		glfwTerminate(); //卸载GLFW库
		return false;
	}

	glEnable(GL_DEPTH_TEST);	//开启深度测试
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);		//开启面剔除
	glEnable(GL_STENCIL_TEST);	//开启模板测试
	glStencilFunc(GL_ALWAYS, 1, 0xFF);			//设置总是通过模板测试
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);	//设置更新模板缓冲区方式
	glStencilMask(0xFF);						//设置允许写入模板缓冲区
	glEnable(GL_MULTISAMPLE);					//启用多重采样抗锯齿
	glEnable(GL_FRAMEBUFFER_SRGB);				//开启SRGB帧缓冲区进行Gamma矫正

	isRunning = true;
	return true;
}
void Renderer::OpenGLRenderer::ProcessDrawcallCmd()
{
	for (auto& drawcallCmd : queue)
	{
		if (drawcallCmd.drawcall)
		{
			drawcallCmd.drawcall();
		}
	}
	queue.clear();
}
void Renderer::OpenGLRenderer::RenderThread()
{
	if (!InitOpenGLContext())
	{
		throw std::runtime_error("Init OpenGL Context Fail!");
	}

	while (true)
	{
		std::unique_lock<std::mutex> lock(mutex);
		cond.wait(lock, [this] { return !queue.empty() || !isRunning; });

		ProcessDrawcallCmd();
		if (queue.empty() && !isRunning)
		{
			break;
		}
	}
}

void Renderer::OpenGLRenderer::Render()
{
	if (!isRunning)
	{
		return;
	}

	{
		//准备drawcall命令
		std::lock_guard<std::mutex> lock(mutex);
		BeginFrame();
		DrawFrame();
		EndFrame();

		//根据渲染队列进行排序
		std::sort(queue.begin(), queue.end(), [](const DrawcallCmd& a, const DrawcallCmd& b) { return a.renderQueue < b.renderQueue; });
	}

	//唤醒渲染线程
	cond.notify_one();
}
void Renderer::OpenGLRenderer::BeginFrame()
{
	//TODO 渲染阴影贴图

	//TODO 切换到窗口帧帧率缓冲区
	//准备渲染 清空窗口帧缓冲区
	queue.push_back(DrawcallCmd(Render::RenderQueue::A, [this]() {window->ClearFrameBuffer();}));
}
void Renderer::OpenGLRenderer::DrawFrame()
{
	//TODO 场景绘制
}
void Renderer::OpenGLRenderer::EndFrame()
{
	//TOOD 场景后处理

	//TODO UI绘制
	queue.push_back(DrawcallCmd(Render::RenderQueue::C, [this]() {window->SwapBuffer(); }));
}
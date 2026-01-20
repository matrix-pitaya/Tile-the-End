#include"opengl/window.h"
#include"event/eventAPI.h"

Window::OpenGLWindow::OpenGLWindow() = default;
Window::OpenGLWindow::~OpenGLWindow()
{
	Release();
}

bool Window::OpenGLWindow::Initialize(int width, int height, const char* title)
{
	if (isInitialized)
	{
		return false;
	}

	//GLFW库
	if (glfwInit() != GLFW_TRUE)
	{
		return false;
	}

	//设置GLFW版本号3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwSwapInterval(1);

	//创建窗口
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	//检测窗口是否创建成功
	if (!window)
	{
		glfwTerminate();//卸载库
		return false;
	}
	glfwSetWindowUserPointer(window, this);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferResetSizeCallback);
	glfwSetCursorPosCallback(window, MouseCursorMoveCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);

	//TODO: 加载图标
	/*
	int _width, _height, _channel;
	unsigned char* pixels = stbi_load(WindowConfig::HUOLG_ICON_PATH, &_width, &_height, &_channel, 4);
	GLFWimage icon;
	icon.width = _width;
	icon.height = _height;
	icon.pixels = pixels;
	glfwSetWindowIcon(window, 1, &icon);
	stbi_image_free(pixels);
	*/

	//初始化GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window); //销毁窗口
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

	this->width = width;
	this->height = height;

	isInitialized = true;
	return true;
}
void Window::OpenGLWindow::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}
bool Window::OpenGLWindow::GetKeyDown(Engine::Input::KeyCode keyCode) const
{
	switch (keyCode)
	{
		case Engine::Input::KeyCode::W:
			return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;

		case Engine::Input::KeyCode::A:
			return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;

		case Engine::Input::KeyCode::S:
			return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

		case Engine::Input::KeyCode::D:
			return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

		case Engine::Input::KeyCode::Mouse0:
			return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

		case Engine::Input::KeyCode::Mouse1:
			return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

		case Engine::Input::KeyCode::Mouse2:
			return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

		case Engine::Input::KeyCode::ESC:
			return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

		default:
			return false;
	}
}
bool Window::OpenGLWindow::IsClose() const
{
	return static_cast<bool>(glfwWindowShouldClose(window));
}
void Window::OpenGLWindow::ClearFrameBuffer() const
{
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClearDepth(1.0f);
	glClearStencil(0x00);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void Window::OpenGLWindow::PollEvents() const
{
	glfwPollEvents();
}
void Window::OpenGLWindow::SwapBuffer() const
{
	glfwSwapBuffers(window);
}
void Window::OpenGLWindow::CloseWindow() const
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void* Window::OpenGLWindow::GetNativeWindow() const
{
	return window;
}
void Window::OpenGLWindow::ResetSize(int width, int height)
{
	this->width = width;
	this->height = height;
	glViewport(0, 0, width, height);
}

void Window::OpenGLWindow::FramebufferResetSizeCallback(GLFWwindow* glfwWindow, int width, int height)
{
	::Window::OpenGLWindow* window = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(glfwWindow));
	if (!window)
	{
		window->ResetSize(width, height);
	}
	
	if ((width > 0) && (height > 0))
	{
		Core::Event::Args::Window::FramebufferResetSizeEventArgs args = Core::Event::Args::Window::FramebufferResetSizeEventArgs(width, height);
		Core::Event::Event event = Core::Event::Event(Core::Event::EventType::WindowFramebufferResetSize, args);
		Core::Event::Emit(event);
	}
}
void Window::OpenGLWindow::MouseCursorMoveCallback(GLFWwindow* glfwWindow, double xPosition, double yPosition)
{
	Core::Event::Args::Input::MouseCurrsorMoveEventArgs args = Core::Event::Args::Input::MouseCurrsorMoveEventArgs(xPosition, yPosition);
	Core::Event::Event event = Core::Event::Event(Core::Event::EventType::MouseCurrsorMove, args);
	Core::Event::Emit(event);
}
void Window::OpenGLWindow::MouseScrollCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
{
	Core::Event::Args::Input::MouseScrollEventArgs args = Core::Event::Args::Input::MouseScrollEventArgs(xOffset, yOffset);
	Core::Event::Event event = Core::Event::Event(Core::Event::EventType::MouseScroll, args);
	Core::Event::Emit(event);
}

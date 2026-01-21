#pragma once

#include"def/def_delete_copy_move.h"
#include"enum/enum.h"

#include"Irenderer.h"

#include<thread>
#include<atomic>
#include<condition_variable>
#include<mutex>
#include<vector>
#include<functional>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace Renderer
{
	class OpenGLRenderer :public Interface::Renderer
	{
		DELETE_COPY_AND_MOVE(OpenGLRenderer)

	private:
		struct DrawcallCmd
		{
			DrawcallCmd(Render::RenderQueue renderQueue, std::function<void()> drawcall)
				:renderQueue(renderQueue), drawcall(std::move(drawcall)) {}

			Render::RenderQueue renderQueue;
			std::function<void()> drawcall;
		};

	public:
		OpenGLRenderer() = default;
		~OpenGLRenderer() { Release(); }

		bool Initialize() override;
		void Release() override;
		void Render() override;

	private:
		void BeginFrame();
		void DrawFrame();
		void EndFrame();

#pragma region RenderThreadFunction
	private:
		void RenderThread();
		bool InitOpenGLContext();
		void ProcessDrawcallCmd();
#pragma endregion

	private:
		std::thread renderThread;
		std::condition_variable cond;
		std::atomic<bool> isRunning = false;
		std::mutex mutex;
		std::vector<DrawcallCmd> queue;

		GLFWwindow* openGLWindow = nullptr;
	};
}
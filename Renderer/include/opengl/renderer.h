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
#include<algorithm>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace Renderer
{
	class OpenGLRenderer :public Interface::Renderer
	{
		DELETE_COPY_AND_MOVE(OpenGLRenderer)

	private:
		class DrawcallCmdParser
		{
			DELETE_COPY_AND_MOVE(DrawcallCmdParser)

		private:
			struct DrawcallCmd
			{
				DrawcallCmd(Render::RenderQueue renderQueue, std::function<void()> drawcall)
					:renderQueue(renderQueue), drawcall(std::move(drawcall)) { }

				Render::RenderQueue renderQueue;
				std::function<void()> drawcall;
			};

		public:
			DrawcallCmdParser() = default;
			~DrawcallCmdParser()
			{
				drawcallCmds.clear();
			}

			inline void ProcessDrawcallCmd()
			{
				//根据渲染队列进行排序
				std::sort(drawcallCmds.begin(), drawcallCmds.end(), [](const DrawcallCmd& a, const DrawcallCmd& b) { return a.renderQueue < b.renderQueue; });
				for (auto& drawcallCmd : drawcallCmds)
				{
					if (drawcallCmd.drawcall)
					{
						drawcallCmd.drawcall();
					}
				}
				drawcallCmds.clear();
			}
			inline void ClearDrawcallCmd()
			{
				drawcallCmds.clear();
			}
			inline void AddDrawcallCmd(Render::RenderQueue renderQueue, std::function<void()> drawcall)
			{
				drawcallCmds.emplace_back(renderQueue, std::move(drawcall));
			}
			inline void AddDrawcallCmd(DrawcallCmd drawcallCmd)
			{
				drawcallCmds.push_back(drawcallCmd);
			}
			inline bool IsEmpty()
			{
				return drawcallCmds.empty();
			}
			inline size_t DrawcallCmdCount()
			{
				return drawcallCmds.size();
			}

		private:
			std::vector<DrawcallCmd> drawcallCmds;
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
		void ProcessRenderCmd();
#pragma endregion

	private:
		std::thread renderThread;
		std::condition_variable cond;
		std::atomic<bool> isRunning = false;
		std::mutex mutex;
		DrawcallCmdParser renderCmd;

		GLFWwindow* openGLWindow = nullptr;
	};
}
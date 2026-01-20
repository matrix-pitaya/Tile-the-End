#pragma once

#include"def/def_delete_copy_move.h"
#include"enum/enum.h"

#include"Iwindow.h"

#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace Window
{
	class OpenGLWindow : public Interface::Window
	{
		DELETE_COPY_AND_MOVE(OpenGLWindow)

	public:
		OpenGLWindow();
		~OpenGLWindow();

		bool Initialize(int width,int height, const char* title) override;
		void Release() override;
		bool GetKeyDown(Engine::Input::KeyCode keyCode) const override;
		bool IsClose() const override;
		void ClearFrameBuffer() const override;
		void PollEvents() const override;
		void SwapBuffer() const override;
		void CloseWindow() const override;
		void* GetNativeWindow() const override;

		void ResetSize(int width, int height);

	private:
		static void FramebufferResetSizeCallback(GLFWwindow* window, int width, int height);
		static void MouseCursorMoveCallback(GLFWwindow* window, double xPosition, double yPosition);
		static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	private:
		GLFWwindow* window = nullptr;
		int width = 0;
		int height = 0;
	};
}
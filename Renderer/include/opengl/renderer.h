#pragma once

#include"def/def_delete_copy_move.h"

#include"Irenderer.h"

namespace Renderer
{
	class OpenGLRenderer :public Interface::Renderer
	{
		DELETE_COPY_AND_MOVE(OpenGLRenderer)
	public:
		OpenGLRenderer() = default;
		~OpenGLRenderer() = default;

		bool Initialize() override;
		void Render() override;

	private:
		void BeginFrame();
		void DrawFrame();
		void EndFrame();
	};
}
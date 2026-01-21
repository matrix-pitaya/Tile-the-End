#pragma once

#include"def/def_interface.h"

#include"Iwindow.h"

namespace Interface
{
	class Renderer
	{
		DECLARE_INTERFACE(Renderer)

	public:
		virtual bool Initialize() = 0;
		virtual void Release() = 0;
		virtual void Render() = 0;

		inline void Bind(Interface::Window* window)
		{
			this->window = window;
		}

	protected:
		Interface::Window* window = nullptr;
		bool isInitialized = false;
		bool isReleased = false;
	};
}
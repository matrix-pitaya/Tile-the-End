#pragma once

namespace Core
{
	enum class Color
	{
		White,
		Black,
		Red,
		Green,
		Yellow,
		Blue
	};
}

namespace Core::Log
{
	enum class LogLevel
	{
		Info, 
		Warning, 
		Error, 
		Debug
	};
}

namespace Core::Event
{
	enum class EventType
	{
		Invalid = -1,
		System = 0,

		//Window
		WindowClose,
		WindowFramebufferResetSize,

		//Input
		MouseCurrsorMove,
		MouseScroll,

		Custom = 1000	//允许应用层从1001开始自定义事件类型
	};
}

namespace Engine::Input
{
	enum class KeyCode
	{
		W,
		A,
		S,
		D,

		Mouse0,
		Mouse1,
		Mouse2,

		ESC
	};
}

namespace Render
{
	enum class RenderQueue
	{
		A, B, C
	};
}
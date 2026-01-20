#pragma once

#include"def/def_engine_subsystem.h"
#include"enum/enum.h"

#include<unordered_map>

namespace Engine
{
	class Engine;
}

namespace Engine::Internal
{
	class Input
	{
		DECLARE_ENGINE_SUBSYSTEM(Input)

	private:
		void Listen();
		bool GetKeyDown(::Engine::Input::KeyCode keyCode);

	private:
		std::unordered_map<::Engine::Input::KeyCode, bool> keyMap;
	};
}
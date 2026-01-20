#pragma once

#include"def/def_engine_subsystem.h"

namespace Engine
{
	class Engine;
}

namespace Engine::Internal
{
	class Destroyer
	{
		DECLARE_ENGINE_SUBSYSTEM(Destroyer)

	public:
		void Destroy();
	};
}
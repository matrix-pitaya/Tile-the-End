#pragma once

#include"def/def_engine_subsystem.h"

#include<chrono>
#include<cstdint>

namespace Engine
{
	class Engine;
}

namespace Engine::Internal
{
	class Time
	{
		DECLARE_ENGINE_SUBSYSTEM(Time)
		
	private:
		void Tick();
		void FrameSync();
		void SetFPS(float fps);
		float Seconds();
		int64_t Milliseconds();

	private:
		float delta = 0.0f;
		float fixdelta = 1.0f / 60.0f;
		float unscaledDeltaTime = 0.0f;
		float scale = 1.0f;
		float targetFrameTime = 1.0f / 144.0f;

		std::chrono::steady_clock::time_point tick = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point lastTick = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	};
}
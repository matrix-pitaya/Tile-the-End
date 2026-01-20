#include"internal/time/time.h"

#include<thread>

bool Engine::Internal::Time::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	isInitialized = true;
	return true;
}
void Engine::Internal::Time::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}

void Engine::Internal::Time::Tick()
{
	tick = std::chrono::steady_clock::now();
	unscaledDeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(tick - lastTick).count();
	delta = unscaledDeltaTime * scale;
	lastTick = tick;
}
void Engine::Internal::Time::FrameSync()
{
	float sleepTime = targetFrameTime - std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::steady_clock::now() - tick).count();
	if (sleepTime > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
	}
}
void Engine::Internal::Time::SetFPS(float fps)
{
	targetFrameTime = 1.0f / fps;
}
float Engine::Internal::Time::Seconds()
{
	return std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::steady_clock::now() - start).count();
}
int64_t  Engine::Internal::Time::Milliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
}
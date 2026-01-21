#include"engine.h"
#include"config.h"

IMPLEMENT_SINGLETON_CLASS(Engine, Engine);

bool Engine::Engine::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	if (!game)
	{
		throw std::runtime_error("Engine game module missing!");
	}
	if (!renderer)
	{
		throw std::runtime_error("Engine renderer module missing!");
	}
	if (!physics)
	{
		throw std::runtime_error("Engine physics module missing!");
	}
	if (!window)
	{
		throw std::runtime_error("Engine window module missing!");
	}
	if (!camera)
	{
		throw std::runtime_error("Engine camera module missing!");
	}

	renderer->Bind(window);
	window->Initialize(1080, 720, "Tile the End");
	renderer->Initialize();

	isInitialized = true;
	return true;
}
bool Engine::Engine::IsRunning()
{
	return !window->IsClose();
}
void Engine::Engine::Input()
{
	input.Listen();
}
void Engine::Engine::Tick()
{
	time.Tick();
	window->PollEvents();
	timer.Tick();
}
void Engine::Engine::Fixupdata()
{
	static float passTime = 0;
	unsigned int times = 0;
	passTime += time.delta;
	while (passTime >= time.fixdelta && times <= ::Engine::Config::MaxFixupdataExecuteTimes)
	{
		times++;
		passTime -= time.fixdelta;
	}

	//¹Ì¶¨Ö¡ÂÊ
	if (times > 0)
	{
		physics->OnFixupdata(times);
		script.OnFixupdata(times);
	}
}
void Engine::Engine::CoroutineSchedule()
{

}
void Engine::Engine::Updata()
{

}
void Engine::Engine::Lateupdata()
{

}
void Engine::Engine::Render()
{
	renderer->Render();
}
void Engine::Engine::EndOfFrame()
{
	destroyer.Destroy();
}
void Engine::Engine::FrameSync()
{
	time.FrameSync();
}
void Engine::Engine::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}
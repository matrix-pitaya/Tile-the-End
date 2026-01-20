#include"engineAPI.h"
#include"engine.h"

int Engine::Execute()
{
	return ::Engine::Engine::Instance.Execute();
}

bool Engine::Bind(Interface::Game* game, Interface::Renderer* renderer, Interface::Physics* physics,
	Interface::Window* window, Interface::Camera* camera)
{
	return ::Engine::Engine::Instance.Bind(game, renderer, physics, window, camera);
}

bool Engine::Module::RegisterGame(const std::string& name, std::function<Interface::Game* ()> function)
{
	return ::Engine::Engine::Instance.RegisterGame(name, std::move(function));
}
bool Engine::Module::RegisterPhysics(const std::string& name, std::function<Interface::Physics* ()> function)
{
	return ::Engine::Engine::Instance.RegisterPhysics(name, std::move(function));
}
bool Engine::Module::RegisterRenderer(const std::string& name, std::function<Interface::Renderer* ()> function)
{
	return ::Engine::Engine::Instance.RegisterRenderer(name, std::move(function));
}
bool Engine::Module::RegisterWindow(const std::string& name, std::function<Interface::Window* ()> function)
{
	return ::Engine::Engine::Instance.RegisterWindow(name, std::move(function));
}
bool Engine::Module::RegisterCamera(const std::string& name, std::function<Interface::Camera* ()> function)
{
	return ::Engine::Engine::Instance.RegisterCamera(name, std::move(function));
}

Interface::Game* Engine::Module::CreateGame(const std::string& name)
{
	return ::Engine::Engine::Instance.CreateGame(name);
}
Interface::Physics* Engine::Module::CreatePhysics(const std::string& name)
{
	return ::Engine::Engine::Instance.CreatePhysics(name);
}
Interface::Renderer* Engine::Module::CreateRenderer(const std::string& name)
{
	return ::Engine::Engine::Instance.CreateRenderer(name);
}
Interface::Window* Engine::Module::CreateWindow(const std::string& name)
{
	return ::Engine::Engine::Instance.CreateWindow(name);
}
Interface::Camera* Engine::Module::CreateCamera(const std::string& name)
{
	return ::Engine::Engine::Instance.CreateCamera(name);
}

const float& ::Engine::Time::delta = ::Engine::Engine::Instance.GetDeltaTime();
const float& ::Engine::Time::fixdelta = ::Engine::Engine::Instance.GetFixdeltaTime();
const float& ::Engine::Time::unscaledDeltaTime = ::Engine::Engine::Instance.GetUnscaledDeltaTime();
float& ::Engine::Time::scale = ::Engine::Engine::Instance.GetTimeScale();

float Engine::Time::Seconds()
{
	return ::Engine::Engine::Instance.GetSecondsTime();
}
int64_t Engine::Time::Milliseconds()
{
	return ::Engine::Engine::Instance.GetMillisecondsTime();
}

bool Engine::Timer::InvalidateTimerTask(const ::Engine::Timer::TaskToken& taskToken)
{
	return Engine::Engine::Instance.InvalidateTimerTask(taskToken);
}
::Engine::Timer::TaskToken RegisterTimer(float interval, bool isLoop, std::function<void()> callback)
{
	return Engine::Engine::Instance.RegisterTimer(interval, isLoop, callback);
}
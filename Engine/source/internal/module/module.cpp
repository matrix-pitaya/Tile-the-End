#include"internal/module/module.h"

bool Engine::Internal::Module::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	isInitialized = true;
	return true;
}
void Engine::Internal::Module::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}

bool Engine::Internal::Module::RegisterGame(const std::string& name, std::function<Interface::Game* ()> function)
{
	if (function == nullptr || (game.count(name) > 0))
	{
		return false;
	}

	game[name] = std::move(function);
	return true;
}
bool Engine::Internal::Module::RegisterPhysics(const std::string& name, std::function<Interface::Physics* ()> function)
{
	if (function == nullptr || (physics.count(name) > 0))
	{
		return false;
	}

	physics[name] = std::move(function);
	return true;
}
bool Engine::Internal::Module::RegisterRenderer(const std::string& name, std::function<Interface::Renderer* ()> function)
{
	if (function == nullptr || (renderer.count(name) > 0))
	{
		return false;
	}

	renderer[name] = std::move(function);
	return true;
}
bool Engine::Internal::Module::RegisterWindow(const std::string& name, std::function<Interface::Window* ()> function)
{
	if (function == nullptr || (window.count(name) > 0))
	{
		return false;
	}

	window[name] = std::move(function);
	return true;
}
bool Engine::Internal::Module::RegisterCamera(const std::string& name, std::function<Interface::Camera* ()> function)
{
	if (function == nullptr || (camera.count(name) > 0))
	{
		return false;
	}

	camera[name] = std::move(function);
	return true;
}

Interface::Game* Engine::Internal::Module::CreateGame(const std::string& name)
{
	auto iterator = game.find(name);
	return (iterator == game.end() || iterator->second == nullptr) ? nullptr : iterator->second();
}
Interface::Physics* Engine::Internal::Module::CreatePhysics(const std::string& name)
{
	auto iterator = physics.find(name);
	return (iterator == physics.end() || iterator->second == nullptr) ? nullptr : iterator->second();
}
Interface::Renderer* Engine::Internal::Module::CreateRenderer(const std::string& name)
{
	auto iterator = renderer.find(name);
	return (iterator == renderer.end() || iterator->second == nullptr) ? nullptr : iterator->second();
}
Interface::Window* Engine::Internal::Module::CreateWindow(const std::string& name)
{
	auto iterator = window.find(name);
	return (iterator == window.end() || iterator->second == nullptr) ? nullptr : iterator->second();
}
Interface::Camera* Engine::Internal::Module::CreateCamera(const std::string& name)
{
	auto iterator = camera.find(name);
	return (iterator == camera.end() || iterator->second == nullptr) ? nullptr : iterator->second();
}

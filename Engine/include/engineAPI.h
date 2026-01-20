#pragma once

#include"Iwindow.h"
#include"Irenderer.h"
#include"Iphysics.h"
#include"Igame.h"
#include"Icamera.h"

#include<string>
#include<functional>

namespace Engine
{
	int Execute();

	bool Bind(Interface::Game* game, Interface::Renderer* renderer, Interface::Physics* physics,
		Interface::Window* window, Interface::Camera* camera);
}

namespace Engine::Module
{
	bool RegisterGame(const std::string& name, std::function<Interface::Game* ()> function);
	bool RegisterPhysics(const std::string& name, std::function<Interface::Physics* ()> function);
	bool RegisterRenderer(const std::string& name, std::function<Interface::Renderer* ()> function);
	bool RegisterWindow(const std::string& name, std::function<Interface::Window* ()> function);
	bool RegisterCamera(const std::string& name, std::function<Interface::Camera* ()> function);

	Interface::Game* CreateGame(const std::string& name);
	Interface::Physics* CreatePhysics(const std::string& name);
	Interface::Renderer* CreateRenderer(const std::string& name);
	Interface::Window* CreateWindow(const std::string& name);
	Interface::Camera* CreateCamera(const std::string& name);
}

namespace Engine::Time
{
	extern const float& delta;
	extern const float& fixdelta;
	extern const float& unscaledDeltaTime;
	extern float& scale;

	float Seconds();
	int64_t Milliseconds();
}

namespace Engine::Timer
{
	struct TaskToken;

	bool InvalidateTimerTask(const ::Engine::Timer::TaskToken& taskToken);
	::Engine::Timer::TaskToken RegisterTimer(float interval, bool isLoop, std::function<void()> callback);
}

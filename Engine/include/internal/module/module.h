#pragma once

#include"def/def_engine_subsystem.h"

#include"Iwindow.h"
#include"Irenderer.h"
#include"Iphysics.h"
#include"Igame.h"
#include"Icamera.h"

#include<string>
#include<unordered_map>
#include<functional>

namespace Engine
{
	class Engine;
}

namespace Engine::Internal
{
	class Module
	{
		DECLARE_ENGINE_SUBSYSTEM(Module)

	private:
		Interface::Game* CreateGame(const std::string& name);
		Interface::Physics* CreatePhysics(const std::string& name);
		Interface::Renderer* CreateRenderer(const std::string& name);
		Interface::Window* CreateWindow(const std::string& name);
		Interface::Camera* CreateCamera(const std::string& name);

		bool RegisterGame(const std::string& name, std::function<Interface::Game*()> function);
		bool RegisterPhysics(const std::string& name, std::function<Interface::Physics*()> function);
		bool RegisterRenderer(const std::string& name, std::function<Interface::Renderer*()> function);
		bool RegisterWindow(const std::string& name, std::function<Interface::Window*()> function);
		bool RegisterCamera(const std::string& name, std::function<Interface::Camera* ()> function);

	private:
		std::unordered_map<std::string, std::function<Interface::Game*()>> game;
		std::unordered_map<std::string, std::function<Interface::Physics*()>> physics;
		std::unordered_map<std::string, std::function<Interface::Renderer*()>> renderer;
		std::unordered_map<std::string, std::function<Interface::Window*()>> window;
		std::unordered_map<std::string, std::function<Interface::Camera* ()>> camera;
	};
}
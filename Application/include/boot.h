#pragma once

#include"console/console.h"

#include"engineAPI.h"
#include"applicationAPI.h"

#include<stdexcept>

namespace Application
{
	inline int Execute()
	{
		try
		{
			Application::Bootstrap();

			Interface::Game* application = Engine::Module::CreateGame("TilltheEnd");
			Interface::Renderer* renderer = Engine::Module::CreateRenderer("OpenGLRenderer");
			Interface::Physics* physics = Engine::Module::CreatePhysics("PitayaPhysics");
			Interface::Window* window = Engine::Module::CreateWindow("OpenGLWindow");
			Interface::Camera* camera = Engine::Module::CreateCamera("PerspectiveCamera");

			Engine::Bind(application, renderer, physics, window, camera);
			
			return Engine::Execute();
		}
		catch (const std::runtime_error& e)
		{
			Core::Console::Print(e.what());
			return -1;
		}
	}
}
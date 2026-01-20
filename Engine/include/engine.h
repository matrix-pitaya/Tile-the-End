#pragma once

#include"def/def_singleton.h"
#include"enum/enum.h"

#include"Igame.h"
#include"Irenderer.h"
#include"Iphysics.h"
#include"Iwindow.h"
#include"Icamera.h"

#include"internal/input/input.h"
#include"internal/time/time.h"
#include"internal/module/module.h"
#include"internal/destroyer/destroyer.h"
#include"internal/script/script.h"
#include"internal/timer/timer.h"

namespace Engine
{
	class Engine
	{
		DECLARE_SINGLETON_CLASS_RI(Engine);

	public:
		inline int Execute()
		{
			if (!Initialize())
			{
				return -1;
			}

			while (IsRunning())
			{
				Input();
				Tick();
				Fixupdata();
				Updata();
				CoroutineMoveNext();
				Lateupdata();
				Render();
				EndOfFrame();
				FrameSync();
			}

			Release();
			return 0;
		}

		inline bool Bind(Interface::Game* game, Interface::Renderer* renderer, Interface::Physics* physics,
			Interface::Window* window, Interface::Camera* camera)
		{
			this->game = game;
			this->renderer = renderer;
			this->physics = physics;
			this->window = window;
			this->camera = camera;
			return true;
		}

#pragma region Input
		inline bool GetKeyDown(::Engine::Input::KeyCode keyCode) const
		{
			return window->GetKeyDown(keyCode);
		}
#pragma endregion

#pragma region Module
		inline bool RegisterGame(const std::string& name, std::function<Interface::Game* ()> function)
		{
			return module.RegisterGame(name, function);
		}
		inline bool RegisterPhysics(const std::string& name, std::function<Interface::Physics* ()> function)
		{
			return module.RegisterPhysics(name, function);
		}
		inline bool RegisterRenderer(const std::string& name, std::function<Interface::Renderer* ()> function)
		{
			return module.RegisterRenderer(name, function);
		}
		inline bool RegisterWindow(const std::string& name, std::function<Interface::Window* ()> function)
		{
			return module.RegisterWindow(name, function);
		}
		inline bool RegisterCamera(const std::string& name, std::function<Interface::Camera* ()> function)
		{
			return module.RegisterCamera(name, function);
		}

		inline Interface::Game* CreateGame(const std::string& name)
		{
			return module.CreateGame(name);
		}
		inline Interface::Physics* CreatePhysics(const std::string& name)
		{
			return module.CreatePhysics(name);
		}
		inline Interface::Renderer* CreateRenderer(const std::string& name)
		{
			return module.CreateRenderer(name);
		}
		inline Interface::Window* CreateWindow(const std::string& name)
		{
			return module.CreateWindow(name);
		}
		inline Interface::Camera* CreateCamera(const std::string& name)
		{
			return module.CreateCamera(name);
		}
#pragma endregion

#pragma region Time
		inline const float& GetDeltaTime() const
		{
			return time.delta;
		}
		inline const float& GetFixdeltaTime() const
		{
			return time.fixdelta;
		}
		inline const float& GetUnscaledDeltaTime() const
		{
			return time.unscaledDeltaTime;
		}
		inline float& GetTimeScale()
		{
			return time.scale;
		}
		inline float GetSecondsTime()
		{
			return time.Seconds();
		}
		inline int64_t GetMillisecondsTime()
		{
			return time.Milliseconds();
		}
#pragma endregion

#pragma region Timer
		inline bool InvalidateTimerTask(const ::Engine::Timer::TaskToken& taskToken)
		{
			return timer.InvalidateTask(taskToken);
		}
		inline ::Engine::Timer::TaskToken RegisterTimer(float interval, bool isLoop, std::function<void()> callback)
		{
			return timer.RegisterTimer(interval, isLoop, callback);
		}
#pragma endregion

#pragma region Destroyer

#pragma endregion

	private:
		bool IsRunning();
		void Input();
		void Tick();
		void Fixupdata();
		void Updata();
		void CoroutineMoveNext();
		void Lateupdata();
		void Render();
		void EndOfFrame();
		void FrameSync();

	private:
		Interface::Game* game = nullptr;
		Interface::Renderer* renderer = nullptr;
		Interface::Physics* physics = nullptr;
		Interface::Window* window = nullptr;
		Interface::Camera* camera = nullptr;

		Internal::Input input;
		Internal::Module module;
		Internal::Script script;
		Internal::Time time;
		Internal::Timer timer;
		Internal::Destroyer destroyer;
		//coroutine
		//scene
	};
}
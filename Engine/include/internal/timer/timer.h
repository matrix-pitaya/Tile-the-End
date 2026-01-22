#pragma once

#include"def/def_engine_subsystem.h"

#include"objectpool/objectpool.h"

#include<chrono>
#include<unordered_map>

namespace Engine
{
	class Engine;
}

namespace Engine::Timer
{
	struct TaskToken
	{
		TaskToken(unsigned int id) :id(id) {}
		~TaskToken() = default;

		bool operator==(const TaskToken& other) const noexcept
		{
			return id == other.id;
		}

		const unsigned int id;

		struct Hash
		{
			size_t operator()(const ::Engine::Timer::TaskToken& taskToken) const noexcept
			{
				return std::hash<unsigned int>()(taskToken.id);
			}
		};
	};
}

namespace Engine::Internal
{
	class Timer
	{
		DECLARE_ENGINE_SUBSYSTEM(Timer)

	private:
		class Task
		{
			friend class Timer;
			struct CompareHandler
			{
				bool operator()(const Task* a, const Task* b)
				{
					return a->triggerTime > b->triggerTime;
				}
			};
		public:
			Task() = default;
			~Task() = default;
			Task(const Task&) = delete;
			Task& operator=(const Task&) = delete;
			Task(Task&& other) noexcept = default;
			Task& operator=(Task&& other) noexcept = default;

			inline void Execute()
			{
				if (!callback)
				{
					return;
				}

				callback();
			}
			inline void Reset()
			{
				id = 0;
				interval = 0.0f;
				triggerTime = 0.0f;
				isLoop = true;
				isValid = true;
				callback = nullptr;
			}

		private:
			unsigned int id = 0;
			float interval = 0.0f;
			float triggerTime = 0.0f;
			bool isLoop = true;
			bool isValid = true;
			std::function<void()> callback;
		};

	public:
		void Tick();
		bool InvalidateTask(const ::Engine::Timer::TaskToken& taskToken);
		::Engine::Timer::TaskToken RegisterTimer(float interval, bool isLoop, std::function<void()> callback);

	private:
		std::priority_queue<Task*, std::vector<Task*>, Task::CompareHandler> taskQueue;
		std::unordered_map<::Engine::Timer::TaskToken, Task*, ::Engine::Timer::TaskToken::Hash> taskMap;
		Core::ObjectPool<Task> taskPool = Core::ObjectPool<Task>([](Task* task) { task->Reset(); }, [](Task* task) { task->Reset(); }, 10);
	};
}

#include"internal/timer/timer.h"

#include"utility/utility.h"

#include"engineAPI.h"

bool Engine::Internal::Timer::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	isInitialized = true;
	return true;
}
void Engine::Internal::Timer::Release()
{
	if (isReleased)
	{
		return;
	}

	taskMap.clear();

	while (!taskQueue.empty())
	{
		taskQueue.pop();
	}

	isReleased = true;
}

void Engine::Internal::Timer::Tick()
{
	const float currentTime = ::Engine::Time::Seconds();

	std::vector<Task*> triggerTasks;
	while (!taskQueue.empty() && taskQueue.top()->triggerTime <= currentTime)
	{
		Task* task = taskQueue.top();
		taskQueue.pop();
		taskMap.erase(::Engine::Timer::TaskToken(task->id));

		triggerTasks.push_back(task);
	}

	for (auto& task : triggerTasks)
	{
		if (!task->isValid)
		{
			taskPool.Release(task);
			continue;
		}

		task->Execute();
		if (task->isLoop)
		{
			task->triggerTime = currentTime + task->interval;
			taskQueue.push(task);
			taskMap.emplace(::Engine::Timer::TaskToken(task->id), task);
			continue;
		}
		taskPool.Release(task);
	}
	triggerTasks.clear();
}
bool Engine::Internal::Timer::InvalidateTask(const ::Engine::Timer::TaskToken& taskToken)
{
	auto iterator = taskMap.find(taskToken);
	if((iterator == taskMap.end()) || (!iterator->second))
	{
		return false; 
	}

	iterator->second->isValid = false;
	taskMap.erase(iterator);
	return true;
}
::Engine::Timer::TaskToken Engine::Internal::Timer::RegisterTimer(float interval, bool isLoop, std::function<void()> callback)
{
	Task* task = taskPool.Get();
	task->id = Core::Generator::GenerateInstanceId();
	task->interval = interval;
	task->triggerTime = ::Engine::Time::Seconds() + interval;
	task->isLoop = isLoop;
	task->isValid = true;
	task->callback = std::move(callback);

	::Engine::Timer::TaskToken taskToken = ::Engine::Timer::TaskToken(task->id);

	taskQueue.push(task);
	taskMap.emplace(taskToken, task);

	return taskToken;
}
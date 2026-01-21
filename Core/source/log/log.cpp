#include"log/log.h"

#include"utility/utility.h"

IMPLEMENT_SINGLETON_CLASS(Core::Log, LogManager)

void Core::Log::LogManager::Bootstrap()
{
	if (isBootstraped)
	{
		return;
	}

	const std::string& path = GetExeDir() + "log.txt";
	ofs.open(path, std::ios::out | std::ios::trunc);
	if (!ofs.is_open())
	{
		throw std::runtime_error("Open Log File Fail! Path: " + path);
	}

	logThread = std::thread(&LogManager::LogThread, this);

	isBootstraped = true;
}
void Core::Log::LogManager::Release()
{
	if (isReleased)
	{
		return;
	}

	isRunning = false;
	cond.notify_one();
	if (logThread.joinable())
	{
		logThread.join();
	}
	ofs.close();
	while (!queue.empty())
	{
		queue.pop();
	}

	isReleased = true;
}
void Core::Log::LogManager::LogThread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(mutex);
		cond.wait(lock, [this] { return !queue.empty() || !isRunning; });

		while (!queue.empty()) 
		{
			const LogMessage& logMessage = queue.front();
			ofs << "[" << (logMessage.time) << "][" << LogLevelToString(logMessage.level) << "] "<< logMessage.message << std::endl;
			queue.pop();
		}
		ofs.flush();

		if (queue.empty() && !isRunning)
		{
			break;
		}
	}
}
void Core::Log::LogManager::Log(LogLevel level, const std::string& message)
{
	LogMessage logMessage;
	logMessage.level = level;
	logMessage.message = message;
	logMessage.time = Core::Utility::Date();
	{
		std::lock_guard<std::mutex> lock(mutex);
		queue.push(logMessage);
	}
	cond.notify_one();
}
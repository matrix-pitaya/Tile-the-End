#include"log/logapi.h"
#include"log/log.h"

void Core::Log::Log(LogLevel level, const std::string& message)
{
	Core::Log::LogManager::Instance.Log(level, message);
}
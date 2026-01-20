#pragma once

#include"enum/enum.h"
#include<string>

namespace Core::Log
{
	void Log(LogLevel level,const std::string& message);
}
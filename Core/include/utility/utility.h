#pragma once

#include <string>

namespace Core::Generator
{
	unsigned int GenerateInstanceId();
	std::string GenerateInstanceUId();
}

namespace Core::Utility
{
	std::string Date();
}
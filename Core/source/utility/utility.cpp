#include"utility/utility.h"

#include<random>
#include<chrono>

unsigned int Core::Generator::GenerateInstanceId()
{
	static unsigned int instanceId = 1;
	return instanceId++;
}
std::string Core::Generator::GenerateInstanceUId()
{
	static const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	std::random_device rd = std::random_device();
	std::mt19937 gen = std::mt19937(rd());
	std::uniform_int_distribution<> dist = std::uniform_int_distribution<>(0, sizeof(charset) - 2);

	std::string uid;
	for (int i = 0; i < 16; ++i)
	{
		uid += charset[dist(gen)];
	}

	uid.insert(4, "-");
	uid.insert(9, "_");
	uid.insert(14, "-");
	return uid;
}

std::string Core::Utility::Date()
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm buf;
#if defined(_WIN32)
	localtime_s(&buf, &t);
#else
	localtime_r(&t, &buf);
#endif
	char temp[32] = {};
	std::strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", &buf);
	return temp;
}
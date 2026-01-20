#include"internal/script/script.h"

bool ::Engine::Internal::Script::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	isInitialized = true;
	return true;
}
void ::Engine::Internal::Script::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}
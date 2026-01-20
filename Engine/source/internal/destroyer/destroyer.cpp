#include"internal/destroyer/destroyer.h"

bool Engine::Internal::Destroyer::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	isInitialized = true;
	return true;
}
void Engine::Internal::Destroyer::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}

void Engine::Internal::Destroyer::Destroy()
{

}
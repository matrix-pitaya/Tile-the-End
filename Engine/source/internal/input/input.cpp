#include"internal/input/input.h"

#include"engine.h"

bool Engine::Internal::Input::Initialize()
{
	if (isInitialized)
	{
		return false;
	}

	keyMap.emplace(::Engine::Input::KeyCode::W, false);
	keyMap.emplace(::Engine::Input::KeyCode::A, false);
	keyMap.emplace(::Engine::Input::KeyCode::S, false);
	keyMap.emplace(::Engine::Input::KeyCode::D, false);
	keyMap.emplace(::Engine::Input::KeyCode::Mouse0, false);
	keyMap.emplace(::Engine::Input::KeyCode::Mouse1, false);
	keyMap.emplace(::Engine::Input::KeyCode::Mouse2, false);
	keyMap.emplace(::Engine::Input::KeyCode::ESC, false);

	isInitialized = true;
	return true;
}
void Engine::Internal::Input::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}

void Engine::Internal::Input::Listen()
{
	for (auto& pair : keyMap)
	{
		pair.second = Engine::Instance.GetKeyDown(pair.first);
	}
}
bool Engine::Internal::Input::GetKeyDown(::Engine::Input::KeyCode keyCode)
{
	return keyMap.at(keyCode);
}
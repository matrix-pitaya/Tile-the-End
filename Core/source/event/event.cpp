#include"event/event.h"
#include"event/eventAPI.h"
#include"utility/utility.h"

IMPLEMENT_SINGLETON_CLASS(Core::Event, EventManager)

void Core::Event::EventManager::Release()
{
	if (isReleased)
	{
		return;
	}

	isReleased = true;
}

Core::Event::EventToken Core::Event::EventManager::Subscribe(::Core::Event::EventType type, std::function<void(const ::Core::Event::Event&)> function)
{
	if (function == nullptr)
	{
		return EventToken(0, ::Core::Event::EventType::Invalid);
	}

	EventToken eventToken = EventToken(Core::Generator::GenerateInstanceId(), type);
	eventMap[type][eventToken] = std::move(function);
	return eventToken;
}
bool Core::Event::EventManager::UnSubscribe(const Core::Event::EventToken& eventToken)
{
	auto iterator = eventMap.find(eventToken.type);
	if (iterator == eventMap.end())
	{
		return false;
	}
	
	if (iterator->second.find(eventToken) == iterator->second.end())
	{
		return false;
	}

	iterator->second.erase(eventToken);
	if (iterator->second.empty())
	{
		eventMap.erase(eventToken.type);
	}
	return true;
}
void Core::Event::EventManager::Emit(const ::Core::Event::Event& event)
{
	auto iterator = eventMap.find(event.type);
	if (iterator == eventMap.end())
	{
		return;
	}

	for (const auto& pair : iterator->second)
	{
		if (pair.second != nullptr)
		{
			pair.second(event);
		}
	}
}

Core::Event::EventToken::EventToken(unsigned int id, Core::Event::EventType type)
	:id(id), type(type) { }

Core::Event::Event::Event(::Core::Event::EventType type, const ::Core::Event::Args::EventArgs& args) 
	:type(type), args(args) { }

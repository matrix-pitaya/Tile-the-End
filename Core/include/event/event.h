#pragma once

#include"def/def_singleton.h"
#include"enum/enum.h"

#include<functional>
#include<unordered_map>

namespace Core::Event
{
	namespace Args
	{
		struct EventArgs;
	}

	struct Event;
	struct EventToken;

	class EventManager
	{
		DECLARE_SINGLETON_CLASS_R(EventManager)
	public:
		Core::Event::EventToken Subscribe(::Core::Event::EventType type, std::function<void(const ::Core::Event::Event&)> function);
		bool UnSubscribe(const Core::Event::EventToken& eventToken);
		void Emit(const ::Core::Event::Event& event);

	private:
		std::unordered_map<::Core::Event::EventType,
			std::unordered_map<::Core::Event::EventToken, std::function<void(const ::Core::Event::Event&)>>> eventMap;
	};
}
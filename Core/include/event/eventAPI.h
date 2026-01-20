#pragma once

#include"enum/enum.h"

#include<functional>

namespace Core::Event
{
	namespace Args
	{
		struct EventArgs
		{
			EventArgs() = default;
			virtual ~EventArgs() = default;
		};

		namespace Window
		{
			struct CloseEventArgs : public ::Core::Event::Args::EventArgs
			{

			};
			struct FramebufferResetSizeEventArgs : public ::Core::Event::Args::EventArgs
			{
				FramebufferResetSizeEventArgs(int width, int height);

				int width = 0;
				int height = 0;
			};
		}

		namespace Input
		{
			struct MouseCurrsorMoveEventArgs : public ::Core::Event::Args::EventArgs
			{
				MouseCurrsorMoveEventArgs(double xPosition, double yPosition);

				double xPosition = 0;
				double yPosition = 0;
			};
			struct MouseScrollEventArgs : public ::Core::Event::Args::EventArgs
			{
				MouseScrollEventArgs(double xOffset, double yOffset);

				double xOffset = 0;
				double yOffset = 0;
			};
		}
	}

	struct Event
	{
		Event(::Core::Event::EventType type, const ::Core::Event::Args::EventArgs& args);

		const ::Core::Event::EventType type;
		const ::Core::Event::Args::EventArgs& args;
	};

	struct EventToken
	{
		EventToken(unsigned int id, EventType type);

		bool operator==(const EventToken& other) const noexcept
		{ 
			return id == other.id; 
		}

		const unsigned int id;
		const EventType type;
	};

	EventToken Subscribe(::Core::Event::EventType type, std::function<void(const ::Core::Event::Event&)> function);
	bool UnSubscribe(const Core::Event::EventToken& eventToken);
	void Emit(const ::Core::Event::Event& event);
}

namespace std
{
	template <>
	struct hash<Core::Event::EventToken>
	{
		std::size_t operator()(const Core::Event::EventToken& eventToken) const noexcept
		{
			return std::hash<unsigned int>()(eventToken.id);
		}
	};
}
#include"event/eventAPI.h"
#include"event/event.h"

Core::Event::EventToken Core::Event::Subscribe(::Core::Event::EventType type, std::function<void(const ::Core::Event::Event&)> function)
{
	return EventManager::Instance.Subscribe(type, std::move(function));
}
bool Core::Event::UnSubscribe(const Core::Event::EventToken& eventToken)
{
	return EventManager::Instance.UnSubscribe(eventToken);
}
void Core::Event::Emit(const ::Core::Event::Event& event)
{
	return EventManager::Instance.Emit(event);
}

Core::Event::Args::Window::FramebufferResetSizeEventArgs::FramebufferResetSizeEventArgs(int width, int height)
	:width(width), height(height) { }
Core::Event::Args::Input::MouseCurrsorMoveEventArgs::MouseCurrsorMoveEventArgs(double xPosition, double yPosition)
	:xPosition(xPosition), yPosition(yPosition) { }
Core::Event::Args::Input::MouseScrollEventArgs::MouseScrollEventArgs(double xOffset, double yOffset)
	:xOffset(xOffset), yOffset(yOffset) { }
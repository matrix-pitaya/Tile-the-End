#include"applicationAPI.h"
#include"engineAPI.h"
#include"log/logapi.h"
#include"console/console.h"
#include"utility/utility.h"
#include"thread/threadapi.h"

#include"tilltheend/game.h"
#include"opengl/renderer.h"
#include"pitaya/physics.h"
#include"opengl/window.h"
#include"perspective/camera.h"

void Application::Bootstrap()
{
	Core::Thread::RegisterThread("Main", std::this_thread::get_id());

	Core::Console::Print(Core::Color::Yellow, (Core::Utility::Date() + " Application Bootstrap Begin").c_str());
	Core::Log::Log(Core::Log::LogLevel::Info, "Application Bootstrap Begin");

	Engine::Module::RegisterGame("TilltheEnd", []()-> Game::TilltheEnd* {return new Game::TilltheEnd(); });
	Engine::Module::RegisterRenderer("OpenGLRenderer", []()->Renderer::OpenGLRenderer* {return new Renderer::OpenGLRenderer(); });
	Engine::Module::RegisterPhysics("PitayaPhysics", []()->Physics::PitayaPhysics* {return new Physics::PitayaPhysics(); });
	Engine::Module::RegisterWindow("OpenGLWindow", []()->Window::OpenGLWindow* {return new Window::OpenGLWindow(); });
	Engine::Module::RegisterCamera("PerspectiveCamera", []()->Camera::PerspectiveCamera* {return new Camera::PerspectiveCamera(); });

	Core::Console::Print(Core::Color::Yellow, (Core::Utility::Date() + " Application Bootstrap Begin").c_str());
	Core::Log::Log(Core::Log::LogLevel::Info, "Application Bootstrap End");
}

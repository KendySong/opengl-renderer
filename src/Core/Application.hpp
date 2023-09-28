#pragma once
#include <cstdint>

class Application
{
public :
	Application(Application&) = delete;
	static Application& instance();
	int run();
	
	std::uint32_t infoFps;

private :
	Application();
	static Application m_application;
};
#pragma once
class Application
{
public :
	Application(Application&) = delete;
	static Application& instance();
	int run();

private :
	Application();
	static Application m_application;
};
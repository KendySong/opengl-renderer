#include "Settings.hpp"

Settings Settings::m_instance;
Settings::Settings()
{
    width = 1280;
    height = 720;

    resolution = glm::vec2(width, height);
}

Settings& Settings::instance()
{
    return m_instance;
}

Settings& Settings::operator=(Settings&)
{
    return m_instance;
}
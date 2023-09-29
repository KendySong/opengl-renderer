#pragma once
#include <cstdint>
#include <glm/glm.hpp>

class Settings 
{
public :
    Settings& operator=(Settings&);
    static Settings& instance();

    std::uint32_t width;
    std::uint32_t height;
    glm::vec2 resolution;

private :
    static Settings m_instance;
    Settings();
};
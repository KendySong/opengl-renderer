#pragma once
#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>

enum class RenderMode : int
{
    Fill = GL_FILL,
    Wireframe = GL_LINE,
    Point = GL_POINT
};

class Settings 
{
public :
    Settings(const Settings&) = delete;

    RenderMode renderMode;

    std::uint32_t width;
    std::uint32_t height;
    glm::vec2 resolution;

    static Settings instance;

private :
    Settings();
};


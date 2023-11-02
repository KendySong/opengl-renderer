#include "Settings.hpp"

Settings Settings::instance;
Settings::Settings()
{
    width = 1280;
    height = 720;

    resolution = glm::vec2(width, height);
    renderMode = RenderMode::Fill;
}
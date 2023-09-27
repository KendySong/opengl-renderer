#pragma once
#include <cstdint>

class Texture
{
public :
    Texture();
    Texture(const char* imgPath);

    void bind() noexcept;

private :
    std::uint32_t m_id;
};
#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>

#include "Texture.hpp"

Texture::Texture()
{
    
}

Texture::Texture(const char* imgPath)
{
    std::fstream imgStream(imgPath);
    if (!imgStream.is_open())
    {
        std::cout << "[ERROR] Image path not found : " << imgPath << '\n';
    }

    int channel;
    glm::ivec2 imgSize;
    std::uint8_t* image = stbi_load(imgPath, &imgSize.x, &imgSize.y, &channel, 0);

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgSize.x, imgSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::bind() noexcept
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}
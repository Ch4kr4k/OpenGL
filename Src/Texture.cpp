#include "Texture.h"
#include "Vendor/stb_image/stb_image.h"
#include <iostream>

Texture::Texture(const std::string &path)
    : m_RenderID(0),
    m_FilePath(path),
    m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if (m_LocalBuffer) {
        std::cout << "Texture loaded: " << m_Width << "x" << m_Height << ", BPP: " << m_BPP << std::endl;
    }
    else {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    GLCall(glGenTextures(1, &m_RenderID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    //if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
}


Texture::~Texture()
{
	GLCall(glDeleteTextures(1, 0));
}

void Texture::Bind(u4 slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

//
// Created by manan on 06/08/2021.
//

#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace crescent

{
    OpenGLTexture::OpenGLTexture(const std::string &filePath, const std::string& type) : Texture(filePath, type) {

        // Load texture with stb_image.
        m_Data = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);

        if (m_Data)
        {
            CRESCENT_CORE_INFO("Loaded texture: {}", filePath);
        }
        else
        {
            CRESCENT_CORE_INFO("Texture loading error : {}", filePath);
        }
    }

    OpenGLTexture::OpenGLTexture(int width, int height, GLenum gl_format) :
    m_Width(width), m_Height(height)
    {
        // Generate texture
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, gl_format, m_Width, m_Height, 0, gl_format, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    }

    void OpenGLTexture::GenerateTexture() {

        // Upload Texture data to GPU
        glGenTextures(1, &m_TextureID);

        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        if (m_Data)
        {
            GLenum format;
            switch (m_NrChannels)
            {
                case 1: format = GL_RED;break;
                case 3: format = GL_RGB;break;
                case 4: format = GL_RGBA;break;
                default: format = GL_RGB;break;
            }
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
            glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Data);
            glGenerateMipmap(GL_TEXTURE_2D);

        }
        glBindTexture(GL_TEXTURE_2D, 0);

    }

    void OpenGLTexture::BindTextureUnit(ShaderProgram& shader, const std::string& name, uint32_t unit) {
        // Get uniform location
        shader.SetUniformInt(name, unit);
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

    }

    void OpenGLTexture::Release() {
        stbi_image_free(m_Data); // free data from the cpu as it is not needed anymore
        glDeleteTextures(1, &m_TextureID);
    }



}
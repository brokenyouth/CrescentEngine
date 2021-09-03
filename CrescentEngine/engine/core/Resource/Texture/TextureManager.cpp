//
// Created by manan on 05/08/2021.
//

#include "TextureManager.h"

namespace crescent
{

    TextureManager::TextureManager() : ResourceManager() {
    }

    OpenGLTexturePtr TextureManager::CreateTextureFromFile(const std::string &filePath, const std::string& type) {

        // opengl for now
        return std::static_pointer_cast<OpenGLTexture>(CreateResourceFromFile(filePath, type));

    }

    Resource *TextureManager::LoadResourceFromFile(const std::string &filePath, const std::string& type) {
        // opengl for now
        return new OpenGLTexture(filePath, type);
    }

    void TextureManager::Release() {
        ResourceManager::Release();
        CRESCENT_CORE_INFO("Texture Manager released.");
    }

}
//
// Created by manan on 05/08/2021.
//

#ifndef CRESCENTENGINE_TEXTUREMANAGER_H
#define CRESCENTENGINE_TEXTUREMANAGER_H

#include "../ResourceManager.h"
#include "Texture.h"
#include "OpenGLTexture.h"


namespace crescent
{

    class TextureManager : public ResourceManager {

    public:
        TextureManager() ;
        virtual ~TextureManager() {};
        void                                                    Release();

    public:
        OpenGLTexturePtr                                        CreateTextureFromFile(const std::string &filePath, const std::string& type);
    protected:
        virtual Resource*                                       LoadResourceFromFile(const std::string& filePath, const std::string& type);
    };

}

#endif //CRESCENTENGINE_TEXTUREMANAGER_H

//
// Created by manan on 05/08/2021.
//

#include "Texture.h"


namespace crescent
{


    Texture::Texture(const std::string &filePath, const std::string& type) : Resource(filePath) {

        m_Type = type;

    }

    void Texture::Release() {

    }
}
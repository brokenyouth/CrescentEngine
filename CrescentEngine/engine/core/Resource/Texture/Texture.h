//
// Created by manan on 05/08/2021.
//

#ifndef CRESCENTENGINE_TEXTURE_H
#define CRESCENTENGINE_TEXTURE_H

#include "../Resource.h"

namespace crescent
{

    class Texture : public Resource {

    protected:
        int                                                     m_Width;
        int                                                     m_Height;
        int                                                     m_NrChannels;
        uint32_t                                                m_ID;
        std::string                                             m_Type;

    public:
        Texture() = default;
        Texture(const std::string& filePath, const std::string& type);
        virtual ~Texture() { Release(); };
    public:
        void                                                    Release() override;
        inline uint32_t                                         GetID() const { return m_ID; }
        inline const std::string&                               GetType() const { return m_Type; }


    };

    typedef std::shared_ptr<Texture> TexturePtr;
}

#endif //CRESCENTENGINE_TEXTURE_H

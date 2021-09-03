//
// Created by manan on 02/09/2021.
//

#ifndef CRESCENTENGINE_SHADOWMAP_H
#define CRESCENTENGINE_SHADOWMAP_H

#include "../../engine/core/Resource/Texture/OpenGLTexture.h"

namespace crescent
{

    class ShadowMap {
    private:
        int                                                                 m_Width;
        int                                                                 m_Height;
        uint32_t                                                            m_depthMapID; // Framebuffer ID
        OpenGLTexture*                                                      m_pTexture;
    public:
        ShadowMap(int w, int h);
        virtual ~ShadowMap() {};
    public:
        void                                                                Bind();
        void                                                                Release();

    };


}

#endif //CRESCENTENGINE_SHADOWMAP_H

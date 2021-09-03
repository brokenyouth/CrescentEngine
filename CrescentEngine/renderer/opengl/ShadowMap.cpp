//
// Created by manan on 02/09/2021.
//

#include "ShadowMap.h"

namespace crescent
{


    ShadowMap::ShadowMap(int w, int h) {

        m_Width = w;
        m_Height = h;

        // Create the framebuffer object to render the shadow map
        glGenFramebuffers(1, &m_depthMapID);

        // Create an empty texture to hold the depth map
        m_pTexture = new OpenGLTexture(m_Width, m_Height, GL_DEPTH_COMPONENT);

        // Link the framebuffer object and the depth map texture
        glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_pTexture->GetTextureID(), 0);

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void ShadowMap::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapID);
        glViewport(0, 0, m_Width, m_Height);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void ShadowMap::Release() {
        glDeleteFramebuffers(1, &m_depthMapID);
        m_pTexture->Release();
        delete m_pTexture;
    }


}
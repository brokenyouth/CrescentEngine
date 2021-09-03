//
// Created by manan on 26/07/2021.
//

#include "OpenGLRenderer.h"


namespace crescent
{

    OpenGLRenderer::~OpenGLRenderer() noexcept
    {
        Release();
    }

    void OpenGLRenderer::Initialize(const RendererInfo& render_info)
    {
        CRESCENT_CORE_INFO("Initializing OpenGL renderer. ");
        if (m_initialized)
            Release();

        m_window.Initialize(*render_info.p_WindowInfo);
        m_pWindow = &m_window;
        m_initialized = true;

        CRESCENT_CORE_INFO("OpenGL renderer initialized. ");
    }

    void OpenGLRenderer::Release()
    {
        if (m_initialized)
        {
            m_window.Release();
            m_pWindow = nullptr;

            m_initialized = false;
            CRESCENT_CORE_INFO("OpenGL renderer released. ");
        }
    }

    OpenGLWindow *OpenGLRenderer::GetWindow() {
        return &m_window;
    }

    void OpenGLRenderer::ClearScreen(const glm::vec3 &color) {
        glClearColor(color.x, color.y, color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

}
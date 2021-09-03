//
// Created by manan on 26/07/2021.
//

#ifndef CRESCENTENGINE_OPENGLRENDERER_H
#define CRESCENTENGINE_OPENGLRENDERER_H


#include "../IRenderer.h"
#include "OpenGLWindow.h"
#include "ShaderProgram.h"

#include "../../engine/core/Log/Log.h"

namespace crescent
{

    class OpenGLRenderer : public IRenderer
    {
    private:
        OpenGLWindow	m_window;

    public:
        ~OpenGLRenderer() override;
        void			Initialize(const RendererInfo& render_info) final;
        void			Release() final;
        OpenGLWindow*   GetWindow();
    public:
        void            ClearScreen(const glm::vec3& color) override;
    };

}

#endif //CRESCENTENGINE_OPENGLRENDERER_H

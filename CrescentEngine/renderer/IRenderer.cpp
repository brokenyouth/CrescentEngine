//
// Created by manan on 25/07/2021.
//

#include "IRenderer.h"

namespace crescent
{

    IWindow* IRenderer::GetWindow() const
    {
        return m_pWindow;
    }

}
//
// Created by manan on 25/07/2021.
//

#ifndef CRESCENTENGINE_IRENDERER_H
#define CRESCENTENGINE_IRENDERER_H

#include <glm/glm.hpp>
#include "IWindow.h"

namespace crescent
{
    enum ERendererType
    {
        OpenGL45,
        DirectX11,
        DirectX12,
        Vulkan
    };

    struct RendererInfo
    {
        ERendererType	eRenderType;
        WindowInfo*		p_WindowInfo;
    };

    class IRenderer
    {
    protected:
        IWindow*		m_pWindow = nullptr;
        bool			m_initialized = false;
    public:
        virtual ~IRenderer() = default;
    public:
        virtual void	Initialize(const RendererInfo& render_info) = 0;
        virtual void	Release() = 0;
        IWindow*		GetWindow() const;
    public:
        virtual void    ClearScreen(const glm::vec3& color) = 0;

    };

}


#endif //CRESCENTENGINE_IRENDERER_H

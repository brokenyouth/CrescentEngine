//
// Created by manan on 25/07/2021.
//

#ifndef CRESCENTENGINE_IWINDOW_H
#define CRESCENTENGINE_IWINDOW_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace crescent
{

    struct WindowInfo
    {
        int					width;
        int					height;
        const char*			title;
    };

    class IWindow
    {
    protected:
        GLFWwindow*			m_pWindow = nullptr;
        bool				m_initialized = false;
    public:
        virtual				~IWindow() = default;
    public:
        virtual void		Initialize(const WindowInfo& wnd_info) = 0;
        virtual void		Release() = 0;

        virtual GLFWwindow*	GetHandle();
        virtual bool        ShouldWindowClose() = 0;
    };

}


#endif //CRESCENTENGINE_IWINDOW_H

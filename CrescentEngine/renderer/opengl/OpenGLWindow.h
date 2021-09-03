//
// Created by manan on 25/07/2021.
//

#ifndef CRESCENTENGINE_OPENGLWINDOW_H
#define CRESCENTENGINE_OPENGLWINDOW_H


#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "../IWindow.h"
#include "../../engine/core/Log/Log.h"


namespace crescent
{
    void ErrorCallback(int error, const char* msg);

    class OpenGLWindow : public IWindow
    {
    public:
                            ~OpenGLWindow()		override;
        void				Initialize(const WindowInfo& wnd_info) final;
        void				Release() final;
        GLFWwindow*			GetHandle() override;
        bool                ShouldWindowClose() override;
    };

}

#endif //CRESCENTENGINE_OPENGLWINDOW_H

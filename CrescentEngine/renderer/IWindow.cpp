//
// Created by manan on 25/07/2021.
//

#include "IWindow.h"

namespace crescent
{

    GLFWwindow* IWindow::GetHandle()
    {
        return m_pWindow;
    }

}
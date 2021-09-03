//
// Created by manan on 18/08/2021.
//

#include "GLFWInputManager.h"

namespace crescent
{
    Input* Input::s_pInstance = nullptr;

    GLFWInputManager::GLFWInputManager(GLFWwindow *pWindow) {

        if (Input::s_pInstance == nullptr)
        {
            m_pWindow = pWindow;
            Input::s_pInstance = this;
            if(Input::s_pInstance)
                CRESCENT_CORE_INFO("Input Manager initialized.");
        }
        else
        {
            CRESCENT_CORE_INFO("Input Manager already initialized.");
        }
    }

    bool GLFWInputManager::IsKeyPressedImpl(int keyCode) {
        auto keyState = glfwGetKey(m_pWindow, keyCode);
        return ( keyState == GLFW_PRESS || keyState == GLFW_REPEAT );
    }

    bool GLFWInputManager::IsMouseButtonPressedImpl(int button) {
        auto mouseState = glfwGetMouseButton(m_pWindow, button);
        return ( mouseState == GLFW_PRESS );
    }

    std::pair<float, float> GLFWInputManager::GetMouseXYImpl() {
        double x, y;
        glfwGetCursorPos(m_pWindow, &x, &y);
        return std::make_pair( (float)x, (float)y );
    }

    void GLFWInputManager::Release() {
        if (Input::s_pInstance != nullptr)
        {
            delete Input::s_pInstance;
            Input::s_pInstance = nullptr;
            CRESCENT_CORE_INFO("Input Manager released.");
        }
        else
        {
            CRESCENT_CORE_INFO("Input Manager already released.");
        }
    }

}


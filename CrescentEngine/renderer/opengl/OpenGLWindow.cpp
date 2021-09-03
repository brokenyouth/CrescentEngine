//
// Created by manan on 25/07/2021.
//

#include "OpenGLWindow.h"

namespace crescent
{


    void ErrorCallback(int error , const char* msg)
    {
        CRESCENT_CORE_ERROR("An error has occured: {}" , msg);
    }

    OpenGLWindow::~OpenGLWindow() noexcept
    {
        Release();
    }

    void OpenGLWindow::Initialize(const WindowInfo& wnd_info)
    {
        CRESCENT_CORE_INFO("Initializing OpenGL window... ");
        // If already initialized, release
        if (m_initialized)
            Release();

        // Initialize GLFW
        if (!glfwInit())
        {
            CRESCENT_CORE_ERROR("Failed to initialize GLFW.");
            return;
        }

        glfwSetErrorCallback(ErrorCallback);
        glfwWindowHint(GLFW_SAMPLES , 4); // 4x AA
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 4); // Target OpenGL 4.5
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 5);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);

        // New window and create context
        m_pWindow = glfwCreateWindow(wnd_info.width , wnd_info.height , wnd_info.title , nullptr , nullptr);

        if (!m_pWindow) {
            CRESCENT_CORE_ERROR("Failed to create GLFW window.");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_pWindow);
        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            CRESCENT_CORE_ERROR("Failed to initialize GLEW.");
            glfwTerminate();
            return;
        }

        glfwSetInputMode(m_pWindow , GLFW_STICKY_KEYS , GL_TRUE);

        // if we're here then everything went fine.
        m_initialized = true;
        CRESCENT_CORE_INFO("OpenGL window initialized. ");

        CRESCENT_CORE_INFO("OpenGL version: {} ", glGetString(GL_VERSION));

    }

    void OpenGLWindow::Release()
    {
        if (m_initialized)
        {
            glfwDestroyWindow(m_pWindow);
            glfwTerminate();
            m_pWindow = nullptr;
            m_initialized = false;
            CRESCENT_CORE_INFO("OpenGL window released. ");
        }

    }

    GLFWwindow *OpenGLWindow::GetHandle() {
        return m_pWindow;
    }

    bool OpenGLWindow::ShouldWindowClose() {
        return glfwWindowShouldClose(m_pWindow);
    }


}
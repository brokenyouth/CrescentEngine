//
// Created by manan on 18/08/2021.
//

#ifndef CRESCENTENGINE_GLFWINPUTMANAGER_H
#define CRESCENTENGINE_GLFWINPUTMANAGER_H

#include <GLFW/glfw3.h>

#include "Input.h"
#include "InputCode.h"
#include "../core/Log/Log.h"

namespace crescent
{
    class GLFWInputManager : public Input {
    private:
        GLFWwindow*                                                 m_pWindow = nullptr;
    public:
        explicit GLFWInputManager(GLFWwindow*    pWindow);
        virtual ~GLFWInputManager() {};
    protected:
        bool                                                        IsKeyPressedImpl(int keyCode) override;
        bool                                                        IsMouseButtonPressedImpl(int button) override;
        std::pair<float, float>                                     GetMouseXYImpl() override;

    public:
        static void                                                 Release();

    };

    typedef GLFWInputManager InputManager; // remove this later on

}


#endif //CRESCENTENGINE_GLFWINPUTMANAGER_H

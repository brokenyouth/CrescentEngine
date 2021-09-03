//
// Created by manan on 26/07/2021.
//

#ifndef CRESCENTENGINE_RENDERINGENGINE_H
#define CRESCENTENGINE_RENDERINGENGINE_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "opengl/OpenGLRenderer.h"
#include "opengl/ShaderProgram.h"
#include "opengl/ShadowMap.h"
#include "opengl/Mesh.h"

#include "../engine/core/Shader/ShaderManager.h"
#include "../engine/core/Resource/Texture/TextureManager.h"
#include "../engine/core/Scene/SceneObject.h"
#include "../engine/core/Log/Log.h"
#include "../engine/core/Timer/Timer.h"

#include "../engine/input/GLFWInputManager.h"
#include "../engine/core/Camera/FreeFlyCamera.h"

#include "../engine/core/Lighting/DirectionalLight.h"

namespace crescent {

    class RenderingEngine {
    private:
        bool                                                    m_Initialized = false;
        IRenderer*                                              m_pRenderer = nullptr;
        Timer*                                                  m_Timer = nullptr;
        std::unique_ptr<SceneObject>                            m_SceneObject;

    private:
        glm::mat4                                               m_ProjectionMatrix;
    private:
        TextureManager*                                         m_pTextureManager = nullptr;
        InputManager*                                           m_pInputManager;
        std::unique_ptr<ShaderManager>                          m_pShaderManager;
        std::unique_ptr<FreeFlyCamera>                          m_Camera;
        DirectionalLight                                        m_DirectionalLight;
        ShadowMap                                               m_ShadowMap;

    public:
        RenderingEngine() = default;
        void                                                    Initialize(int width, int height, const char* title);
        void                                                    Release();
        void                                                    Run();
        void                                                    Update(float dt);
        void                                                    Draw();
        IRenderer*                                              GetRenderer() const;
        TextureManager*                                         GetTextureManager() const;

    };

}

#endif //CRESCENTENGINE_RENDERINGENGINE_H

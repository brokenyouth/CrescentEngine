//
// Created by manan on 26/07/2021.
//

#include "RenderingEngine.h"

#include <memory>

namespace crescent
{

    void RenderingEngine::Initialize(int width, int height, const char* title) {
        // Init logger
        Log::Init();

        CRESCENT_CORE_INFO("Initializing Rendering Engine.");
        WindowInfo w_info = {
                width,
                height,
                title
        };
        RendererInfo r_info = {
                OpenGL45,
                &w_info
        };
        CRESCENT_CORE_INFO("Initializing OpenGL.");
        m_pRenderer = new OpenGLRenderer();
        m_pRenderer->Initialize(r_info);
        m_Timer = new Timer();
        if(m_pRenderer)
            CRESCENT_CORE_INFO("Rendering engine initialized.");

        m_pTextureManager = new TextureManager();
        if(m_pTextureManager)
            CRESCENT_CORE_INFO("Texture Manager initialized.");

        m_pInputManager = new GLFWInputManager(GetRenderer()->GetWindow()->GetHandle());


        // TODO: Move this to GL renderer class
        glEnable   (GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable   (GL_CULL_FACE);
        glCullFace (GL_BACK);
        glFrontFace(GL_CCW);
        glEnable   (GL_MULTISAMPLE);
        glEnable   (GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_pShaderManager = std::make_unique<ShaderManager>();
        m_pShaderManager->Initialize();
        m_Camera = std::make_unique<FreeFlyCamera>(m_pInputManager, glm::vec3(0.f, 0.f, 0.f));
        Model backpackMdl = Model(m_pTextureManager);
        backpackMdl.LoadModel("./game/models/sponza/sponza.gltf");

        m_DirectionalLight = DirectionalLight();
        m_ShadowMap = ShadowMap(1024, 1024);
        m_SceneObject = std::make_unique<SceneObject>(backpackMdl, glm::vec3(0.0f, 0.0f, 0.0f),
                                                      glm::vec3(1.0f, 1.0f, 1.0f),
                                                      glm::vec3(0.f, 0.0f, 0.0f));

        m_ProjectionMatrix = glm::perspective(glm::radians(90.f), (float)width/height, 0.1f, 9000.f);
        m_Initialized = true;

    }

    void RenderingEngine::Release() {
        if(m_Initialized)
        {
            if(m_pRenderer)
            {
                m_SceneObject->Release();
                m_ShadowMap.Release();
                m_pRenderer->Release();
                m_pTextureManager->Release();
                m_pShaderManager->Release();
                crescent::InputManager::Release();
                delete m_pRenderer; m_pRenderer = nullptr;
                delete m_pTextureManager; m_pTextureManager = nullptr;
            }
            delete m_Timer; m_Timer = nullptr;
            m_Initialized = false;
            CRESCENT_CORE_INFO("Rendering engine released.");
        }

    }

    void RenderingEngine::Update(float dt) {
        //m_SceneObject->SetRotation(/*(m_SceneObject->GetRotation().x) + dt * 3.1415f/5.f*/0.f, (m_SceneObject->GetRotation().y) + dt * 3.1415f/2.f, 0.f);
        m_DirectionalLight.SetDirection(glm::vec3(0.f, m_DirectionalLight.GetDirection().y + dt * 3.1415f, 0.f));
        m_Camera->Update(dt);
    }

    void RenderingEngine::Draw() {
        GLFWwindow * m_pWindowHandle = (m_pRenderer->GetWindow())->GetHandle();

        // Render shadow map
        ShaderProgram* shadowShader = m_pShaderManager->GetShader("shadowShader");
        m_ShadowMap.Bind();
        shadowShader->Bind();
        glm::vec3 lightDir = m_DirectionalLight.GetDirection();
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 9.0f);
        glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 10.0f, -1.0f),
                                          glm::vec3( 0.0f, 0.0f,  0.0f),
                                          glm::vec3( 0.0f, 1.0f,  0.0f));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;
        shadowShader->SetUniformMat4("projectionMatrix", lightSpaceMatrix);
        m_ShadowMap.
        m_SceneObject->Draw(shadowShader);
        shadowShader->Unbind();
        // end shadow map

        // Retrieve and set original window size
        int width, height;
        glfwGetWindowSize(m_pWindowHandle, &width, &height);
        glViewport(0, 0, width, height);
        // Render scene
        ShaderProgram* lightShader = m_pShaderManager->GetShader("lightShader");
        lightShader->Bind();
        lightShader->SetUniformMat4("projectionMatrix", m_ProjectionMatrix);
        lightShader->SetUniformMat4("viewMatrix", m_Camera->GetView());
        lightShader->SetUniformVec3("cameraPosition", m_Camera->GetPosition());
        lightShader->SetUniformVec3("light.direction", m_DirectionalLight.GetDirection());
        lightShader->SetUniformVec3("light.diffuse", m_DirectionalLight.GetDiffuse());
        lightShader->SetUniformVec3("light.ambient", m_DirectionalLight.GetAmbient());
        lightShader->SetUniformVec3("light.specular", m_DirectionalLight.GetSpecular());
        lightShader->SetUniformFloat("light.intensity", m_DirectionalLight.GetIntensity());
        //m_SceneObject->Draw(lightShader);
        lightShader->Unbind();

    }


    void RenderingEngine::Run() {
        // TODO: encapsulate window handle?
        GLFWwindow * m_pWindowHandle = (m_pRenderer->GetWindow())->GetHandle();
        glfwSetInputMode(m_pWindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetInputMode(m_pWindowHandle, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
        // fps limit
        const double fpsLimit = 1.0 / 144.0;
        double lastUpdateTime = 0;  // number of seconds since the last loop
        double lastFrameTime = 0;   // number of seconds since the last frame

        // main loop
        while (!(m_pRenderer->GetWindow())->ShouldWindowClose())
        {
            double now = glfwGetTime();
            double deltaTime = 0;

            glfwPollEvents();

            if ((now - lastFrameTime) >= fpsLimit)
            {
                deltaTime = m_Timer->GetDeltaTime();
                int fps = static_cast<int> (1 / (deltaTime));
                //CRESCENT_INFO("FPS: {}" , fps);
                m_Timer->Reset();

                // update
                // ------
                Update((float)deltaTime);

                // !update

                // render
                // ------
                m_pRenderer->ClearScreen(glm::vec3(0.0f, 0.0f, 0.0f));

                Draw();
                // !render

                // glfw specific
                // ------
                glfwSwapBuffers(m_pWindowHandle);
                // !glfw specific

                // only set lastFrameTime when you actually draw something
                lastFrameTime = now;

            }
            // set lastUpdateTime every iteration
            lastUpdateTime = now;
            //Sleep(1);

        }

    }

    TextureManager* RenderingEngine::GetTextureManager() const {
        return m_pTextureManager;
    }

    IRenderer *RenderingEngine::GetRenderer() const {
        return m_pRenderer;
    }


}
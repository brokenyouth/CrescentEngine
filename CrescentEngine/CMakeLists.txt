cmake_minimum_required(VERSION 3.19)

project(CrescentEngine)

add_executable(CrescentEngine main.cpp ../thirdparty/stb_image.h engine/core/Log/Log.cpp engine/core/Log/Log.h renderer/IWindow.cpp renderer/IWindow.h renderer/IRenderer.cpp renderer/IRenderer.h renderer/opengl/OpenGLWindow.cpp renderer/opengl/OpenGLWindow.h renderer/opengl/OpenGLRenderer.cpp renderer/opengl/OpenGLRenderer.h renderer/RenderingEngine.cpp renderer/RenderingEngine.h engine/core/Timer/Timer.cpp engine/core/Timer/Timer.h renderer/opengl/ShaderProgram.cpp renderer/opengl/ShaderProgram.h renderer/opengl/Mesh.cpp renderer/opengl/Mesh.h engine/core/Vertex.h engine/core/Scene/SceneObject.cpp engine/core/Scene/SceneObject.h engine/core/Scene/Prefab/Cube.h engine/core/Resource/ResourceManager.cpp engine/core/Resource/ResourceManager.h engine/core/Resource/Resource.cpp engine/core/Resource/Resource.h engine/core/Resource/Texture/Texture.cpp engine/core/Resource/Texture/Texture.h engine/core/Resource/Texture/TextureManager.cpp engine/core/Resource/Texture/TextureManager.h engine/core/Resource/Texture/OpenGLTexture.cpp engine/core/Resource/Texture/OpenGLTexture.h engine/core/Model/Model.cpp engine/core/Model/Model.h engine/input/Input.h engine/input/GLFWInputManager.cpp engine/input/GLFWInputManager.h engine/input/InputCode.h engine/core/Camera/Camera.h engine/core/Camera/Camera.cpp engine/core/Camera/FreeFlyCamera.cpp engine/core/Camera/FreeFlyCamera.h engine/CustomMath.h engine/core/Shader/ShaderManager.cpp engine/core/Shader/ShaderManager.h engine/core/Lighting/DirectionalLight.cpp engine/core/Lighting/DirectionalLight.h renderer/opengl/ShadowMap.cpp renderer/opengl/ShadowMap.h)

target_link_libraries(CrescentEngine
        glfw
        libglew_static
        assimp
)
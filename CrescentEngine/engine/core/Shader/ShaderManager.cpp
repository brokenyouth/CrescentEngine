//
// Created by manan on 22/08/2021.
//

#include "ShaderManager.h"

namespace crescent

{
    ShaderManager* ShaderManager::m_pInstance = nullptr;

    void ShaderManager::Initialize() {
        if(ShaderManager::m_pInstance == nullptr)
        {
            ShaderManager::m_pInstance = new ShaderManager();
            CRESCENT_CORE_INFO("Shader Manager initialized.");
        } else
        {
            CRESCENT_CORE_INFO("Shader Manager already initialized.");
        }

        AddShader("defaultShader", ShaderProgram("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl"));
        ShaderManager::m_pInstance->m_ShaderMap["defaultShader"].CreateUniform("projectionMatrix");
        ShaderManager::m_pInstance->m_ShaderMap["defaultShader"].CreateUniform("viewMatrix");
        ShaderManager::m_pInstance->m_ShaderMap["defaultShader"].CreateUniform("modelMatrix");
        ShaderManager::m_pInstance->m_ShaderMap["defaultShader"].CreateUniform("diffuse0");


        AddShader("lightShader", ShaderProgram("shaders/Lighting/lightingVertex.glsl", "shaders/Lighting/lightingFragment.glsl"));
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("projectionMatrix");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("viewMatrix");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("modelMatrix");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("cameraPosition");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("material.diffuse");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("material.specular");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("material.shininess");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("light.ambient");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("light.diffuse");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("light.direction");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("light.specular");
        ShaderManager::m_pInstance->m_ShaderMap["lightShader"].CreateUniform("light.intensity");

        AddShader("shadowShader", ShaderProgram("shaders/Shadow/shadowVertex.glsl", "shaders/Lighting/shadowFragment.glsl"));
        ShaderManager::m_pInstance->m_ShaderMap["shadowShader"].CreateUniform("modelMatrix");
        ShaderManager::m_pInstance->m_ShaderMap["shadowShader"].CreateUniform("projectionMatrix");


    }

    void ShaderManager::AddShader(const std::string& name, ShaderProgram shader) {
        auto iterator = ShaderManager::m_pInstance->m_ShaderMap.find(name);

        // if this shader has already been loaded / created, do nothing;
        if ( iterator != ShaderManager::m_pInstance->m_ShaderMap.end() )
            return;

        ShaderManager::m_pInstance->m_ShaderMap.emplace(name, shader);

    }

    void ShaderManager::RemoveShader(const std::string &name) {
        auto iterator = ShaderManager::m_pInstance->m_ShaderMap.find(name);
        if ( iterator != ShaderManager::m_pInstance->m_ShaderMap.end() )
            ShaderManager::m_pInstance->m_ShaderMap.erase(iterator);
    }

    ShaderProgram* ShaderManager::GetShader(const std::string &name) const {
        auto iterator = ShaderManager::m_pInstance->m_ShaderMap.find(name);
        if ( iterator != ShaderManager::m_pInstance->m_ShaderMap.end() )
            return &(iterator->second);
        return nullptr;
    }

    void ShaderManager::Release() {
        if(ShaderManager::m_pInstance)
        {
            delete ShaderManager::m_pInstance; ShaderManager::m_pInstance = nullptr;
            CRESCENT_CORE_INFO("Shader Manager released.");
        } else
        {
            CRESCENT_CORE_INFO("Shader Manager already released.");
        }

    }
}
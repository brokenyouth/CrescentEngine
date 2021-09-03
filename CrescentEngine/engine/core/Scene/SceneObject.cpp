//
// Created by manan on 03/08/2021.
//

#include "SceneObject.h"

namespace crescent
{

    SceneObject::SceneObject(const Model& model, const glm::vec3 &position, const glm::vec3 &scale,
                             const glm::vec3 &rotation){

        m_Model = model;
        m_ModelMatrix = glm::mat4(1.0f);
        SetPosition(position.x, position.y, position.z);
        SetRotation(rotation.x, rotation.y, rotation.z);
        SetScale(scale.x, scale.y, scale.z);

    }

    void SceneObject::Draw(ShaderProgram* pShader) {
        ApplyModelMatrix();
        pShader->SetUniformMat4("modelMatrix", m_ModelMatrix);
        m_Model.Draw(*pShader);
    }

    void SceneObject::Release() {
        m_Model.CleanUp();
    }

    void SceneObject::SetPosition(float x, float y, float z)  {
        m_Translation.x = x;
        m_Translation.y = y;
        m_Translation.z = z;
        m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation);

    }

    void SceneObject::SetScale(float x, float y, float z)  {
        m_Scale.x = x;
        m_Scale.y = y;
        m_Scale.z = z;
        m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);

    }

    void SceneObject::SetRotation(float x, float y, float z)  {
        m_Rotation.x = x;
        m_Rotation.y = y;
        m_Rotation.z = z;

    }

    const glm::vec3 &SceneObject::GetPosition() const {
        return m_Translation;
    }

    const glm::vec3 &SceneObject::GetScale() const {
        return m_Scale;
    }

    const glm::vec3 &SceneObject::GetRotation() const {
        return m_Rotation;
    }

    const Model &SceneObject::GetModel() const {
        return m_Model;
    }

    SceneObject::~SceneObject() {
        Release();
    }

    void SceneObject::ApplyModelMatrix() {
        // Apply translation
        m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_Translation);

        // Apply rotation
        if (m_Rotation.x != 0.f)
        {
            m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if (m_Rotation.y != 0.f)
        {
            m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (m_Rotation.z != 0.f)
        {
            m_ModelMatrix = glm::rotate(m_ModelMatrix, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        }

        // Apply scaling
        m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);

    }
}
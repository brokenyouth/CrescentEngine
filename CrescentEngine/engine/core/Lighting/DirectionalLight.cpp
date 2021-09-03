//
// Created by manan on 22/08/2021.
//

#include "DirectionalLight.h"

namespace crescent

{

    DirectionalLight::DirectionalLight() {
        m_Position = glm::vec3(1.2f, 50.0f, 2.0f);
        m_Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
        m_Ambient = glm::vec3(0.6f, 0.6f, 0.6f);
        m_Diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        m_Specular = glm::vec3(0.7f, 0.7f, 0.7f);
        m_LightIntensity = 1.f;

    }

    glm::mat4 DirectionalLight::GetModelMatrix() const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, m_Position);
        return model;
    }

}
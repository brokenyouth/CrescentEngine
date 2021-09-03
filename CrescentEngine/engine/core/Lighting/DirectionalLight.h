//
// Created by manan on 22/08/2021.
//

#ifndef CRESCENTENGINE_DIRECTIONALLIGHT_H
#define CRESCENTENGINE_DIRECTIONALLIGHT_H


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace crescent
{

    class DirectionalLight {
    private:
        glm::vec3                                                                                       m_Position;
        glm::vec3                                                                                       m_Direction;
        glm::vec3                                                                                       m_Diffuse;
        glm::vec3                                                                                       m_Ambient;
        glm::vec3                                                                                       m_Specular;
        float                                                                                           m_LightIntensity;
    public:
        DirectionalLight();
        virtual ~DirectionalLight() {};
    public:
        inline void                                                                                     SetPosition(const glm::vec3 & newPosition) { m_Position = newPosition; };
        inline void                                                                                     SetDirection(const glm::vec3 & newDirection) { m_Direction = newDirection; };
        inline void                                                                                     SetDiffuse(const glm::vec3 & newColor) { m_Diffuse = newColor; };
        inline void                                                                                     SetAmbient(const glm::vec3 & newAmbient) { m_Ambient = newAmbient; };
        inline void                                                                                     SetSpecular(const glm::vec3 & newSpecular) { m_Specular = newSpecular; };
        inline void                                                                                     SetLightIntensity(float newIntensity) { m_LightIntensity = newIntensity; };
        glm::mat4                                                                                       GetModelMatrix() const;
        inline const glm::vec3&                                                                         GetPosition() const { return m_Position;} ;
        inline const glm::vec3&                                                                         GetDirection() const { return m_Direction;} ;
        inline const glm::vec3&                                                                         GetDiffuse() const { return m_Diffuse;} ;
        inline const glm::vec3&                                                                         GetAmbient() const { return m_Ambient;} ;
        inline const glm::vec3&                                                                         GetSpecular() const { return m_Specular;} ;
        inline float                                                                                    GetIntensity() const { return m_LightIntensity;} ;

    };

}


#endif //CRESCENTENGINE_DIRECTIONALLIGHT_H

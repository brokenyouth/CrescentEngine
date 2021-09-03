//
// Created by manan on 03/08/2021.
//

#ifndef CRESCENTENGINE_SCENEOBJECT_H
#define CRESCENTENGINE_SCENEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Model/Model.h"
#include "../../../renderer/opengl/ShaderProgram.h"


namespace crescent {

    class SceneObject {
    private:
        glm::vec3                                                                   m_Translation;
        glm::vec3                                                                   m_Scale;
        glm::vec3                                                                   m_Rotation;
        glm::mat4                                                                   m_ModelMatrix;
        Model                                                                       m_Model;
    public:
        SceneObject(const Model& model, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation);
        virtual ~SceneObject();
    public:
        void                                                                        Draw(ShaderProgram* pShader);
        void                                                                        Release();
    public:
        void                                                                        SetPosition(float x, float y, float z) ;
        void                                                                        SetScale(float x, float y, float z) ;
        void                                                                        SetRotation(float x, float y, float z) ;

        const glm::vec3&                                                            GetPosition() const;
        const glm::vec3&                                                            GetScale() const;
        const glm::vec3&                                                            GetRotation() const;
        const Model&                                                                GetModel() const;
        void                                                                        ApplyModelMatrix();

    };

}
#endif //CRESCENTENGINE_SCENEOBJECT_H
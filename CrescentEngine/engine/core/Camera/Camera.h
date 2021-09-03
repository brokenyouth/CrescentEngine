//
// Created by manan on 19/08/2021.
//

#ifndef CRESCENTENGINE_CAMERA_H
#define CRESCENTENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../input/GLFWInputManager.h"


namespace crescent

{

    class Camera
    {
    public:
        InputManager*   pInputManager;
        glm::mat4 Projection;
        glm::mat4 View;

        glm::vec3 Position = glm::vec3(0.0f, 0.0f,  0.0f);
        glm::vec3 Forward  = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up       = glm::vec3(0.0f, 1.0f,  0.0f);
        glm::vec3 Right    = glm::vec3(1.0f, 0.0f,  0.0f);

        float FOV;
        float Aspect;
        float Near;
        float Far;
        bool  Perspective;
    public:
        Camera() = default;
        Camera(InputManager* pIM, const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up);

        void Update(float dt);

        void SetPerspective(float fov, float aspect, float znear, float zfar);
        void UpdateView();
        inline const glm::vec3&  GetPosition() const { return Position; };


    };

}



#endif //CRESCENTENGINE_CAMERA_H

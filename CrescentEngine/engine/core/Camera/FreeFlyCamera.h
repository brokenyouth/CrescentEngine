//
// Created by manan on 21/08/2021.
//

#ifndef CRESCENTENGINE_FREEFLYCAMERA_H
#define CRESCENTENGINE_FREEFLYCAMERA_H

#include "Camera.h"
#include "../../CustomMath.h"

namespace crescent
{
    class FreeFlyCamera : public Camera {

    public:
        float Yaw;
        float Pitch;

        float MovementSpeed   = 500.0f;
        float MouseSensitivty =  0.1f;
        float Damping         =  5.0f;
    private:
        glm::vec3 m_TargetPosition;
        glm::vec3 m_WorldUp;
        glm::vec2 m_MousePosition;
        float m_TargetYaw;
        float m_TargetPitch;
        bool firstMouse;
    public:
        FreeFlyCamera(InputManager* pIM, glm::vec3 position, glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

        virtual void Update(float dt);

        virtual void InputKey(float dt);
        virtual void InputMouse();
        virtual void InputScroll(float deltaX, float deltaY);
        inline glm::mat4 GetView() {
            return glm::lookAt(Position, Position + Forward, Up );
        }
    };

}


#endif //CRESCENTENGINE_FREEFLYCAMERA_H

//
// Created by manan on 21/08/2021.
//

#include "FreeFlyCamera.h"
#include <math.h>

namespace crescent

{


    FreeFlyCamera::FreeFlyCamera(InputManager* pIM, glm::vec3 position, glm::vec3 forward, glm::vec3 up) {
        pInputManager = pIM;
        Yaw = -90.0f;
        Pitch = 0.f;
        Forward = forward;
        m_WorldUp = Up;
        m_TargetPosition = position;
        m_MousePosition = glm::vec2(1600/2.f, 900/2.f);
        firstMouse = true;
    }

    void FreeFlyCamera::Update(float dt) {
        InputKey(dt);
        InputMouse();
        // slowly interpolate to target position each frame given some damping factor.
        // this gives smooth camera movement that fades out the closer we are to our target.
        Position = lerp(Position, m_TargetPosition, glm::clamp(dt * Damping, 0.f, 1.f));
        Yaw      = lerp(Yaw, m_TargetYaw, glm::clamp(dt * Damping * 250.0f, 0.f, 1.f));
        Pitch    = lerp(Pitch, m_TargetPitch, glm::clamp(dt * Damping * 250.0f, 0.f, 1.f));

        // calculate new cartesian basis vectors from yaw/pitch pair:
        glm::vec3 newForward;
        newForward.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
        newForward.y = glm::sin(glm::radians(Pitch));
        newForward.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
        Forward = glm::normalize(newForward);
        Right = glm::normalize(glm::cross(Forward, m_WorldUp));
        Up = glm::cross(Right, Forward);

        // calculate the new view matrix
        UpdateView();
    }

    void FreeFlyCamera::InputKey(float dt) {

        float speed = MovementSpeed * dt;
        if (crescent::InputManager::IsKeyPressed(CR_KEY_W))
        {
            m_TargetPosition = m_TargetPosition + Forward * speed;
        }
        if (crescent::InputManager::IsKeyPressed(CR_KEY_S))
        {
            m_TargetPosition = m_TargetPosition - Forward * speed;
        }
        if (crescent::InputManager::IsKeyPressed(CR_KEY_D))
        {
            m_TargetPosition = m_TargetPosition + Right * speed;
        }
        if (crescent::InputManager::IsKeyPressed(CR_KEY_A))
        {
            m_TargetPosition = m_TargetPosition - Right * speed;
        }

    }

    void FreeFlyCamera::InputMouse() {

        auto [x , y] = crescent::InputManager::GetMouseXY();
        if (firstMouse)
        {
            m_MousePosition.x = x;
            m_MousePosition.y = y;
            firstMouse = false;
        }

        float xoffset = x - m_MousePosition.x;
        float yoffset = m_MousePosition.y - y;

        float xmovement = xoffset * MouseSensitivty;
        float ymovement = yoffset * MouseSensitivty;
        m_MousePosition.x = x;
        m_MousePosition.y = y;

        m_TargetYaw   = glm::mod(m_TargetYaw + xmovement, 360.f);
        m_TargetPitch += ymovement;

        if(m_TargetYaw == 0.0f) m_TargetYaw = 0.01f;
        if(m_TargetPitch == 0.0f) m_TargetPitch = 0.01f;

        if (m_TargetPitch > 89.f)  m_TargetPitch =  89.f;
        if (m_TargetPitch < -89.f) m_TargetPitch = -89.f;


    }

    void FreeFlyCamera::InputScroll(float deltaX, float deltaY) {

    }
}
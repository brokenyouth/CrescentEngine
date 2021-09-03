//
// Created by manan on 19/08/2021.
//

#include "Camera.h"

namespace crescent


{

    Camera::Camera(InputManager* pIM, const glm::vec3 &position, const glm::vec3 &forward, const glm::vec3 &up) {
            pInputManager = pIM;
            Position = position;
            Forward = forward;
            Up = up;
            UpdateView();
    }

    void Camera::SetPerspective(float fov, float aspect, float znear, float zfar) {
            Projection = glm::perspective(fov, aspect, znear, zfar);
            FOV = fov;
            Aspect = aspect;
            Near = znear;
            Far = zfar;
            Perspective = true;
    }

    void Camera::Update(float dt) {
    }

    void Camera::UpdateView() {
            View = glm::lookAt(Position, Position + Forward, Up );
    }

}
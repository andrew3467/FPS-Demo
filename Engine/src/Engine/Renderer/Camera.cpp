//
// Created by Andrew Graser on 4/30/2024.
//

#include "Camera.h"


#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


#define CAMERA_MIN_ZOOM 1.0f
#define CAMERA_MAX_ZOOM 90.0f

#define CAMERA_MIN_PITCH -89.0f
#define CAMERA_MAX_PITCH 89.0f



namespace Engine {
    Camera::Camera()
            : Camera({0.0f, 0.0f, 0.0f}, 16.f / 9.f) {

    }

    Camera::Camera(const glm::vec3 &position, float aspect)
            : mAspect(aspect), mNear(0.1f), mFar(1000.0f) {
        mProjection = glm::perspective(glm::radians(mFOV), mAspect, mNear, mFar);

        SetPosition(position);
    }

    Camera::~Camera() {

    }

    void Camera::RecalculateMatrices() {
        glm::vec3 front = {
                cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)),
                sin(glm::radians(mPitch)),
                sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))
        };

        mFront = glm::normalize(front);

        mRight = glm::normalize(glm::cross(mFront, mWorldUp));
        mUp = glm::normalize(glm::cross(mRight, mFront));

        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjection = glm::perspective(glm::radians(mFOV), mAspect, mNear, mFar);
        mViewProjection = mProjection * mView;
    }

    void Camera::SetRotation(const glm::vec3 &rotation) {
        mFront = glm::normalize(rotation);

        mRight = glm::normalize(glm::cross(mFront, glm::vec3(0.0f, 1.0f, 0.0f)));
        mUp = glm::normalize(glm::cross(mRight, mFront));
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, bool constrainPitch) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        mYaw += xoffset;
        mPitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            mPitch = glm::clamp(mPitch, CAMERA_MIN_PITCH, CAMERA_MAX_PITCH);
        }

        RecalculateMatrices();
    }

    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime, float moveSpeed) {
        float velocity = moveSpeed * deltaTime;
        if (direction == FORWARD)
            mPosition += mFront * velocity;
        if (direction == BACKWARD)
            mPosition -= mFront * velocity;
        if (direction == LEFT)
            mPosition -= mRight * velocity;
        if (direction == RIGHT)
            mPosition += mRight * velocity;

        RecalculateMatrices();
    }

    void Camera::ProcessMouseScroll(float yoffset) {
        mFOV -= (float) yoffset;
        mFOV = glm::clamp(mFOV, CAMERA_MIN_ZOOM, CAMERA_MAX_ZOOM);
    }
}
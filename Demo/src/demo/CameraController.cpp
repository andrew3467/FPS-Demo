//
// Created by Andrew Graser on 4/30/2024.
//

#include "CameraController.h"
#include "Engine/Core/Input.h"
#include "Engine/Core/Engine.h"

#include "GLFW/glfw3.h"
#include "Engine/Renderer/Camera.h"


namespace Demo {
    CameraController::CameraController(float moveSpeed, float sensitivity)
            : mMoveSpeed(moveSpeed), mSensitivity(sensitivity) {
        mCamera = std::make_shared<Engine::Camera>(glm::vec3(0.0f, 0.0f, 3.0f), 1280.0f / 720.0f);
    }

    CameraController::~CameraController() {

    }

    void CameraController::ProcessInput() {
        KeyboardInput();
        MouseInput();
    }

    void CameraController::KeyboardInput() {

        if (Engine::Input::IsKeyPressed(GLFW_KEY_W)) {
            mCamera->ProcessKeyboard(Engine::Camera_Movement::FORWARD, 1, mMoveSpeed);
        }
        if (Engine::Input::IsKeyPressed(GLFW_KEY_S)) {
            mCamera->ProcessKeyboard(Engine::Camera_Movement::BACKWARD, 1, mMoveSpeed);
        }
        if (Engine::Input::IsKeyPressed(GLFW_KEY_A)) {
            mCamera->ProcessKeyboard(Engine::Camera_Movement::LEFT, 1, mMoveSpeed);
        }
        if (Engine::Input::IsKeyPressed(GLFW_KEY_D)) {
            mCamera->ProcessKeyboard(Engine::Camera_Movement::RIGHT, 1, mMoveSpeed);
        }
    }

    void CameraController::MouseInput() {

        if (Engine::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
            Engine::Engine::Get().GetWindow().ToggleCursor(false);
            auto [x, y] = Engine::Input::GetMousePos();

            if (mFirstMouse) {
                mLastX = x;
                mLastY = y;

                mFirstMouse = false;
            }

            if (mFirstScrollDown) {
                Engine::Input::SetMousePos(mLastX, mLastY);
                mFirstScrollDown = false;
            }

            float xOffset = x - mLastX;
            float yOffset = mLastY - y;

            mLastX = x;
            mLastY = y;

            mCamera->ProcessMouseMovement(xOffset, yOffset, mSensitivity * 1);
        } else {
            Engine::Engine::Get().GetWindow().ToggleCursor(true);
            if (!mFirstScrollDown) {
                mFirstScrollDown = true;
            }
        }
    }
}

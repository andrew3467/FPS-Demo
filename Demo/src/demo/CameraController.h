//
// Created by Andrew Graser on 4/30/2024.
//

#ifndef FPS_DEMO_CAMERACONTROLLER_H
#define FPS_DEMO_CAMERACONTROLLER_H

#include <memory>

namespace Engine {
    class Camera;
}


namespace Demo {
    class CameraController {
    public:
        CameraController(float moveSpeed, float sensitivity);

        ~CameraController();

        inline std::shared_ptr<Engine::Camera> GetCamera() const { return mCamera; }

        void ProcessInput();

    private:
        void KeyboardInput();
        void MouseInput();

    private:
        std::shared_ptr<Engine::Camera> mCamera;

        float mMoveSpeed;
        float mSensitivity;

        float mLastX, mLastY;

        bool mFirstMouse = true;
        bool mFirstScrollDown = true;
    };
}


#endif //FPS_DEMO_CAMERACONTROLLER_H

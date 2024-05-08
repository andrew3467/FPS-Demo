//
// Created by Andrew Graser on 4/25/2024.
//

#ifndef FPS_DEMO_APPLICATION_H
#define FPS_DEMO_APPLICATION_H

#include "CameraController.h"

namespace Demo {
    class Application {
    public:
        Application() = default;
        ~Application() = default;

        static Application &GetInstance() { return *sInstance; }

        void Run();

    private:
        void Init();

        void Update();
        void Render();

    private:
        static Application *sInstance;


    private:
        std::unique_ptr<CameraController> mCamController;


    };
}


#endif //FPS_DEMO_APPLICATION_H

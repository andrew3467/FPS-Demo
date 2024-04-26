//
// Created by Andrew Graser on 4/25/2024.
//

#ifndef FPS_DEMO_APPLICATION_H
#define FPS_DEMO_APPLICATION_H

namespace Demo {
    class Application {
    public:
        Application() = default;
        ~Application() = default;

        static Application &GetInstance() { return *sInstance; }

        void Run();

        void OnEvent();

    private:
        void Init();

        void Update();
        void Render();

    private:
        static Application *sInstance;

        bool mRunning;
    };
}


#endif //FPS_DEMO_APPLICATION_H

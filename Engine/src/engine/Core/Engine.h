//
// Created by Andrew Graser on 4/25/2024.
//

#ifndef FPS_DEMO_ENGINE_H
#define FPS_DEMO_ENGINE_H



namespace Engine {
    class Engine {
    public:
        Engine();
        ~Engine() = default;

        void Init();
        void Update();

        void OnEvent();

    private:

    private:
        GLFWwindow* mWindow;
    };
}


#endif //FPS_DEMO_ENGINE_H
